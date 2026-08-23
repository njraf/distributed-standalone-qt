#ifndef APPSERVICE_H
#define APPSERVICE_H

#include "rep_appservice_source.h"

class AppService : public AppServiceSimpleSource
{
	Q_OBJECT
public:
	explicit AppService(QObject *parent = nullptr) : AppServiceSimpleSource(parent){}

signals:
	void applicationStartRequest(QString name);
	void applicationStopRequest(QString name);
public slots:
	void startApplication(QString name) {
		emit applicationStartRequest(name);
	}

	void stopApplication(QString name) {
		emit applicationStopRequest(name);
	}
};

#endif // APPSERVICE_H
