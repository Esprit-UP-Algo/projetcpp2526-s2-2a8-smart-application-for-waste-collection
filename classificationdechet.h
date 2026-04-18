#ifndef CLASSIFICATIONDECHET_H
#define CLASSIFICATIONDECHET_H

#include <QString>

struct ResultatClassification {
    bool    recyclable;
    int     tauxReussite;      // pourcentage 0–100
    QString recommandation;
    QString couleur;           // "vert" ou "rouge"
};

class ClassificationDechet
{
public:
    ClassificationDechet();
    ClassificationDechet(const QString &typeDechet, const QString &etat);

    // Setters
    void setTypeDechet(const QString &type);
    void setEtat(const QString &etat);

    // Logique principale
    ResultatClassification calculerResultat() const;

    // Utilitaire
    static QString formatResultatHTML(const ResultatClassification &r);

private:
    QString m_typeDechet;  // "Plastique", "Papier", "Verre", "Métal"
    QString m_etat;        // "Propre", "Sale"
};

#endif // CLASSIFICATIONDECHET_H
