#pragma once
#include "service.h"
#include "QtWidgets/qapplication.h"
#include "QtWidgets/qwidget.h"
#include "qpainter.h"

class GUITip : public QWidget
{
	Service& srv;
	string tip;
public:
	GUITip(Service& srv, string tip) :srv{ srv }, tip{ tip }
	{
		init();
	};
private:

	void paintEvent(QPaintEvent* event)
	{
		QPainter painter(this);
		painter.setPen(Qt::black);
		for (int i = 0; i < srv.nrTip(tip); i++)
		{
			int nr = rand() % 100;
			painter.drawEllipse(QPointF(nr, nr), 10, 10);
		}
	}

	void init()
	{
		QHBoxLayout* lyMain = new QHBoxLayout;
		setLayout(lyMain);
		setWindowTitle(QString::fromStdString(tip));
	}
};
