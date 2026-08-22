#ifndef APPSERVICE_H
#define APPSERVICE_H

#include "rep_appservice_source.h"

class AppService : public AppServiceSimpleSource
{
	Q_OBJECT
public:
	explicit AppService(QObject *parent = nullptr) : AppServiceSimpleSource(parent){}

public slots:
	void startApplication(QString name) {

	}

	void stopApplication(QString name) {

	}
};

#endif // APPSERVICE_H
