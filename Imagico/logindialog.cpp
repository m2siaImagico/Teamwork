#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include<iostream>

using namespace std;

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    _user = new Utilisateur("admin");
}

Utilisateur LoginDialog::getUser() const
{
    return *_user;
}

LoginDialog::~LoginDialog()
{
    cout<<endl<<"destructeur Login"<<endl;
    delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{

   // _utilisateurConnecte->setLoginConnect(ui->loginlineEdit->text());
    _user->setLoginConnect(ui->loginlineEdit->text());
    _user->setMotDePasseConnect(ui->ModedePasselineEdit->text());

      if (ui->loginlineEdit->text() == "admin" && ui->ModedePasselineEdit->text()=="0000" ||
            ui->loginlineEdit->text() == "user" && ui->ModedePasselineEdit->text()=="0000")
    {
         accept();
    }else
    {

        QMessageBox::critical(this,"Authentification.","Le login ou le mot de passe est incorrecte");
                return;
    }
}

void LoginDialog::on_buttonBox_rejected()
{
    quick_exit(-1);
}
