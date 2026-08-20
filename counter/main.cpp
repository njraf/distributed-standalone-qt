#include "mainwindow.h"
#include "countercontroller.h"

#include <QApplication>

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);

	Controller *counterController = new CounterController();

	// MainWindow takes ownership of the controller and deletes it
	MainWindow w(counterController);
	w.show();
	return a.exec();
}
