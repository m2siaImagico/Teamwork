#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QDialog>
#include<iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");

    MainWindow w;
   /* LoginDialog win;

    if (win.exec() != QDialog::Accepted)
    {
        cout<<"erreur"<<endl;
        return (-1);
    }
*/
    w.show();
    return a.exec();
}
