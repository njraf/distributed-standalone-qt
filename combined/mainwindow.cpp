#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "counterwidget.h"
#include "rep_appservice_replica.h"
#include <QDockWidget>
#include <QPushButton>
#include <iostream>

MainWindow::MainWindow(QString serviceURL, QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_node.connectToNode(QUrl(serviceURL));
	m_appService = m_node.acquire<AppServiceReplica>();
	m_appService->setParent(this);
	if (!m_appService->waitForSource() || !m_appService->isReplicaValid()) {
		std::cerr << "Could not connect to the source after waiting" << std::endl;
		return;
	}


	CounterWidget *counterWidget = new CounterWidget(this);
	externalWidgets.insert("counter", counterWidget);


	QDockWidget *counterDock = new QDockWidget("Counter", this);
	counterDock->setWidget(counterWidget);
	counterDock->setDockLocation(Qt::LeftDockWidgetArea);


	connect(ui->counterPushButton, &QPushButton::clicked, this, &MainWindow::toggleCounterProxy);
	connect(m_appService, &AppServiceReplica::processStateChanged, this, [this](QString name, bool start) {
		if (name == "counter") {
			onCounterProcessStateChanged(start);
		}
	});
}

MainWindow::~MainWindow() {
	delete ui;
}

void MainWindow::toggleCounterProxy() {
	if (!m_counter) {
		m_appService->startApplication("counter");
	} else {
		m_appService->stopApplication("counter");
	}
}

void MainWindow::onCounterProcessStateChanged(bool start) {
	if (start) {
		std::cout << "Starting counter" << std::endl;
		m_counter = new counter::ProxyController(this);
		connect(m_counter, &counter::ProxyController::counterIncremented, dynamic_cast<CounterWidget*>(externalWidgets.value("counter")), &CounterWidget::updateCounter);
		connect(dynamic_cast<CounterWidget*>(externalWidgets.value("counter")), &CounterWidget::increment, m_counter, &counter::ProxyController::increment);
		ui->counterPushButton->setText("Stop");
		std::cout << "Started counter" << std::endl;
	} else {
		std::cout << "Stopping counter" << std::endl;
		delete m_counter;
		m_counter = nullptr;
		ui->counterPushButton->setText("Start");
		std::cout << "Stopped counter" << std::endl;
	}
}
