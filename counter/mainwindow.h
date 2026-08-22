#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
	Q_OBJECT

public:
	explicit MainWindow(counter::Controller *controller, QWidget *parent = nullptr);
	~MainWindow();

	void initUI();

private:
	Ui::MainWindow *ui;
	counter::Controller *m_controller;
};
#endif // MAINWINDOW_H
