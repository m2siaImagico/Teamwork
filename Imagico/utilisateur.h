#ifndef UTILISATEUR_H
#define UTILISATEUR_H
#include<QString>

class Utilisateur
{
public:
    Utilisateur();
    Utilisateur(const QString &login = "");

    QString getLoginConnect() const;
    QString getMotDePasseConnect() const;
    QString getTypeConnect() const;

    void setLoginConnect(QString Login);
    void setMotDePasseConnect(QString MotDePasse);
    void setTypeConnect(QString Type);

private :
    QString _Login;
    QString _MotDepasse;
    QString _TypeUser;

};

#endif // UTILISATEUR_H
