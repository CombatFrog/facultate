#pragma once
#include <fstream>
#include "service.h"

#include <QtWidgets/qwidget.h>
#include <QtWidgets/QApplication>
#include <QtWidgets/qlabel.h>
#include <QtWidgets/qpushbutton.h>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qformlayout.h>
#include <QtWidgets/qlistwidget.h>
#include <QtWidgets/qspinbox.h>
#include <QtWidgets/qradiobutton.h>
#include <qmessagebox.h>
#include <qstackedlayout.h>
#include <qtoolbar.h>
#include <qsignalmapper.h>
#include <vector>

class ProductGUI : public QWidget {
    Service& service;
public:
    ProductGUI(Service& service) noexcept :service{ service } {
        initGUI();
        loadData();
        initConnect();
    }
private:
    QListWidget* lst = new QListWidget;
    QPushButton* btnExit = new QPushButton{ "Exit" };
    QPushButton* btnExitReteta = new QPushButton{ "Exit" };
    QPushButton* btnAdd = new QPushButton{ "Adauga" };
    QPushButton* btnModifica = new QPushButton{ "Modifica" };
    QPushButton* btnSterge = new QPushButton{ "Sterge" };
    QPushButton* btnUndo = new QPushButton{ "Undo" };
    QPushButton* btnSort = new QPushButton{ "Sorteaza" };
    QPushButton* btnFilter = new QPushButton{ "Filtreaza" };
    QPushButton* btnReload = new QPushButton{ "Reincarca" };
    QPushButton* btnRecipe = new QPushButton{ "Reteta" };

    QLineEdit* txtDenumire = new QLineEdit;
    QSpinBox* txtPret = new QSpinBox;
    QLineEdit* txtProducator = new QLineEdit;
    QLineEdit* txtSubstanta = new QLineEdit;

    QFormLayout* formLy = new QFormLayout;
    
    QWidget* widgetSort = new QWidget();
    QVBoxLayout* lySort = new QVBoxLayout{widgetSort};
    QHBoxLayout* lySortOk = new QHBoxLayout{};
    QRadioButton* btnSortDenumire = new QRadioButton{ "Sorteaza dupa denumire" };
    QRadioButton* btnSortProducator = new QRadioButton{ "Sorteaza dupa producator" };
    QRadioButton* btnSortSubstanta = new QRadioButton{ "Sorteaza dupa substanta activa" };
    QPushButton* btnSortOk = new QPushButton{ "Ok" };
    QPushButton* btnSortCancel = new QPushButton{ "Cancel" };

    QWidget* widgetFilter = new QWidget();
    QVBoxLayout* lyFilter = new QVBoxLayout{ widgetFilter };
    QHBoxLayout* lyFilterOk = new QHBoxLayout{};
    QRadioButton* btnFilterPret= new QRadioButton{ "Filtreaza dupa pret" };
    QRadioButton* btnFilterSubstanta = new QRadioButton{ "Sorteaza dupa substanta activa" };
    QLineEdit* txtFilterSubstanta = new QLineEdit;
    QSpinBox* txtFilterPret = new QSpinBox;
    QPushButton* btnFilterOk = new QPushButton{ "Ok" };
    QPushButton* btnFilterCancel = new QPushButton{ "Cancel" };

    QAction* actFarmacie = new QAction{ "Farmacie" };
    QAction* actReteta = new QAction{ "Reteta" };

    QWidget* widgetReteta = new QWidget();
    QWidget* widgetRonly = new QWidget();
    QHBoxLayout* lyReteta = new QHBoxLayout{ widgetReteta };
    QListWidget* lstReteta = new QListWidget;
    QLineEdit* txtExport = new QLineEdit;
    QLineEdit* txtMed = new QLineEdit;
    QPushButton* btnRetetaGenereaza = new QPushButton{ "Genereaza" };
    QPushButton* btnRetetaGoleste = new QPushButton{ "Goleste" };
    QPushButton* btnRetetaExport = new QPushButton{ "Export" };

    QVBoxLayout* lyCerinta = new QVBoxLayout{};
    QPushButton* CosCRUD = new QPushButton{ "CosGUI" };
    QPushButton* CosROnly = new QPushButton{ "CosReadOnly" };


    void initConnect() {
        QObject::connect(btnExit, &QPushButton::clicked, [&]() {
            close();
            widgetFilter->close();
            widgetSort->close();
            widgetReteta->close();
            });

        QObject::connect(btnExitReteta, &QPushButton::clicked, [&]() {
            widgetFilter->close();
            widgetSort->close();
            widgetReteta->close();
            close();
            });

        QObject::connect(lst, &QListWidget::itemClicked, [&]() {
            Medicament m = service.cautaMedicament(lst->currentItem()->text().toStdString());
            txtDenumire->setText(QString::fromStdString(m.getDenumire()));
            txtPret->setValue(m.getPret());
            txtProducator->setText(QString::fromStdString(m.getProducator()));
            txtSubstanta->setText(QString::fromStdString(m.getSubstantaActiva()));
            });

        QObject::connect(btnAdd, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            auto pret = txtPret->value();
            auto producator = txtProducator->text();
            auto substanta = txtSubstanta->text();
            service.adaugaMedicament(denumire.toStdString(), pret, producator.toStdString(), substanta.toStdString());
            loadData();
            });

