#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counterwidget.h"
#include <QDockWidget>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	CounterWidget *counterWidget = new CounterWidget(this);
	externalWidgets.insert("counter", counterWidget);


	QDockWidget *counterDock = new QDockWidget("Counter", this);
	counterDock->setWidget(counterWidget);
	counterDock->setDockLocation(Qt::LeftDockWidgetArea);


	connect(ui->counterPushButton, &QPushButton::clicked, this, &MainWindow::toggleCounterProxy);
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::toggleCounterProxy() {
	if (!m_counter) {
		std::cout << "Counter start clicked" << std::endl;
		m_counterProcess = new QProcess(this);
		m_counterProcess->setProgram("../../../counter/build/Desktop-Debug/counter");
		m_counterProcess->setArguments({"--server"});
		connect(m_counterProcess, &QProcess::readyReadStandardOutput, this, [this](){
			std::cout << "Starting counter" << std::endl;
			m_counter = new ProxyController(this);
			connect(m_counter, &ProxyController::counterIncremented, dynamic_cast<CounterWidget*>(externalWidgets.value("counter")), &CounterWidget::updateCounter);
			connect(dynamic_cast<CounterWidget*>(externalWidgets.value("counter")), &CounterWidget::increment, m_counter, &ProxyController::increment);
			ui->counterPushButton->setText("Stop");
			std::cout << "Started counter" << std::endl;
		});
		connect(m_counterProcess, &QProcess::errorOccurred, this, [](QProcess::ProcessError error) {
			std::cout << "Counter error: " << error << std::endl;
		});
		m_counterProcess->start();
	} else {
		std::cout << "Stopping counter" << std::endl;
		m_counterProcess->close();
		delete m_counter;
		delete m_counterProcess;
		m_counter = nullptr;
		m_counterProcess = nullptr;

		ui->counterPushButton->setText("Start");
		std::cout << "Stopped counter" << std::endl;
	}
}
