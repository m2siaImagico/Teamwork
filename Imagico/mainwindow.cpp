#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ajouterdialogfiche.h"
#include "recherchedialogfiche.h"
#include <iostream>
#include <QDialog>
#include "QDomDocument"
#include"QDomElement"
#include"QFile"
#include"QFileDialog"
#include"QMessageBox"
#include"QTextStream"
#include"triedialogfiche.h"
#include "logindialog.h"
#include "utilisateur.h"

//QMAKE_CXXFLAGS += std=gnu++14

using namespace std;

//git test

QString _PathFile;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    QStringList  Structuredonnes {"Sources", "Titre", "Numero", "Cout", "Acces","Id"};
    ui->tableWidget->setColumnCount(Structuredonnes.size());
    ui->tableWidget->setHorizontalHeaderLabels(Structuredonnes);

    //resultat de la recherche
    ui->tableWidget_Resultat->setColumnCount(Structuredonnes.size());
    ui->tableWidget_Resultat->setHorizontalHeaderLabels(Structuredonnes);

    //authentification

    _logindialog = new LoginDialog(this);
    _logindialog->exec();
    _logindialog->setModal(true);

    ajouterUtilisateur(_logindialog->getUser());
}

void MainWindow::rechercheXML(QString Critere ="", QString NumeroRech="",
                              float ValCoutMin=0, float ValCoutMax=0)
{

    cout<<"### chemin XML  "<< _PathFile.toStdString()<<endl;

    QString NomFichier = _PathFile;
    QFile fichier(NomFichier);

   //tester si le fichier est vide, si oui alors retour
   if (NomFichier.isEmpty())
   {
       cout<<"fichier 2 vide"<<endl;
       return;
   }

   if (!fichier.open(QIODevice::ReadOnly  | QIODevice::Text))
   {
          QMessageBox::critical(this,"Erreur",fichier.errorString());
           return;
   }

   //sauvegarder le contenu du fichier xml dans une variable Domdocument

   QDomDocument doc;
   doc.setContent(&fichier);
   fichier.close();

   //Parcourir le fichier xml

   int i(0);
   auto root   = doc.firstChild().toElement(); //l'element parent "FICHESTECNIQUES"
   auto nbfils = root.firstChild().toElement();
   cout<<"tester la 1ere ligne : "<<nbfils.isNull();
   while(!nbfils.isNull())
   {
       i++;

       //on recuperer l'attribu et la sauvegarder dans une variable attr
       QString Numero = nbfils.attribute("Numero");
       //on recupere la liste des elements
       auto Source = nbfils.firstChild().toElement().text();
       auto Titre = nbfils.firstChild().nextSibling().toElement().text();
       auto Cout  = nbfils.firstChild().nextSibling().nextSibling().toElement().text();
       auto Acces  = nbfils.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();

        if (Critere =="NUMERO")
        {
            if (Numero == NumeroRech){
                AjouterFicheTechniqueResultat(FichetechniqueImage(Source, Titre, Numero,Cout, Acces));
            }
        }

        if (Critere == "MINMAX")
        {
            if(Cout.toFloat() >= ValCoutMin && Cout.toFloat() <= ValCoutMax)
            {
                AjouterFicheTechniqueResultat(FichetechniqueImage(Source,Titre,Numero,Cout,Acces));
            }
        }
       //on passe au 2ème fiche technique de l'image suivante => le 2ème parent dans notre fichier xml
       nbfils = nbfils.nextSibling().toElement();
   }
}

QString MainWindow::getTypeUser() const
{
   // cout<<"getTypeuser() : "<<endl;
    return _TypeUser;
}

