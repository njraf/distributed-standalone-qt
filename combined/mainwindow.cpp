#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counterwidget.h"
#include <QDockWidget>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CounterWidget *counterWidget = new CounterWidget(this);


	QDockWidget *counterDock = new QDockWidget("Counter", this);
	counterDock->setWidget(counterWidget);
	counterDock->setDockLocation(Qt::LeftDockWidgetArea);
}

MainWindow::~MainWindow() {
	delete ui;
}
