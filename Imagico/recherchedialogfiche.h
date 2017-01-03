#ifndef RECHERCHEDIALOGFICHE_H
#define RECHERCHEDIALOGFICHE_H

#include <QDialog>
#include "fichetechniqueimage.h"

namespace Ui {
class RechercheDialogFiche;
}

class RechercheDialogFiche : public QDialog
{
    Q_OBJECT

public:
    explicit RechercheDialogFiche(QWidget *parent = nullptr);
    QString getNumeroRecherche() const;
    float getCoutMin() const;
    float getCoutMax() const;
    QString getCritereRecherche() const;

    ~RechercheDialogFiche();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_groupBox_clicked();

    void on_radioButtonNumero_clicked();

    void on_radioButtonCout_clicked();

private:
    Ui::RechercheDialogFiche *ui;
    FichetechniqueImage _ficheTech;
    QString _NumeroRecherche;
    float _CoutMin;
    float _CoutMax;
    QString _CritereDeRecherche;

    //Critères de recherches
    enum{
        NUMERO,
        MINMAX,
        NOM,
        SOURCE,
        AUTRE,
    };

};

#endif // RECHERCHEDIALOGFICHE_H
