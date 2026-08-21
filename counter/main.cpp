#include "mainwindow.h"
#include "countercontroller.h"
#include "proxycontroller.h"
#include <iostream>

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QCommandLineOption clientOption("client", "Start the program in client mode");
	QCommandLineOption serverOption("server", "Start the program in server mode");
	QCommandLineParser clp;
	clp.addOption(clientOption);
	clp.addOption(serverOption);
	clp.process(a);

	const bool isClient = clp.isSet(clientOption);
	const bool isServer = clp.isSet(serverOption);

	if(isClient && isServer) {
		std::cerr << "Cannot be both client and server" << std::endl;
		return 1;
	}


	Controller *controller = nullptr;

	if (isServer) {
		controller = new CounterController();

		const auto result = a.exec();
		delete controller;
		return result;
	} else if (isClient) {
		controller = new ProxyController();

		// MainWindow takes ownership of the controller and deletes it
		MainWindow w(controller);
		w.show();
		return a.exec();
	} else {
		controller = new CounterController();

		// MainWindow takes ownership of the controller and deletes it
		MainWindow w(controller);
		w.show();
		return a.exec();
	}
}
