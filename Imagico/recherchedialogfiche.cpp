#include "recherchedialogfiche.h"
#include "ui_recherchedialogfiche.h"
#include "mainwindow.h"
//#include "ui_mainwindow.h"
#include <iostream>
#include"QMessageBox"

using namespace std;

RechercheDialogFiche::RechercheDialogFiche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RechercheDialogFiche)
{
    ui->setupUi(this);
}

QString RechercheDialogFiche::getNumeroRecherche() const
{
    return _NumeroRecherche;
}

float RechercheDialogFiche::getCoutMin() const
{
    return _CoutMin;
}

float RechercheDialogFiche::getCoutMax() const
{
    return _CoutMax;
}

QString RechercheDialogFiche::getCritereRecherche() const
{
    return _CritereDeRecherche;
}

RechercheDialogFiche::~RechercheDialogFiche()
{
    delete ui;
}

void RechercheDialogFiche::on_buttonBox_accepted()
{

    QString NumeroRech = ui->NumeroArechercher->text();
    float ValCoutMin = ui->CoutMin->text().toFloat();
    float ValCoutMax = ui->CoutMax->text().toFloat();

    if (ui->radioButtonNumero->isChecked()==0 && ui->radioButtonCout->isChecked()==0)
    {
        QMessageBox::information(this,"Choisir un critère",
                                      "Critère de recherche non selectionné");
       return;
    }

    if (ui->radioButtonNumero->isChecked()==1 && NumeroRech.isEmpty())
    {
        QMessageBox::information(this,"I-magico","Veuillez saisir un numeo à rechercher.");
        return;
    }else
    {
        _NumeroRecherche = NumeroRech;
        _CritereDeRecherche = "NUMERO";
    }


    if (ui->radioButtonCout->isChecked() ==1)
    {
        if(ValCoutMin ==0 || ValCoutMax == 0)
        {
            QMessageBox::information(this,"I-magico","Veuillez saisir les bornes Min et Max.");
            return;
        }else
        {
            _CoutMin = ValCoutMin;
            _CoutMax = ValCoutMax;
            _CritereDeRecherche = "MINMAX";
        }
    }

    cout<<endl<<"get critere :" << getCritereRecherche().toStdString();

    accept();
}

void RechercheDialogFiche::on_buttonBox_rejected()
{
    reject();
}

void RechercheDialogFiche::on_groupBox_clicked()
{

}

void RechercheDialogFiche::on_radioButtonNumero_clicked()
{

    if (ui->radioButtonNumero->isChecked())
    {
        ui->NumeroArechercher->setVisible(true);
        ui->label_Numero->setVisible(true);
        ui->CoutMax->setVisible(false);
        ui->CoutMin->setVisible(false);
        ui->label_entreCout->setVisible(false);
        ui->label_EtCout->setVisible(false);
    }
}

void RechercheDialogFiche::on_radioButtonCout_clicked()
{

     if(ui->radioButtonCout->isChecked())
     {
        ui->NumeroArechercher->setVisible(false);
        ui->label_Numero->setVisible(false);
        ui->CoutMax->setVisible(true);
        ui->CoutMin->setVisible(true);
        ui->label_entreCout->setVisible(true);
        ui->label_EtCout->setVisible(true);
    }
}
