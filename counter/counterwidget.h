#ifndef COUNTERWIDGET_H
#define COUNTERWIDGET_H

#include <QWidget>

namespace Ui {
class CounterWidget;
}

class CounterWidget : public QWidget {
	Q_OBJECT

public:
	explicit CounterWidget(QWidget *parent = nullptr);
	~CounterWidget();

private:
	Ui::CounterWidget *ui;
	int m_count;

public slots:
	void updateCounter(int value);

signals:
	void increment();
};

#endif // COUNTERWIDGET_H
