#include "mainwindow.h"

#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <iostream>
int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	QCommandLineOption serviceOption({"s", "service"}, " The URL that the combined project should use to communicate with the process launcher.", "url");
	QCommandLineParser clp;
	clp.addOption(serviceOption);
	clp.process(a);

	if (!clp.isSet(serviceOption) || clp.value(serviceOption).isEmpty()) {
		std::cerr << "Need -s option" << std::endl;
		return 1;
	}

	MainWindow w(clp.value(serviceOption));
	w.show();
	return a.exec();
}
