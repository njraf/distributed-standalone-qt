#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

class Controller : public QObject {
	Q_OBJECT
public:
	Controller();

public slots:
	virtual void increment()=0;


signals:
	void counterIncremented(int value);
};

#endif // CONTROLLER_H
