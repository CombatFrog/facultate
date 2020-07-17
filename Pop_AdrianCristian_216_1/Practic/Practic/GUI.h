#pragma once
#include <string>
using std::string;

#include "service.h"
#include "QtWidgets/qapplication.h"
#include "QtWidgets/qwidget.h"
#include "qboxlayout.h"
#include "qtableview.h"
#include "tableModel.h"
#include "qlineedit.h"
#include "qformlayout.h"
#include "qpushbutton.h"
#include "qcombobox.h"
#include "GUITip.h"

class GUI : public QWidget
{
	Service& srv;
	vector<GUITip*> ferestre;
public:
	GUI(Service& s) :srv{ s } {
		initGUI();
		initConnect();
	}

private:
	QTableView* mainTable = new QTableView;
	QLineEdit* txtId = new QLineEdit;
	QLineEdit* txtNume = new QLineEdit;
	QLineEdit* txtTip = new QLineEdit;
	QLineEdit* txtPret = new QLineEdit;
	QPushButton* btnAdd = new QPushButton{ "Adauga" };
	QComboBox* boxTip = new QComboBox;

	void initConnect()
	{
		QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
			int id = txtId->text().toInt();
			string nume = txtNume->text().toStdString();
			string tip = txtTip->text().toStdString();
			double pret = txtPret->text().toDouble();
			Produs p{ id, nume, tip, pret };
			srv.adauga(p);
			string filtru = boxTip->currentText().toStdString();
			TableModel* model = new TableModel(srv, filtru);
			mainTable->setModel(model);
			for (auto& f : ferestre)
			{
				f->update();
			}
			});

		QObject::connect(boxTip, &QComboBox::currentTextChanged, [&]() {
			string filtru = boxTip->currentText().toStdString();
			TableModel* model = new TableModel(srv, filtru);
			mainTable->setModel(model);
			});
	}

	void initGUI()
	{
		QHBoxLayout* lyMain = new QHBoxLayout;
		setLayout(lyMain);

		string filtru = boxTip->currentText().toStdString();
		TableModel* model = new TableModel(srv, filtru);
		mainTable->setModel(model);
		lyMain->addWidget(mainTable);

		QFormLayout* lyAdd = new QFormLayout;
		lyAdd->addRow("Id", txtId);
		lyAdd->addRow("Nume", txtNume);
		lyAdd->addRow("Tip", txtTip);
		lyAdd->addRow("Pret", txtPret);

		QVBoxLayout* lyFunc = new QVBoxLayout;
		lyFunc->addLayout(lyAdd);
		lyFunc->addWidget(btnAdd);

		boxTip->addItem("Alege tipul");
		for (auto& t : srv.toateTipurile())
		{
			boxTip->addItem(QString::fromStdString(t));
		}
		lyFunc->addWidget(boxTip);

		lyMain->addLayout(lyFunc);

		for (auto& t : srv.toateTipurile())
		{
			GUITip* tip = new GUITip(srv, t);
			tip->show();
		}
	}
};