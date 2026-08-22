#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "proxycontroller.h"
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	Ui::MainWindow *ui;
	QMap<QString, QWidget*> externalWidgets;

	ProxyController *m_counter = nullptr;
	QProcess *m_counterProcess = nullptr;

public slots:
	void toggleCounterProxy();
};
#endif // MAINWINDOW_H
