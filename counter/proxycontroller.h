#ifndef COUNTERPROXYCONTROLLER_H
#define COUNTERPROXYCONTROLLER_H

#include "controller.h"
#include "rep_counter_replica.h"

#include <QRemoteObjectNode>

namespace counter {

class ProxyController : public Controller {
	Q_OBJECT
public:
	ProxyController(QObject *parent = nullptr);

	void increment() override;
	void initUI() override;

private:
	QRemoteObjectNode m_node;
	CounterReplica *m_replica;

};

} // namespace counter

#endif // COUNTERPROXYCONTROLLER_H
