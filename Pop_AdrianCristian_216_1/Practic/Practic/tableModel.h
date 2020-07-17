#pragma once
#include <QAbstractTableModel>
#include "service.h"

class TableModel : public QAbstractTableModel {
	Service& srv;
	string filtru;
public:
	TableModel(Service& srv, string filtru) :srv{ srv }, filtru{ filtru } {}

	int rowCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return srv.getAll().size();
	}

	int columnCount(const QModelIndex& parent = QModelIndex()) const override
	{
		return 5;
	}

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override
	{
		if (role == Qt::DisplayRole)
		{
			Produs p = srv.sorteaza()[index.row()];
			if (index.column() == 0)
			{
				return QString::number(p.getId());
			}
			if (index.column() == 1)
			{
				return QString::fromStdString(p.getNume());
			}
			if (index.column() == 2)
			{
				return QString::fromStdString(p.getTip());
			}
			if (index.column() == 3)
			{
				return QString::number(p.getPret());
			}
			if (index.column() == 4)
			{
				return QString::number(srv.nrTip(p.getTip()));
			}
		}
		if (role == Qt::BackgroundRole && filtru != "Alege tipul")
		{
			int row = index.row();
			QModelIndex index = this->index(row, 2);
			QString data = index.data().toString();
			if (data == QString::fromStdString(filtru))
			{
				return QBrush(Qt::red);
			}
		}
		return QVariant{};
	}

	QVariant headerData(int section, Qt::Orientation orientation, int role) const override
	{
		if (orientation == Qt::Horizontal)
		{
			if (role == Qt::DisplayRole)
			{
				if (section == 0)
				{
					return "Id";
				}
				if (section == 1)
				{
					return "Nume";
				}
				if (section == 2)
				{
					return "Tip";
				}
				if (section == 3)
				{
					return "Pret";
				}
				if (section == 4)
				{
					return "Nr Tip";
				}
			}
		}
		return QVariant{};
	}
};