/**
 * @file newWidgets.hpp
 * @author SpaceSkyNet (spaceskynet@outlook.com)
 * @brief 自实现的提升类
 * @version 0.1
 * @date 2022-06-27
 * 
 * @copyright Copyright (c) 2022
 * 
 */
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