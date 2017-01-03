#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "fichetechniqueimage.h"
#include "logindialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    //methode rechercher dans un fichier xml
    QString getPathFileXML();
    void rechercheXML(QString Critere, QString NumeroRech, float ValCoutMin, float ValCoutMax);
    QString getTypeUser() const;
    void setTypeUser(QString type);
    ~MainWindow();

private slots:

    //le Menu principal

    void on_actionOuvrir_triggered();
    void on_actionEnregistrer_sous_triggered();
    void on_actionQuitter_triggered();
    void on_actionAjouter_triggered();
    void on_actionSupprimer_triggered();
    void on_actionPermitons_triggered();
    void on_actionNouveau_triggered();
    void on_actionRechercher_triggered();
    void on_actionTrier_triggered();

private:

    enum{
        SOURCE,
        TITRE ,
        NUMERO ,
        COUT ,
        ACCES
    };

    Ui::MainWindow *ui;
    void AjouterFicheTechnique(const FichetechniqueImage &ptrFcheTech);
    void ajouterUtilisateur(const Utilisateur &ptrUtilisateur);

    //ajouter une fiche dans la tablewifget resultat
    void AjouterFicheTechniqueResultat(const FichetechniqueImage &ptrFcheTech);

    QString _TypeUser;
    LoginDialog *_logindialog;
    Utilisateur *_utilisateur;

};

#endif // MAINWINDOW_H
