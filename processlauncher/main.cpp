#include <QCoreApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QRemoteObjectHost>
#include <iostream>
#include <QProcess>

#include "appservice.h"

QProcess *counterProcess = nullptr;
QString communicatorURL = "";

void toggleCounter(bool start) {
	if (start) {
		std::cout << "counter start requested" << std::endl;
		counterProcess = new QProcess();
		counterProcess->setProgram("counter/build/Desktop-Debug/counter"); // assumes processlauncher is run from the root of the repo
		counterProcess->setArguments({"--server"});
		QObject::connect(counterProcess, &QProcess::errorOccurred, [](QProcess::ProcessError error) {
			std::cout << "counter error: " << error << std::endl;
		});
		counterProcess->start();
	} else {
		std::cout << "Stopping counter" << std::endl;
		counterProcess->close();
		delete counterProcess;
		counterProcess = nullptr;
		std::cout << "Stopped counter" << std::endl;
	}

}

int main(int argc, char *argv[]) {
	QCoreApplication a(argc, argv);

	QCommandLineOption controllerOption({"c", "controllerCommunicator"}, "The URL application controllers should use to communicate with the process launcher.", "url");
	QCommandLineOption serviceOption({"s", "service"}, " The URL that the combined project should use to communicate with the process launcher.", "url");
	QCommandLineParser clp;
	clp.addOption(controllerOption);
	clp.addOption(serviceOption);
	clp.process(a);

	if (!clp.isSet(controllerOption) || clp.value(controllerOption).isEmpty() || !clp.isSet(serviceOption) || clp.value(serviceOption).isEmpty()) {
		std::cerr << "Need both -c and -s options" << std::endl;
		return 1;
	}

	// application service setup

	QRemoteObjectHost serviceHost(QUrl(clp.value(serviceOption)));
	AppService service;
	if (!serviceHost.enableRemoting(&service)) {
		std::cerr << "Could not enable remoting for the application service" << std::endl;
		return 1;
	}

	std::cout << "Started application service remoting" << std::endl;

	QObject::connect(&service, &AppService::applicationStartRequest, [&service](QString name){
		if (name == "counter") {
			toggleCounter(true);
			QObject::connect(counterProcess, &QProcess::readyReadStandardOutput, [&service]() {
				service.processStateChanged("counter", true);
			});
		}
	});

	QObject::connect(&service, &AppService::applicationStopRequest, [&service](QString name){
		if (name == "counter") {
			toggleCounter(false);
		}
		service.processStateChanged(name, false);
	});

	// controller communicator setup

	QRemoteObjectHost controllerHost(QUrl(clp.value(controllerOption)));
	//AppService service;
	//if (!controllerHost.enableRemoting(&service)) {
	//	std::cerr << "Could not enable remoting for the application service" << std::endl;
	//	return 1;
	//}

	//std::cout << "Started controller communicator remoting" << std::endl;

	auto result = a.exec();
	if (counterProcess) {
		delete counterProcess;
	}

	return result;
}
