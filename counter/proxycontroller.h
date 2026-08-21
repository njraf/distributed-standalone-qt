#ifndef PROXYCONTROLLER_H
#define PROXYCONTROLLER_H

#include "controller.h"
#include "rep_counter_replica.h"

#include <QRemoteObjectNode>

class ProxyController : public Controller {
	Q_OBJECT
public:
	ProxyController();

	void increment() override;

private:
	QRemoteObjectNode m_node;
	CounterReplica *m_replica;
};

#endif // PROXYCONTROLLER_H
