#ifndef ABSTRACTCOUNTERCONTROLLER_H
#define ABSTRACTCOUNTERCONTROLLER_H

#include <QObject>

namespace counter {

class Controller : public QObject {
	Q_OBJECT
public:
	Controller(QObject *parent = nullptr);

	virtual void initUI()=0;

public slots:
	virtual void increment()=0;


signals:
	void counterIncremented(int value);
};

} // namespace counter

#endif // ABSTRACTCOUNTERCONTROLLER_H
