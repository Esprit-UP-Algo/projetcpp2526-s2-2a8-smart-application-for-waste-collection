#ifndef CALCULE_ANCIENNETE_H
#define CALCULE_ANCIENNETE_H

#include <QWidget>
#include <QDialog>
#include <QSqlQuery>
#include <QTableWidget>
#include <QLabel>
#include <QProgressBar>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QDate>

class Calcule_anciennete
{
public:
    Calcule_anciennete();

    // Métier avancé — Ancienneté + Prime
    void calculerAncienneteEtPrime(QWidget *parent);

private:
    // Règle de calcul prime selon années
    double calculerPrime(double salaire, int annees);
};

#endif // CALCULE_ANCIENNETE_H
