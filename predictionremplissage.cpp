#include "predictionremplissage.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDate>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QLabel>
#include <QFrame>
#include <QPushButton>
#include <QProgressBar>
#include <QGridLayout>
#include <QWidget>
#include <QFont>
#include <QPainter>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

// ============================================================
// Estimation du taux journalier de remplissage
// ============================================================
double PredictionRemplissage::estimer_taux_journalier(int idConteneur, const QString &/*typeDechet*/)
{
    // Essaie de trouver la fréquence de collecte historique via CONSOMMER
    QSqlQuery q;
    q.prepare(
        "SELECT COUNT(*), MIN(c.Date_collecte), MAX(c.Date_collecte) "
        "FROM CONSOMMER co "
        "JOIN COLLECTES c ON co.ID_collecte = c.ID_collecte "
        "WHERE co.ID_conteneur = :id"
    );
    q.bindValue(":id", idConteneur);

    if (q.exec() && q.next()) {
        int nbCollectes = q.value(0).toInt();
        if (nbCollectes >= 2) {
            QDate dateMin = q.value(1).toDate();
            QDate dateMax = q.value(2).toDate();
            int joursTotal = dateMin.daysTo(dateMax);
            if (joursTotal > 0) {
                // Fréquence = nbCollectes / joursTotal → on en déduit que la collecte a lieu
                // quand le conteneur est plein, donc taux = 1 / (joursTotal/(nbCollectes-1))
                double joursParCycle = (double)joursTotal / (double)(nbCollectes - 1);
                double taux = 1.0 / joursParCycle;
                // Clamp entre 1% et 25% par jour
                return qBound(0.01, taux, 0.25);
            }
        }
    }

    // Pas d'historique → taux par défaut selon le type de propriété
    // On va chercher le type de propriété du conteneur
    QSqlQuery q2;
    q2.prepare("SELECT Type_propriete FROM CONTENEURS WHERE ID_conteneur = :id");
    q2.bindValue(":id", idConteneur);
    if (q2.exec() && q2.next()) {
        QString type = q2.value(0).toString().toLower();
        if (type == "public")  return 0.12; // 12% par jour → plein en ~8 jours
        if (type == "privé")   return 0.07; // 7% par jour  → plein en ~14 jours
    }
    return 0.09; // valeur par défaut : ~11 jours
}

// ============================================================
// Calcul des prédictions
// ============================================================
QList<ConteneurPrediction> PredictionRemplissage::calculerPredictions()
{
    QList<ConteneurPrediction> liste;
    QDate aujourd_hui = QDate::currentDate();

    QSqlQuery query;
    if (!query.exec(
        "SELECT ID_conteneur, Capacite, Adresse_complete, Etat, "
        "Type_propriete, Date_derniere_collecte "
        "FROM CONTENEURS ORDER BY ID_conteneur"
    )) {
        qDebug() << "PredictionRemplissage::calculerPredictions error:" << query.lastError().text();
        return liste;
    }

    while (query.next()) {
        ConteneurPrediction pred;
        pred.id           = query.value(0).toInt();
        pred.capacite     = query.value(1).toDouble();
        pred.adresse      = query.value(2).toString();
        pred.etat         = query.value(3).toString();
        pred.typePropriete= query.value(4).toString();

        // Calcul des jours écoulés depuis la dernière collecte
        QDate derniere = query.value(5).toDate();
        if (!derniere.isValid()) {
            // Si pas de date, on suppose que le conteneur vient d'être collecté
            derniere = aujourd_hui.addDays(-3);
        }
        pred.joursDepuisCollecte = derniere.daysTo(aujourd_hui);
        if (pred.joursDepuisCollecte < 0) pred.joursDepuisCollecte = 0;

        // Estimation du taux journalier
        double tauxJournalier = estimer_taux_journalier(pred.id, "");

        // Taux actuel estimé
        pred.tauxRemplissageEstime = qMin(1.0, tauxJournalier * pred.joursDepuisCollecte);

        // Jours restants avant remplissage complet
        double reste = 1.0 - pred.tauxRemplissageEstime;
        if (tauxJournalier > 0.0 && reste > 0.0)
            pred.joursAvantPlein = (int)(reste / tauxJournalier);
        else
            pred.joursAvantPlein = 0;

        // Niveau d'alerte
        if (pred.tauxRemplissageEstime >= 0.85 || pred.joursAvantPlein <= 1)
            pred.niveauAlerte = "Critique";
        else if (pred.tauxRemplissageEstime >= 0.60 || pred.joursAvantPlein <= 4)
            pred.niveauAlerte = "Attention";
        else
            pred.niveauAlerte = "OK";

        liste.append(pred);
    }

    // Trier : Critique d'abord, puis Attention, puis OK
    std::sort(liste.begin(), liste.end(), [](const ConteneurPrediction &a, const ConteneurPrediction &b) {
        auto rank = [](const QString &s) {
            if (s == "Critique") return 0;
            if (s == "Attention") return 1;
            return 2;
        };
        return rank(a.niveauAlerte) < rank(b.niveauAlerte);
    });

    return liste;
}

