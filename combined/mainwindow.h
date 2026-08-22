#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRemoteObjectNode>
#include <QString>
#include "rep_appservice_replica.h"
#include "proxycontroller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QString serviceURL, QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QMap<QString, QWidget*> externalWidgets;

	counter::ProxyController *m_counter = nullptr;
	QRemoteObjectNode m_node;
	AppServiceReplica *m_appService = nullptr;

public slots:
	void toggleCounterProxy();
	void onCounterProcessStateChanged(bool start);
};
#endif // MAINWINDOW_H
