#ifndef COUNTERCONTROLLER_H
#define COUNTERCONTROLLER_H

#include "controller.h"

class CounterController : public Controller {
public:
	CounterController();

	void increment() override;

private:
	int count = 0;
};

#endif // COUNTERCONTROLLER_H