// ============================================================
// Affichage du dashboard
// ============================================================
void PredictionRemplissage::afficherPredictions(QWidget *parent)
{
    QList<ConteneurPrediction> predictions = calculerPredictions();

    // ── Comptages résumé ────────────────────────────────────────
    int nbCritique = 0, nbAttention = 0, nbOk = 0;
    for (auto &p : predictions) {
        if (p.niveauAlerte == "Critique")  nbCritique++;
        else if (p.niveauAlerte == "Attention") nbAttention++;
        else nbOk++;
    }

    // ── Fenêtre principale ──────────────────────────────────────
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("🔮 Prédiction du Remplissage des Conteneurs");
    dlg->setMinimumSize(920, 700);
    dlg->resize(960, 740);
    dlg->setStyleSheet(R"(
        QDialog {
            background: qlineargradient(x1:0, y1:0, x2:0, y2:1,
                stop:0 #0F1923, stop:1 #1A2E3D);
        }
        QScrollArea { background: transparent; border: none; }
        QScrollBar:vertical {
            background: rgba(255,255,255,0.05);
            width: 6px; border-radius: 3px;
        }
        QScrollBar::handle:vertical {
            background: rgba(100,180,255,0.3);
            border-radius: 3px; min-height: 30px;
        }
        QScrollBar::add-line, QScrollBar::sub-line { background: none; }
    )");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(24, 24, 24, 24);
    mainLay->setSpacing(18);

    // ── Header ──────────────────────────────────────────────────
    QFrame *headerFrame = new QFrame();
    headerFrame->setStyleSheet(R"(
        QFrame {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #0D3349, stop:1 #1B5E82);
            border-radius: 16px;
            border: 1px solid rgba(100,200,255,0.2);
        }
    )");
    headerFrame->setFixedHeight(88);
    QHBoxLayout *headerLay = new QHBoxLayout(headerFrame);
    headerLay->setContentsMargins(24, 0, 24, 0);

    QVBoxLayout *titleLay = new QVBoxLayout();
    QLabel *titleLbl = new QLabel("🔮  Prédiction de Remplissage");
    titleLbl->setStyleSheet(
        "font-size: 22px; font-weight: 800; color: #E0F4FF; "
        "background: transparent; letter-spacing: 0.5px;"
    );
    QLabel *subLbl = new QLabel("Estimation intelligente basée sur l'historique des collectes");
    subLbl->setStyleSheet(
        "font-size: 12px; color: rgba(160,210,255,0.75); background: transparent;"
    );
    titleLay->addWidget(titleLbl);
    titleLay->addWidget(subLbl);
    titleLay->setSpacing(2);
    headerLay->addLayout(titleLay);
    headerLay->addStretch();

    QLabel *dateLbl = new QLabel("📅  " + QDate::currentDate().toString("dd MMMM yyyy"));
    dateLbl->setStyleSheet(
        "font-size: 13px; font-weight: 600; color: rgba(160,210,255,0.8); background: transparent;"
    );
    headerLay->addWidget(dateLbl);
    mainLay->addWidget(headerFrame);

    // ── KPI Row ─────────────────────────────────────────────────
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(14);

    struct KPI { QString icon; QString value; QString label; QString bg; QString border; };
    QList<KPI> kpis = {
        {"🗑️",  QString::number(predictions.size()), "Total conteneurs",  "#112233", "#2C5F7C"},
        {"🔴",  QString::number(nbCritique),          "Critique (≥85%)",   "#1F0A0A", "#C0392B"},
        {"🟡",  QString::number(nbAttention),         "Attention (≥60%)",  "#1F1400", "#E67E22"},
        {"🟢",  QString::number(nbOk),                "Niveau OK",         "#091A0E", "#27AE60"},
    };

    for (auto &k : kpis) {
        QFrame *card = new QFrame();
        card->setFixedHeight(86);
        card->setStyleSheet(QString(
            "QFrame { background: %1; border-radius: 14px; "
            "border: 1px solid %2; }"
        ).arg(k.bg, k.border));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(18, 12, 18, 12); cl->setSpacing(2);
        QLabel *vl = new QLabel(k.icon + "  " + k.value);
        vl->setStyleSheet("font-size: 24px; font-weight: 800; color: #E8F4FF; background: transparent;");
        QLabel *ll = new QLabel(k.label);
        ll->setStyleSheet("font-size: 11px; color: rgba(160,210,255,0.7); background: transparent;");
        cl->addWidget(vl); cl->addWidget(ll);
        kpiRow->addWidget(card);
    }
    mainLay->addLayout(kpiRow);

    // ── Séparateur + titre liste ─────────────────────────────────
    QLabel *listTitle = new QLabel("  📋  Détail par conteneur — trié par urgence");
    listTitle->setStyleSheet(
        "font-size: 13px; font-weight: 700; color: rgba(160,210,255,0.85); "
        "background: transparent; padding: 4px 0;"
    );
    mainLay->addWidget(listTitle);

    // ── Zone scrollable ─────────────────────────────────────────
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);
    scroll->setStyleSheet("background: transparent;");

    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background: transparent;");
    QVBoxLayout *scrollLay = new QVBoxLayout(scrollContent);
    scrollLay->setContentsMargins(0, 0, 8, 0);
    scrollLay->setSpacing(10);

    if (predictions.isEmpty()) {
        QLabel *empty = new QLabel("Aucun conteneur trouvé dans la base de données.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet("font-size: 14px; color: rgba(160,210,255,0.5); padding: 40px;");
        scrollLay->addWidget(empty);
    }

    for (const ConteneurPrediction &p : predictions) {
        // Couleurs selon le niveau d'alerte
        QString borderColor, barColor, badgeBg, badgeText;
        if (p.niveauAlerte == "Critique") {
            borderColor = "#C0392B"; barColor = "#E74C3C";
            badgeBg = "rgba(192,57,43,0.25)"; badgeText = "#FF7070";
        } else if (p.niveauAlerte == "Attention") {
            borderColor = "#E67E22"; barColor = "#F39C12";
            badgeBg = "rgba(230,126,34,0.2)"; badgeText = "#FFB347";
        } else {
            borderColor = "#27AE60"; barColor = "#2ECC71";
            badgeBg = "rgba(39,174,96,0.15)"; badgeText = "#5EE89A";
        }

        QFrame *card = new QFrame();
        card->setFixedHeight(110);
        card->setStyleSheet(QString(R"(
            QFrame {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                    stop:0 rgba(20,40,60,0.95), stop:1 rgba(15,28,42,0.95));
                border-radius: 14px;
                border-left: 4px solid %1;
                border-top: 1px solid rgba(255,255,255,0.07);
                border-right: 1px solid rgba(255,255,255,0.04);
                border-bottom: 1px solid rgba(255,255,255,0.04);
            }
        )").arg(borderColor));

        QHBoxLayout *cardLay = new QHBoxLayout(card);
        cardLay->setContentsMargins(20, 14, 20, 14);
        cardLay->setSpacing(18);

        // ── Colonne gauche : ID + adresse ────────────────────────
        QVBoxLayout *leftCol = new QVBoxLayout();
        leftCol->setSpacing(4);
        leftCol->setContentsMargins(0,0,0,0);

        QHBoxLayout *idRow = new QHBoxLayout();
        idRow->setSpacing(8);
        QLabel *idLbl = new QLabel(QString("🗑️ #%1").arg(p.id));
        idLbl->setStyleSheet("font-size: 14px; font-weight: 800; color: #B8D8F0; background: transparent;");
        QLabel *typeLbl = new QLabel(p.typePropriete);
        typeLbl->setStyleSheet(QString(
            "font-size: 10px; font-weight: 600; color: rgba(160,210,255,0.7); "
            "background: rgba(44,95,124,0.3); border-radius: 4px; padding: 2px 6px;"
        ));
        idRow->addWidget(idLbl); idRow->addWidget(typeLbl); idRow->addStretch();
        leftCol->addLayout(idRow);

        QString adresse = p.adresse.length() > 38
            ? p.adresse.left(35) + "..."
            : p.adresse;
        QLabel *adrLbl = new QLabel("📍 " + adresse);
        adrLbl->setStyleSheet("font-size: 11px; color: rgba(160,210,255,0.55); background: transparent;");
        leftCol->addWidget(adrLbl);

        QLabel *joursLbl = new QLabel(QString("⏱ Dernière collecte il y a %1 jour(s)")
                                          .arg(p.joursDepuisCollecte));
        joursLbl->setStyleSheet("font-size: 10px; color: rgba(160,210,255,0.4); background: transparent;");
        leftCol->addWidget(joursLbl);
        leftCol->addStretch();

        cardLay->addLayout(leftCol, 3);

        // ── Colonne centrale : barre de progression ──────────────
        QVBoxLayout *midCol = new QVBoxLayout();
        midCol->setSpacing(6);
        midCol->setContentsMargins(0,0,0,0);

        QHBoxLayout *pctRow = new QHBoxLayout();
        QLabel *pctLbl = new QLabel("Taux estimé");
        pctLbl->setStyleSheet("font-size: 10px; color: rgba(160,210,255,0.5); background: transparent;");
        QLabel *pctVal = new QLabel(QString("%1%").arg((int)(p.tauxRemplissageEstime * 100)));
        pctVal->setStyleSheet("font-size: 13px; font-weight: 800; color: #E0F4FF; background: transparent;");
        pctRow->addWidget(pctLbl); pctRow->addStretch(); pctRow->addWidget(pctVal);
        midCol->addLayout(pctRow);

        QProgressBar *bar = new QProgressBar();
        bar->setRange(0, 100);
        bar->setValue((int)(p.tauxRemplissageEstime * 100));
        bar->setTextVisible(false);
        bar->setFixedHeight(12);
        bar->setStyleSheet(QString(R"(
            QProgressBar {
                background: rgba(255,255,255,0.08);
                border-radius: 6px;
                border: none;
            }
            QProgressBar::chunk {
                background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                    stop:0 %1, stop:1 %2);
                border-radius: 6px;
            }
        )").arg(barColor, (p.niveauAlerte == "Critique") ? "#FF2D55" :
                          (p.niveauAlerte == "Attention") ? "#FFD60A" : "#34C759"));
        midCol->addWidget(bar);

        QLabel *capLbl = new QLabel(QString("Capacité : %1 L").arg((int)p.capacite));
        capLbl->setStyleSheet("font-size: 10px; color: rgba(160,210,255,0.35); background: transparent;");
        midCol->addWidget(capLbl);
        midCol->addStretch();

        cardLay->addLayout(midCol, 4);

        // ── Colonne droite : prédiction ──────────────────────────
        QVBoxLayout *rightCol = new QVBoxLayout();
        rightCol->setSpacing(6);
        rightCol->setContentsMargins(0,0,0,0);
        rightCol->setAlignment(Qt::AlignCenter);

        // Badge alerte
        QLabel *alertBadge = new QLabel(
            (p.niveauAlerte == "Critique") ? "🔴  CRITIQUE" :
            (p.niveauAlerte == "Attention") ? "🟡  ATTENTION" : "🟢  OK"
        );
        alertBadge->setAlignment(Qt::AlignCenter);
        alertBadge->setStyleSheet(QString(
            "font-size: 11px; font-weight: 800; color: %1; "
            "background: %2; border-radius: 8px; padding: 4px 12px;"
        ).arg(badgeText, badgeBg));
        rightCol->addWidget(alertBadge);

        QString predText, predSubtext;
        if (p.tauxRemplissageEstime >= 1.0 || p.joursAvantPlein <= 0) {
            predText    = "PLEIN";
            predSubtext = "Collecte requise !";
        } else if (p.joursAvantPlein == 1) {
            predText    = "1 jour";
            predSubtext = "Collecte demain";
        } else {
            predText    = QString("%1 j").arg(p.joursAvantPlein);
            predSubtext = "avant remplissage";
        }

        QLabel *predLbl = new QLabel(predText);
        predLbl->setAlignment(Qt::AlignCenter);
        predLbl->setStyleSheet(QString(
            "font-size: 22px; font-weight: 900; color: %1; background: transparent;"
        ).arg(badgeText));
        rightCol->addWidget(predLbl);

        QLabel *predSub = new QLabel(predSubtext);
        predSub->setAlignment(Qt::AlignCenter);
        predSub->setStyleSheet("font-size: 10px; color: rgba(160,210,255,0.45); background: transparent;");
        rightCol->addWidget(predSub);

        cardLay->addLayout(rightCol, 2);

        scrollLay->addWidget(card);
    }

    scrollLay->addStretch();
    scroll->setWidget(scrollContent);
    mainLay->addWidget(scroll);

    // ── Bouton Fermer ────────────────────────────────────────────
    QPushButton *closeBtn = new QPushButton("✕   Fermer");
    closeBtn->setFixedHeight(46);
    closeBtn->setStyleSheet(R"(
        QPushButton {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #0D3349, stop:1 #1B5E82);
            color: #A0D2FF;
            font-size: 14px; font-weight: 700;
            border: 1px solid rgba(100,180,255,0.25);
            border-radius: 10px;
            letter-spacing: 0.5px;
        }
        QPushButton:hover {
            background: qlineargradient(x1:0,y1:0,x2:1,y2:0,
                stop:0 #1B4F6E, stop:1 #2C7AAA);
            border: 1px solid rgba(100,180,255,0.5);
            color: #E0F4FF;
        }
        QPushButton:pressed { background: #0D3349; }
    )");
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}
