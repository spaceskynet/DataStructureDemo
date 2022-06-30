#pragma once
#include <QLabel>
#include <QMouseEvent>

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