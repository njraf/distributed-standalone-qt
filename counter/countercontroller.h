#ifndef COUNTERCONTROLLER_H
#define COUNTERCONTROLLER_H

#include "controller.h"
#include "Counter.h"
#include <QRemoteObjectHost>

class CounterController : public Controller {
	Q_OBJECT
public:
	CounterController();

	void increment() override;

private:
	QRemoteObjectHost m_host;
	Counter m_counter;
};

#endif // COUNTERCONTROLLER_H
