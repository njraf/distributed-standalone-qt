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
		counterProcess->setProgram("../../../counter/build/Desktop-Debug/counter");
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

	QCommandLineOption controllerOption({"c", "controllerCommunicator"}, "The URL application controllers should use to communicate with the process launcher.");
	QCommandLineOption serviceOption({"s", "service"}, " The URL that the combined project should use to communicate with the process launcher.");
	QCommandLineParser clp;
	clp.addOption(controllerOption);
	clp.addOption(serviceOption);
	clp.process(a);

	if (!clp.isSet(controllerOption) || clp.value(controllerOption).isEmpty() || !clp.isSet(serviceOption) || clp.value(serviceOption).isEmpty()) {
		std::cerr << "Need both -c and -s options" << std::endl;
		return 1;
	}

	communicatorURL = clp.value(controllerOption);

	QRemoteObjectHost host(QUrl(clp.value(serviceOption)));
	AppService service;
	host.enableRemoting(&service);

	QObject::connect(&service, &AppService::startApplication, [](QString name){
		if (name == "counter") {
			toggleCounter(true);
		}
	});

	QObject::connect(&service, &AppService::stopApplication, [](QString name){
		if (name == "counter") {
			toggleCounter(false);
		}
	});

	auto result = a.exec();
	if (counterProcess) {
		delete counterProcess;
	}

	return result;
}
