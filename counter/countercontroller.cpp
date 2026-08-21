#include "countercontroller.h"
#include <QUrl>

CounterController::CounterController() {
	m_host.setHostUrl(QUrl("local:counter"));

	m_host.enableRemoting(&m_counter);

	connect(&m_counter, &Counter::countChanged, this, &CounterController::counterIncremented);
}

void CounterController::increment() {
	m_counter.increment();
}
