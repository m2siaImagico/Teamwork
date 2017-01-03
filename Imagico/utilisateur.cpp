#include "utilisateur.h"
#include<QString>

Utilisateur::Utilisateur()
{
 _Login = "admin test";
}



Utilisateur::Utilisateur(const QString &login)
{
    _Login = login;
}

QString Utilisateur:: getLoginConnect() const
{
    return _Login;
}

QString Utilisateur::getMotDePasseConnect() const
{
    return _MotDepasse;
}

QString Utilisateur::getTypeConnect() const
{
    return _TypeUser;
}

void Utilisateur::setLoginConnect(QString login)
{
    _Login = login;
}

void Utilisateur::setMotDePasseConnect(QString MotDePasse)
{
    _MotDepasse = MotDePasse;
}

void Utilisateur::setTypeConnect(QString Type)
{
    _TypeUser = Type;
}
