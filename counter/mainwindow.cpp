#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counterwidget.h"

#include <QVBoxLayout>

MainWindow::MainWindow(counter::Controller *controller, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
	, m_controller(controller)
{
	ui->setupUi(this);

	controller->setParent(this);

	CounterWidget *counterWidget = new CounterWidget(this);

	connect(m_controller, &counter::Controller::counterIncremented, counterWidget, &CounterWidget::updateCounter);
	connect(counterWidget, &CounterWidget::increment, m_controller, &counter::Controller::increment);

	QVBoxLayout *verticalLayout = new QVBoxLayout(this);
	verticalLayout->addWidget(counterWidget);
	ui->centralwidget->setLayout(verticalLayout);

	m_controller->initUI();
}

MainWindow::~MainWindow() {
	delete ui;
}
