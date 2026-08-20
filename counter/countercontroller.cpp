#include "countercontroller.h"

CounterController::CounterController() {
}

void CounterController::increment() {
	count++;
	emit counterIncremented(count);
}
