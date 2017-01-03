#ifndef TRIEDIALOGFICHE_H
#define TRIEDIALOGFICHE_H

#include <QDialog>

namespace Ui {
class TrieDialogFiche;
}

class TrieDialogFiche : public QDialog
{
    Q_OBJECT

public:
    explicit TrieDialogFiche(QWidget *parent = 0);

    QString getTrieCritere() const;
    QString getTrieOrder() const;

    ~TrieDialogFiche();

private slots:
   // void on_radioButton_5_clicked();
    void on_radioTrieCroissant_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_radioTrieParNom_clicked();

    void on_radioTrieParNumero_clicked();

    void on_radioTrieDecroissant_clicked();

private:
    Ui::TrieDialogFiche *ui;
    QString _TrieCritere;
    QString _TrieOrder;
};

#endif // TRIEDIALOGFICHE_H
