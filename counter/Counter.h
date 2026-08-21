#ifndef COUNTER_H
#define COUNTER_H

#include "rep_counter_source.h"

class Counter : public CounterSimpleSource
{
	Q_OBJECT

public:
	explicit Counter(QObject *parent = nullptr) : CounterSimpleSource(parent)
	{}

	void increment() override {
		setCount(count() + 1);
	}
};


#endif // COUNTER_H