        QObject::connect(btnSterge, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            try {
                service.stergeMedicament(denumire.toStdString());
            }
            catch (RepoException) {
                QMessageBox::critical(nullptr, "Error", "Nu exista medicament cu aceasta denumire!");
            }
            loadData();
            });

        QObject::connect(btnModifica, &QPushButton::clicked, [&]() {
            auto denumire = txtDenumire->text();
            auto pret = txtPret->text();
            auto producator = txtProducator->text();
            auto substanta = txtSubstanta->text();
            try {
                service.modificaMedicament(denumire.toStdString(), pret.toInt(), producator.toStdString(), substanta.toStdString());
            }
            catch (RepoException) {
                QMessageBox::critical(nullptr, "", "Nu exista medicament cu aceasta denumire!");
            }
            loadData();
            });

        QObject::connect(btnUndo, &QPushButton::clicked, [&]() {
            try
            {
                service.undo();
                loadData();
            }
            catch (RepoException)
            {
                QMessageBox::information(nullptr, "Info", "Nu mai exista operatii!");
            }
            });

        QObject::connect(btnSort, &QPushButton::clicked, [&]() {
            widgetSort->setVisible(true);
            });

        QObject::connect(btnSortCancel, &QPushButton::clicked, [&]() {
            widgetSort->setVisible(false);
            });

        QObject::connect(btnSortOk, &QPushButton::clicked, [&]() {
            vector <Medicament> medicamente;
            if (btnSortDenumire->isChecked())
            {
                medicamente = service.sorteazaDenumire();
            }
            if (btnSortProducator->isChecked())
            {
                medicamente = service.sorteazaProducator();
            }
            if (btnSortSubstanta->isChecked())
            {
                medicamente = service.sorteazaSubstantaPret();
            }
            lst->clear();
            for (const auto& m : medicamente) {
                lst->addItem(QString::fromStdString(m.getDenumire()));
            }

           // loadBtns();
            widgetSort->setVisible(false);
            });

        QObject::connect(btnFilter, &QPushButton::clicked, [&]() {
            widgetFilter->setVisible(true);
            });

        QObject::connect(btnFilterCancel, &QPushButton::clicked, [&]() {
            widgetFilter->setVisible(false);
            });

        QObject::connect(btnFilterOk, &QPushButton::clicked, [&]() {
            vector <Medicament> medicamente;
            if (btnFilterPret->isChecked())
            {
                medicamente = service.filtreazaPret(txtFilterPret->text().toInt());
            }
            if (btnFilterSubstanta->isChecked())
            {
                medicamente = service.filtreazaSubstanta(txtFilterSubstanta->text().toStdString());
            }
            lst->clear();
            for (const auto& m : medicamente) {
                lst->addItem(QString::fromStdString(m.getDenumire()));
            }
            
            //loadBtns();
            widgetFilter->setVisible(false);
            });

        QObject::connect(btnReload, &QPushButton::clicked, [&]() {
            loadData();
            });

        QObject::connect(actReteta, &QAction::triggered, [&]() {
            this->setVisible(false);
            widgetReteta->setVisible(true);
            });

        QObject::connect(actFarmacie, &QAction::triggered, [&]() {
            widgetReteta->setVisible(false);
            this->setVisible(true);
            });

        QObject::connect(btnRecipe, &QPushButton::clicked, [&]() {
            service.adaugaReteta(txtDenumire->text().toStdString());
            loadData();
            });

        QObject::connect(btnRetetaGoleste, &QPushButton::clicked, [&]() {
            service.golesteReteta();
            loadData();
            });

        QObject::connect(btnRetetaGenereaza, &QPushButton::clicked, [&]() {
            service.genereazaReteta(txtMed->text().toInt());
            loadData();
            });

        QObject::connect(btnRetetaExport, &QPushButton::clicked, [&]() {
            std::ofstream fisierExport;
            fisierExport.open(txtExport->text().toStdString());
            vector<Medicament> reteta = service.getReteta();
            fisierExport << "Denumire" << " " << "Pret" << " " << "Producator" << " " << "Substanta" << "\n";
            for (const auto& medicament : reteta) {
                fisierExport << medicament.getDenumire() << " " << medicament.getPret() << " " << medicament.getProducator() << " " << medicament.getSubstantaActiva() << "\n";
            }
            fisierExport.close();
            });

        QObject::connect(CosCRUD, &QPushButton::clicked, [&]() {
            widgetReteta->setVisible(true);
            });

        QObject::connect(CosROnly, &QPushButton::clicked, [&]() {
            widgetRonly->setVisible(true);
            });
        
    }

    

    void loadData() {
        lst->clear();
        vector<Medicament> medicamente = service.getAll();
        for (const auto& m : medicamente) {
            lst->addItem(QString::fromStdString(m.getDenumire()));
        }

       

        lstReteta->clear();
        vector<Medicament> reteta = service.getReteta();
        for (const auto& m : reteta) {
            lstReteta->addItem(QString::fromStdString(m.getDenumire()));
        }

        /*
        QLayoutItem* item;
        while ((item = lyCerinta->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }

        for (const auto& m : medicamente)
        {
            QPushButton* btn = new QPushButton(QString::fromStdString(m.getDenumire()));
            connect(btn, &QPushButton::clicked, [=] { service.stergeMedicament(m.getDenumire()); loadData(); });
            lyCerinta->addWidget(btn);

        }
        */

    }

    void loadBtns()
    {
        vector<Medicament> medicamente = service.getAll();
        QLayoutItem* item;
        while ((item = lyCerinta->takeAt(0)) != NULL)
        {
            delete item->widget();
            delete item;
        }

        for (const auto& m : medicamente)
        {
            QPushButton* btn = new QPushButton(QString::fromStdString(m.getDenumire()));
            connect(btn, &QPushButton::clicked, [=] { service.stergeMedicament(m.getDenumire()); loadData(); });
            lyCerinta->addWidget(btn);

        }
    }

    void initGUI() {
        setWindowTitle("Farmacie");
        QHBoxLayout* lyMain = new QHBoxLayout{};
        setLayout(lyMain);
       
        lyMain->addWidget(lst);

        auto stgLy = new QVBoxLayout;
        formLy->addRow("Denumire", txtDenumire);
        formLy->addRow("Pret", txtPret);
        formLy->addRow("Producator", txtProducator);
        formLy->addRow("Substanta activa", txtSubstanta);
        stgLy->addLayout(formLy);

        auto lyBtn = new QHBoxLayout{};
        lyBtn->addWidget(btnAdd);
        lyBtn->addWidget(btnSterge);
        lyBtn->addWidget(btnModifica);
        stgLy->addLayout(lyBtn);

        auto lyBtn2 = new QHBoxLayout{};
        lyBtn2->addWidget(btnSort);
        lyBtn2->addWidget(btnFilter);
        lyBtn2->addWidget(btnReload);
        stgLy->addLayout(lyBtn2);

        auto lyBtn3 = new QHBoxLayout{};
        lyBtn3->addWidget(btnRecipe);
        lyBtn3->addWidget(btnUndo);
        lyBtn3->addWidget(btnExit);
        lyBtn3->addWidget(CosCRUD);
        lyBtn3->addWidget(CosROnly);
        stgLy->addLayout(lyBtn3);

        lyMain->addLayout(stgLy);

        lyMain->addLayout(lyCerinta);

     
        widgetSort->setVisible(false);
        lySort->addWidget(btnSortDenumire);
        btnSortDenumire->setChecked(true);
        lySort->addWidget(btnSortProducator);
        lySort->addWidget(btnSortSubstanta);
        lySortOk->addWidget(btnSortOk);
        lySortOk->addWidget(btnSortCancel);
        lySort->addLayout(lySortOk);
        widgetSort->setWindowTitle("Sorteaza");

        widgetFilter->setVisible(false);
        lyFilter->addWidget(btnFilterPret);
        lyFilter->addWidget(txtFilterPret);
        btnFilterPret->setChecked(true);
        lyFilter->addWidget(btnFilterSubstanta);
        lyFilter->addWidget(txtFilterSubstanta);
        lyFilterOk->addWidget(btnFilterOk);
        lyFilterOk->addWidget(btnFilterCancel);
        lyFilter->addLayout(lyFilterOk);
        widgetFilter->setWindowTitle("Filtreaza");

        /*
        QToolBar* toolBar = new QToolBar();
        toolBar->addAction(actFarmacie);
        toolBar->addAction(actReteta);
        this->layout()->setMenuBar(toolBar);

        QToolBar* toolBarReteta = new QToolBar();
        toolBarReteta->addAction(actFarmacie);
        toolBarReteta->addAction(actReteta);
        this->layout()->setMenuBar(toolBar);
        */


        widgetReteta->setVisible(false);
        auto stgLyReteta = new QVBoxLayout;
        QFormLayout* formLyReteta = new QFormLayout;
        formLyReteta->addRow("Fisier", txtExport);
        formLyReteta->addRow("Numar", txtMed);
        stgLyReteta->addLayout(formLyReteta);
        stgLyReteta->addWidget(btnRetetaGenereaza);
        stgLyReteta->addWidget(btnRetetaGoleste);
        stgLyReteta->addWidget(btnRetetaExport);
        stgLyReteta->addWidget(btnExitReteta);
        widgetReteta->setWindowTitle("Reteta");
        
        lyReteta->addWidget(lstReteta);
        lyReteta->addLayout(stgLyReteta);
        //lyReteta->setMenuBar(toolBarReteta);

        
  
        setLayout(lyMain);
    }

};