void MainWindow::setTypeUser(QString type)
{
    _TypeUser = type;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOuvrir_triggered()
{

     auto NomFichier = QFileDialog::getOpenFileName(this,"I-magico Ouvrir fichier XML",
                                                    QDir::rootPath(),"Fichier XML (*.xml)");
    QFile fichier(NomFichier);

    //tester si le fichier est vide, si oui alors retour
    if (NomFichier.isEmpty())
    {
        cout<<"fichier 2 vide"<<endl;
        return;
    }

    if (!fichier.open(QIODevice::ReadOnly  | QIODevice::Text))
    {
           QMessageBox::critical(this,"Erreur",fichier.errorString());
            return;
    }

    ui->tableWidget->setRowCount(0);
    _PathFile = NomFichier;
    ui->CheminEspaceTravail->setText(NomFichier);
    //sauvegarder le contenu du fichier xml dans une variable doc

    QDomDocument doc;
    doc.setContent(&fichier);
    fichier.close();

    //Parcourir le fichier xml

    int i(0);
    auto root   = doc.firstChild().toElement(); //l'element parent "FICHESTECNIQUES"
    auto nbfils = root.firstChild().toElement();
    cout<<"tester la 1ere ligne : "<<nbfils.isNull();
    while(!nbfils.isNull())
    {
        i++;

        //on recuperer l'attribu et la sauvegarder dans une variable attr
        auto Numero = nbfils.attribute("Numero");
        auto Source = nbfils.firstChild().toElement().text();
        auto Titre = nbfils.firstChild().nextSibling().toElement().text();
        auto Cout  = nbfils.firstChild().nextSibling().nextSibling().toElement().text();
        auto Acces  = nbfils.firstChild().nextSibling().nextSibling().nextSibling().toElement().text();


        AjouterFicheTechnique(FichetechniqueImage(Source, Titre, Numero,Cout, Acces));

        //on passe au 2ème fiche technique de l'image suivante => le 2ème parent dans notre fichier xml
        nbfils = nbfils.nextSibling().toElement();
    }
}

//sauvegarder le chemin du fichier XML
QString getPathFileXML()
{
    return _PathFile;
}

void MainWindow::on_actionEnregistrer_sous_triggered()
{


    auto NomFichier = QFileDialog::getSaveFileName(this,"I-magico Enregistrer fichier XML",
                                                 QDir::rootPath(),"Fichier XML (*.xml)");

cout<<"creation fichier"<<endl;

   //sauvegarder tableau dans un fichier xml
    const auto ColTab = ui->tableWidget->rowCount();
    QDomDocument doc;
   // QDomNode Noeud = doc.createProcessingInstruction("xml","version=\"1.0\" encoding=\"UTF-8\"");

    auto root = doc.createElement("FICHESTECNIQUES");
    doc.appendChild(root);
    //doc.insertBefore(Noeud,doc.firstChild());


   for (int i =0 ; i<ColTab; ++i)
   {

       FichetechniqueImage fc(ui->tableWidget->item(i,SOURCE)->text(),
       ui->tableWidget->item(i,TITRE)->text(),
       ui->tableWidget->item(i,NUMERO)->text() ,
       ui->tableWidget->item(i,COUT)->text(),
       ui->tableWidget->item(i,ACCES)->text());

       auto fcn = doc.createElement("FicheTechnique");
       fcn.setAttribute("Numero",fc.getNumero());
       auto Etitre = doc.createElement("Titre");
       auto Esource =doc.createElement("Source");
       auto Ecout = doc.createElement("Cout");
       auto eacces = doc.createElement("Acces");

        Esource.appendChild(doc.createTextNode(fc.getSource()));
        Etitre.appendChild(doc.createTextNode(fc.getTitre()));
        Ecout.appendChild(doc.createTextNode(fc.getCout()));
        eacces.appendChild(doc.createTextNode(fc.getAcces()));

       fcn.appendChild(Esource);
       fcn.appendChild(Etitre);
       fcn.appendChild(Ecout);
       fcn.appendChild(eacces);

       root.appendChild(fcn);
   }

   //tester si le fichier est vide, si oui alors retour
    if (NomFichier.isEmpty())
    {
        cout<<"fichier vide"<<endl;
        return;
    }
   QFile fichier(NomFichier);
    if(!fichier.open(QIODevice::WriteOnly | QIODevice::Text)){
        QMessageBox::critical(this,"Erreur",fichier.errorString());
        return;
    }
  //si tout se passe bien
  QTextStream XmlOut(&fichier);
  XmlOut << doc.toString();
  //Nettoyer e fichier XML
  fichier.flush();
  //fermer le fichier XML
  fichier.close();

}

void MainWindow::on_actionQuitter_triggered()
{
    close();
}

void MainWindow::on_actionAjouter_triggered()
{
    AJouterDialogFiche fc(this);

    // sil'utilisateur click sur Annuler

    if (fc.exec() == QDialog::Rejected){
     return;
    }

    //si l'utilisateur click sur Accepter

     AjouterFicheTechnique(fc.getFicheTechnique()) ;


}

void MainWindow::on_actionSupprimer_triggered()
{
    cout<<"Totot"<<endl;
    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
}


void MainWindow::AjouterFicheTechnique(const FichetechniqueImage &ptrFcheTech)
{
    const int row = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row);

    //Ajouter une ligne


    ui->tableWidget->setItem(row,SOURCE,new QTableWidgetItem(ptrFcheTech.getSource()));
    ui->tableWidget->setItem(row,TITRE, new QTableWidgetItem(ptrFcheTech.getTitre()));
    ui->tableWidget->setItem(row, NUMERO, new QTableWidgetItem(ptrFcheTech.getNumero()));
    ui->tableWidget->setItem(row, COUT, new QTableWidgetItem(ptrFcheTech.getCout()));
    ui->tableWidget->setItem(row,ACCES, new QTableWidgetItem(ptrFcheTech.getAcces()));
}

