#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include<QString>
#include "utilisateur.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = nullptr);
    //LoginDialog();
    Utilisateur getUser() const;
    ~LoginDialog();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::LoginDialog *ui;
    Utilisateur *_user;


};

#endif // LOGINDIALOG_H
