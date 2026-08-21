#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counterwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(Controller *controller, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_controller(controller)
{
	ui->setupUi(this);

	controller->setParent(this);

	CounterWidget *counterWidget = new CounterWidget(this);

	connect(m_controller, &Controller::counterIncremented, counterWidget, &CounterWidget::updateCounter);
	connect(counterWidget, &CounterWidget::increment, m_controller, &Controller::increment);

	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->addWidget(counterWidget);
	ui->centralwidget->setLayout(verticalLayout);
}

MainWindow::~MainWindow() {
	delete ui;
}
