#pragma once
#include <QSpinBox>
#include <QLabel>
#include <QMouseEvent>

class QClickedSpinBox : public QSpinBox
{
	Q_OBJECT
public:
	explicit QClickedSpinBox(QWidget* parent = nullptr) : QSpinBox(parent) {}

protected:
	virtual void mouseReleaseEvent(QMouseEvent* e) {
		if (e->button() == Qt::LeftButton) {
			emit clicked();
		}
		QSpinBox::mousePressEvent(e);
	}

signals:
	void clicked();
	

public slots:

};

class QClickedLabel : public QLabel
{
	Q_OBJECT
public:
	explicit QClickedLabel(QWidget* parent = nullptr) : QLabel(parent) {}

protected:
	virtual void mouseReleaseEvent(QMouseEvent* e) {
		if (e->button() == Qt::LeftButton) {
			emit clicked();
		}
		QLabel::mousePressEvent(e);
	}

signals:
	void clicked();


public slots:

};