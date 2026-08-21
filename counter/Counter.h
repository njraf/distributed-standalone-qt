#ifndef COUNTER_H
#define COUNTER_H

#include "rep_counter_source.h"
#include <iostream>

class Counter : public CounterSimpleSource
{
	Q_OBJECT

public:
	explicit Counter(QObject *parent = nullptr) : CounterSimpleSource(parent)
	{}

	void increment() override {
		std::cout << "Counter increment()" << std::endl;
		setCount(count() + 1);
	}
};


#endif // COUNTER_H
