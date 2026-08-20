#include "counterwidget.h"
#include "ui_counterwidget.h"
#include <QPushButton>

CounterWidget::CounterWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::CounterWidget)
	, m_count(0)
{
	ui->setupUi(this);

	ui->countValue->setText(QString::number(m_count));
	connect(ui->incrementButton, &QPushButton::clicked, this, [this](){ emit increment(); });
}

CounterWidget::~CounterWidget() {
	delete ui;
}

void CounterWidget::updateCounter(int value)
{
	m_count = value;
	ui->countValue->setText(QString::number(m_count));
}