void MainWindow::ajouterUtilisateur(const Utilisateur &ptrUtilisateur)
{
    QString m_login = ptrUtilisateur.getLoginConnect();
    QString m_password = ptrUtilisateur.getMotDePasseConnect();
    ui->Utilisateurlabel->setText("Profil utilisateur : "+ m_login + " pw : " + m_password);

}

void MainWindow::AjouterFicheTechniqueResultat(const FichetechniqueImage &ptrFcheTech)
{
    const int row = ui->tableWidget_Resultat->rowCount();
    ui->tableWidget_Resultat->insertRow(row);

    //Ajouter une ligne


    ui->tableWidget_Resultat->setItem(row,SOURCE,new QTableWidgetItem(ptrFcheTech.getSource()));
    ui->tableWidget_Resultat->setItem(row,TITRE, new QTableWidgetItem(ptrFcheTech.getTitre()));
    ui->tableWidget_Resultat->setItem(row, NUMERO, new QTableWidgetItem(ptrFcheTech.getNumero()));
    ui->tableWidget_Resultat->setItem(row, COUT, new QTableWidgetItem(ptrFcheTech.getCout()));
    ui->tableWidget_Resultat->setItem(row,ACCES, new QTableWidgetItem(ptrFcheTech.getAcces()));

}

void MainWindow::on_actionPermitons_triggered()
{
    cout<< "good bye";
    close();
}

void MainWindow::on_actionNouveau_triggered()
{
    //code c++
    cout<< "ajouter une nouvelle image"<<endl;
}

void MainWindow::on_actionRechercher_triggered()
{

    RechercheDialogFiche rc;
    QString NumeroRech;
    float ValCoutMin(0);
    float ValCoutMax(0);

    QString Critere ;

    if (rc.exec() == QDialog::Rejected){
     return;
    }

    Critere = rc.getCritereRecherche();

    //selon le critère de recherche selectionné par l'utilisateur.

    //1 - Critère de recherche par Numero de l'image
    if(Critere == "NUMERO")
    {
         NumeroRech= rc.getNumeroRecherche();
        if (NumeroRech.isEmpty())
        {
            cout<<"le texte est vide"<<endl;
            return;
        }
    }

    //2 - Critère de recherche par cout Min et Max
    if(Critere == "MINMAX")
    {
        ValCoutMin = rc.getCoutMin();
        ValCoutMax = rc.getCoutMax();
    }

    //3 - critère à défininr plus tard

    //initialiser le tablewidget
    ui->tableWidget_Resultat->setRowCount(0);

    rechercheXML(Critere,NumeroRech, ValCoutMin, ValCoutMax);

}

/*void MainWindow::on_pushButton_TrieParCout_clicked()
{
   ui->tableWidget->sortByColumn(3, Qt::DescendingOrder);
}
*/

void MainWindow::on_actionTrier_triggered()
{
    TrieDialogFiche td;


    if (td.exec() == QDialog::Rejected){
     return;
    }

    cout<<"critere de trie : "<<td.getTrieCritere().toStdString();
    cout<<endl<<"order de trie : "<<td.getTrieOrder().toStdString();
    if (td.getTrieCritere()== "NUMERO")
    {
        if (td.getTrieOrder() == "A")
        {
            ui->tableWidget->sortByColumn(3,Qt::AscendingOrder);
        }else
        {
            ui->tableWidget->sortByColumn(3,Qt::DescendingOrder);
        }
    }
}
