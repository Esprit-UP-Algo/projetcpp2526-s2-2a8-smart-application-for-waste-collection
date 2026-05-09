#include "classificationdechet.h"
#include <QDebug>

ClassificationDechet::ClassificationDechet() {}

ClassificationDechet::ClassificationDechet(const QString &typeDechet, const QString &etat)
    : m_typeDechet(typeDechet), m_etat(etat) {}

void ClassificationDechet::setTypeDechet(const QString &type) { m_typeDechet = type; }
void ClassificationDechet::setEtat(const QString &etat)       { m_etat = etat; }

ResultatClassification ClassificationDechet::calculerResultat() const
{
    ResultatClassification r;

    // ✅ Normalisation ici, dans le .cpp, pas dans le slot
    QString type = m_typeDechet.toLower().trimmed()
                       .replace("é","e").replace("è","e");
    QString etat = m_etat.toLower().trimmed();
    bool propre  = (etat == "propre");

    // Debug dans la console Qt
    qDebug() << "[ClassificationDechet] type=" << type << "etat=" << etat;

    if (type == "plastique") {
        if (propre) {
            r.recyclable     = true;
            r.tauxReussite   = 85;
            r.recommandation = "Deposez dans le bac jaune. Flacon vide et rince.";
            r.couleur        = "vert";
        } else {
            r.recyclable     = false;
            r.tauxReussite   = 30;
            r.recommandation = "Nettoyez avant recyclage ou jetez dans le bac general.";
            r.couleur        = "rouge";
        }
    }
    else if (type == "papier") {
        if (propre) {
            r.recyclable     = true;
            r.tauxReussite   = 90;
            r.recommandation = "Excellent candidat. Evitez papier carbone ou plastifie.";
            r.couleur        = "vert";
        } else {
            r.recyclable     = false;
            r.tauxReussite   = 25;
            r.recommandation = "Papier souille non recyclable. Ordures menageres.";
            r.couleur        = "rouge";
        }
    }
    else if (type == "verre") {
        r.recyclable     = true;
        r.tauxReussite   = propre ? 95 : 80;
        r.recommandation = propre
                               ? "Taux optimal. Deposez dans le conteneur a verre."
                               : "Rincez rapidement, encore recyclable a 80%.";
        r.couleur = "vert";
    }
    else if (type == "metal" || type == "métal") {
        if (propre) {
            r.recyclable     = true;
            r.tauxReussite   = 92;
            r.recommandation = "Tres bon taux. Ecrasez les boites pour economiser la place.";
            r.couleur        = "vert";
        } else {
            r.recyclable     = true;
            r.tauxReussite   = 70;
            r.recommandation = "Recyclable mais avec pertes. Preferez le rincer avant depot.";
            r.couleur        = "vert";
        }
    }
    else {
        // Ne devrait plus jamais arriver
        r.recyclable     = false;
        r.tauxReussite   = 0;
        r.recommandation = QString("Type recu: [%1] - Verifiez la ComboBox.").arg(m_typeDechet);
        r.couleur        = "rouge";
    }

    return r;
}

QString ClassificationDechet::formatResultatHTML(const ResultatClassification &r)
{
    QString couleurHex = (r.couleur == "vert") ? "#00b894" : "#d63031";
    QString bgColor    = (r.couleur == "vert") ? "#f0fff8" : "#fff5f5";
    QString statut     = r.recyclable ? "RECYCLABLE" : "NON RECYCLABLE";
    QString icone      = r.recyclable ? "♻️" : "🚫";

    int blocs = r.tauxReussite / 10;
    QString barre = "";
    for (int i = 0; i < 10; i++) {
        QString c = (i < blocs) ? couleurHex : "#dfe6e9";
        barre += QString("<span style='color:%1;font-size:22px;'>■</span>").arg(c);
    }

    return QString(
               "<div style='font-family:Segoe UI,Arial;background:%1;padding:16px;border-radius:10px;'>"
               "<p style='font-size:20px;font-weight:bold;color:%2;margin:0 0 8px 0;'>%3 %4</p>"
               "<p style='font-size:15px;margin:0 0 6px 0;color:#2d3436;'>"
               "  <b>Taux de reussite :</b> "
               "  <span style='color:%2;font-size:22px;font-weight:bold;'>%5%</span>"
               "</p>"
               "<p style='font-size:13px;color:#636e72;margin:0 0 10px 0;'>%6</p>"
               "<p style='margin:0;'><b>Progression :</b><br>%7</p>"
               "</div>"
               ).arg(bgColor, couleurHex, icone, statut)
        .arg(r.tauxReussite)
        .arg(r.recommandation)
        .arg(barre);
}
