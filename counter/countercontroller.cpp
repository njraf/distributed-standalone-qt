#include "countercontroller.h"
#include <iostream>
#include <QUrl>

CounterController::CounterController(QObject *parent) : Controller(parent) {
	m_host.setHostUrl(QUrl("local:counter"));

	if (!m_host.enableRemoting(&m_counter)) {
		std::cerr << "Could not enable remoting" << std::endl;
		return;
	} else {
		std::cout << "Enabled remoting" << std::endl;
	}

	connect(&m_counter, &Counter::countChanged, this, &CounterController::counterIncremented);
}

void CounterController::increment() {
	m_counter.increment();
}

void CounterController::initUI() {}
