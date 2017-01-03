#include "triedialogfiche.h"
#include "ui_triedialogfiche.h"

TrieDialogFiche::TrieDialogFiche(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TrieDialogFiche)
{
    ui->setupUi(this);
}

QString TrieDialogFiche::getTrieCritere() const
{
    return _TrieCritere;
}

QString TrieDialogFiche::getTrieOrder() const
{
    return _TrieOrder;
}

TrieDialogFiche::~TrieDialogFiche()
{
    delete ui;
}


void TrieDialogFiche::on_radioTrieCroissant_clicked()
{
    if (ui->radioTrieCroissant->isChecked()== true)
    {
        _TrieOrder = "A";
    }
}

void TrieDialogFiche::on_buttonBox_rejected()
{

    reject();
}

void TrieDialogFiche::on_buttonBox_accepted()
{

    accept();
}

void TrieDialogFiche::on_radioTrieParNom_clicked()
{

    _TrieCritere = "NOM";
}

void TrieDialogFiche::on_radioTrieParNumero_clicked()
{
    if (ui->radioTrieParNumero->isChecked()==true)
    {
        _TrieCritere = "NUMERO";
    }
}

void TrieDialogFiche::on_radioTrieDecroissant_clicked()
{
    if (ui->radioTrieDecroissant->isChecked() == true)
    {
        _TrieOrder = "Z";
    }
}
