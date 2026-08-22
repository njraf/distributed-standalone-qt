#include <iostream>
#include "proxycontroller.h"

ProxyController::ProxyController(QObject *parent) : Controller(parent) {
	if (!m_node.connectToNode(QUrl("local:counter"))) {
		std::cerr << "Could not connect to the source" << std::endl;
		return;
	} else {
		std::cout << "Connected to source" << std::endl;
	}
	m_replica = m_node.acquire<CounterReplica>();
	m_replica->setParent(this);

	if (!m_replica->waitForSource() || !m_replica->isReplicaValid()) {
		std::cerr << "Could not connect to the source after waiting" << std::endl;
		return;
	} else {
		std::cout << "Acquired replica" << std::endl;
	}

	connect(m_replica, &CounterReplica::countChanged, this, &Controller::counterIncremented);

	initUI();
}

void ProxyController::initUI() {
	emit m_replica->countChanged(m_replica->count());
}

void ProxyController::increment() {
	m_replica->increment();
}
