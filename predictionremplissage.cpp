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
#include <QToolTip>
#include <QtMath>

// ============================================================
//  Helpers statiques
// ============================================================

double PredictionRemplissage::facteur_zone(const QString &zone)
{
    QString z = zone.toLower().trimmed();
    if (z == "centre")      return 1.5;
    if (z == "industriel")  return 0.8;
    return 1.0;
}

double PredictionRemplissage::facteur_capacite(double capacite)
{
    if (capacite < 100.0)    return 1.30;
    if (capacite < 500.0)    return 1.10;
    if (capacite < 1500.0)   return 1.00;
    return 0.85;
}

QString PredictionRemplissage::zoneLabel(const QString &zone)
{
    QString z = zone.toLower().trimmed();
    if (z == "centre")      return "🏙️ Centre";
    if (z == "industriel")  return "🏭 Industriel";
    return "🏘️ Résidentiel";
}

QString PredictionRemplissage::zoneCouleur(const QString &zone)
{
    QString z = zone.toLower().trimmed();
    if (z == "centre")      return "#7C3AED";   // violet
    if (z == "industriel")  return "#D97706";   // amber
    return "#2C5F7C";                            // bleu app (résidentiel)
}

// ============================================================
//  Estimation du taux journalier de BASE
// ============================================================
double PredictionRemplissage::estimer_taux_base(int idConteneur,
                                                const QString &typePropriete) const
{
    QSqlQuery q;
    q.prepare(
        "SELECT COUNT(*), MIN(c.Date_collecte), MAX(c.Date_collecte) "
        "FROM CONSOMMER co "
        "JOIN COLLECTES c ON co.ID_collecte = c.ID_collecte "
        "WHERE co.ID_conteneur = :id"
        );
    q.bindValue(":id", idConteneur);

    if (q.exec() && q.next()) {
        int    nbCollectes = q.value(0).toInt();
        QDate  dateMin     = q.value(1).toDate();
        QDate  dateMax     = q.value(2).toDate();
        int    joursTotal  = dateMin.daysTo(dateMax);

        if (nbCollectes >= 2 && joursTotal > 0) {
            double joursParCycle = (double)joursTotal / (double)(nbCollectes - 1);
            double taux = 1.0 / joursParCycle;
            return qBound(0.01, taux, 0.25);
        }
    }

    QString tp = typePropriete.toLower().trimmed();
    if (tp.contains("public"))  return 0.12;
    if (tp.contains("priv"))    return 0.07;
    return 0.09;
}

// ============================================================
//  Calcul des prédictions
// ============================================================
QList<ConteneurPrediction> PredictionRemplissage::calculerPredictions()
{
    QList<ConteneurPrediction> liste;
    const QDate aujourd_hui = QDate::currentDate();

    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_conteneur, Capacite, Adresse_complete, Etat, "
            "Type_propriete, Date_derniere_collecte, NVL(Zone,'residentiel') "
            "FROM CONTENEURS ORDER BY ID_conteneur"
            )) {
        qDebug() << "PredictionRemplissage::calculerPredictions error:"
                 << query.lastError().text();
        return liste;
    }

    while (query.next()) {
        ConteneurPrediction pred;
        pred.id            = query.value(0).toInt();
        pred.capacite      = query.value(1).toDouble();
        pred.adresse       = query.value(2).toString();
        pred.etat          = query.value(3).toString();
        pred.typePropriete = query.value(4).toString();
        pred.zone          = query.value(6).toString();

        QDate derniere = query.value(5).toDate();
        if (!derniere.isValid())
            derniere = aujourd_hui.addDays(-3);
        pred.joursDepuisCollecte = qMax(0, (int)derniere.daysTo(aujourd_hui));

        double tauxBase      = estimer_taux_base(pred.id, pred.typePropriete);
        pred.facteurZone     = facteur_zone(pred.zone);
        pred.facteurCapacite = facteur_capacite(pred.capacite);
        pred.tauxJournalier  = qBound(0.01,
                                     tauxBase * pred.facteurZone * pred.facteurCapacite,
                                     0.50);

        pred.tauxRemplissageEstime = qMin(1.0,
                                          pred.tauxJournalier * pred.joursDepuisCollecte);

        double resteACombler = 1.0 - pred.tauxRemplissageEstime;
        if (pred.tauxJournalier > 0.0 && resteACombler > 0.0)
            pred.joursAvantPlein = qMax(0, (int)(resteACombler / pred.tauxJournalier));
        else
            pred.joursAvantPlein = 0;

        if (pred.tauxRemplissageEstime >= 0.85 || pred.joursAvantPlein <= 1)
            pred.niveauAlerte = "Critique";
        else if (pred.tauxRemplissageEstime >= 0.60 || pred.joursAvantPlein <= 4)
            pred.niveauAlerte = "Attention";
        else
            pred.niveauAlerte = "OK";

        liste.append(pred);
    }

    std::sort(liste.begin(), liste.end(), [](const ConteneurPrediction &a,
                                             const ConteneurPrediction &b) {
        auto rank = [](const QString &s) -> int {
            if (s == "Critique")  return 0;
            if (s == "Attention") return 1;
            return 2;
        };
        int ra = rank(a.niveauAlerte), rb = rank(b.niveauAlerte);
        return (ra != rb) ? (ra < rb) : (a.id < b.id);
    });

    return liste;
}

// ============================================================
//  Dashboard de prédiction — UI épurée et moderne
// ============================================================
void PredictionRemplissage::afficherPredictions(QWidget *parent)
{
    const QList<ConteneurPrediction> predictions = calculerPredictions();

    int nbCritique = 0, nbAttention = 0, nbOk = 0;
    for (const auto &p : predictions) {
        if      (p.niveauAlerte == "Critique")  nbCritique++;
        else if (p.niveauAlerte == "Attention") nbAttention++;
        else                                    nbOk++;
    }

    // ── Fenêtre principale ──────────────────────────────────────────
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("Prédiction du Remplissage des Conteneurs");
    dlg->setMinimumSize(980, 720);
    dlg->resize(1060, 760);

    // ── Global stylesheet ───────────────────────────────────────────
    dlg->setStyleSheet(R"(
        QDialog { background-color: #F0F4F8; }
        QScrollArea { background: transparent; border: none; }
        QScrollBar:vertical {
            background: #DDE3EA; width: 5px; border-radius: 3px; margin: 0;
        }
        QScrollBar::handle:vertical {
            background: #2C5F7C; border-radius: 3px; min-height: 24px;
        }
        QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
            background: none; height: 0;
        }
        QToolTip {
            background: #1B3A57; color: #FFFFFF;
            border: none; border-radius: 6px;
            padding: 6px 10px; font-size: 11px;
        }
    )");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(24, 24, 24, 20);
    mainLay->setSpacing(16);

    // ── Header ─────────────────────────────────────────────────────
    {
        QWidget *header = new QWidget();
        header->setFixedHeight(72);
        header->setStyleSheet(
            "QWidget { background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
            "stop:0 #1B3A57, stop:1 #2E6E8E); border-radius: 12px; }");

        QHBoxLayout *hLay = new QHBoxLayout(header);
        hLay->setContentsMargins(22, 0, 22, 0);
        hLay->setSpacing(0);

        QLabel *iconLbl = new QLabel("◈");
        iconLbl->setStyleSheet(
            "font-size:28px; color:rgba(255,255,255,0.85); background:transparent;");
        hLay->addWidget(iconLbl);
        hLay->addSpacing(14);

        QVBoxLayout *titleBlock = new QVBoxLayout();
        titleBlock->setSpacing(2);
        QLabel *titleLbl = new QLabel("Prédiction de Remplissage");
        titleLbl->setStyleSheet(
            "font-size:18px; font-weight:700; color:#FFFFFF; background:transparent;");
        QLabel *subLbl = new QLabel("Modèle basé sur l'historique · zone géographique · capacité du conteneur");
        subLbl->setStyleSheet(
            "font-size:11px; color:rgba(255,255,255,0.65); background:transparent;");
        titleBlock->addWidget(titleLbl);
        titleBlock->addWidget(subLbl);
        hLay->addLayout(titleBlock);
        hLay->addStretch();

        struct ZL { QString text; QString color; };
        for (const auto &zl : QList<ZL>{
                 { "Centre  x1.5",      "#A78BFA" },
                 { "Residentiel  x1.0", "#67C5E8" },
                 { "Industriel  x0.8",  "#FBBF24" }
             }) {
            QLabel *pill = new QLabel(zl.text);
            pill->setStyleSheet(QString(
                                    "font-size:10px; font-weight:600; color:%1;"
                                    "background:rgba(255,255,255,0.10);"
                                    "border:1px solid %1; border-radius:20px; padding:3px 10px;"
                                    ).arg(zl.color));
            pill->setToolTip("Facteur applique au taux journalier de remplissage");
            hLay->addWidget(pill);
            hLay->addSpacing(6);
        }

        mainLay->addWidget(header);
    }

    // ── KPI row ────────────────────────────────────────────────────
    {
        QHBoxLayout *kpiRow = new QHBoxLayout();
        kpiRow->setSpacing(12);

        struct KpiDef { QString icon; int count; QString label; QString accent; QString bg; };
        const QList<KpiDef> kpis = {
                                    { "●", nbCritique,                     "Critique",         "#EF4444", "#FEF2F2" },
                                    { "●", nbAttention,                    "Attention",        "#F59E0B", "#FFFBEB" },
                                    { "●", nbOk,                           "OK",               "#10B981", "#F0FDF4" },
                                    { "▦", nbCritique+nbAttention+nbOk,    "Total conteneurs", "#2C5F7C", "#F0F4F8" },
                                    };

        for (const auto &k : kpis) {
            QFrame *kcard = new QFrame();
            kcard->setFixedHeight(78);
            kcard->setStyleSheet(QString(
                                     "QFrame { background:%2; border-radius:10px; border:1px solid rgba(0,0,0,0.07); }"
                                     ).arg(k.bg));
            QHBoxLayout *kcl = new QHBoxLayout(kcard);
            kcl->setContentsMargins(16, 0, 16, 0);
            kcl->setSpacing(12);
            QLabel *dot = new QLabel(k.icon);
            dot->setStyleSheet(QString(
                                   "font-size:20px; color:%1; background:transparent;").arg(k.accent));
            QVBoxLayout *vl = new QVBoxLayout();
            vl->setSpacing(1);
            QLabel *num = new QLabel(QString::number(k.count));
            num->setStyleSheet(QString(
                                   "font-size:26px; font-weight:800; color:%1; background:transparent;"
                                   ).arg(k.accent));
            QLabel *lbl = new QLabel(k.label);
            lbl->setStyleSheet("font-size:11px; color:#64748B; background:transparent;");
            vl->addWidget(num);
            vl->addWidget(lbl);
            kcl->addWidget(dot);
            kcl->addLayout(vl);
            kcl->addStretch();
            kpiRow->addWidget(kcard);
        }
        mainLay->addLayout(kpiRow);
    }

    // ── Section label ──────────────────────────────────────────────
    {
        QLabel *secTitle = new QLabel(
            QString("  %1 conteneur(s) — tries par niveau d'alerte").arg(predictions.size()));
        secTitle->setStyleSheet(
            "font-size:11px; font-weight:600; color:#94A3B8; background:transparent;");
        mainLay->addWidget(secTitle);
    }

    // ── Scrollable list ────────────────────────────────────────────
    QScrollArea *scroll = new QScrollArea();
    scroll->setWidgetResizable(true);
    scroll->setFrameShape(QFrame::NoFrame);

    QWidget *scrollContent = new QWidget();
    scrollContent->setStyleSheet("background: transparent;");
    QVBoxLayout *scrollLay = new QVBoxLayout(scrollContent);
    scrollLay->setContentsMargins(0, 0, 8, 0);
    scrollLay->setSpacing(8);

    if (predictions.isEmpty()) {
        QLabel *empty = new QLabel("Aucun conteneur trouve dans la base de donnees.");
        empty->setAlignment(Qt::AlignCenter);
        empty->setStyleSheet(
            "font-size:14px; color:#94A3B8; padding:60px; background:transparent;");
        scrollLay->addWidget(empty);
    }

    // ── Card per container ─────────────────────────────────────────
    for (const ConteneurPrediction &p : predictions) {

        QString accentColor, barFrom, barTo, badgeBg, badgeFg, badgeText;
        if (p.niveauAlerte == "Critique") {
            accentColor = "#EF4444";
            barFrom = "#F87171"; barTo = "#DC2626";
            badgeBg = "#FEE2E2"; badgeFg = "#B91C1C"; badgeText = "CRITIQUE";
        } else if (p.niveauAlerte == "Attention") {
            accentColor = "#F59E0B";
            barFrom = "#FCD34D"; barTo = "#D97706";
            badgeBg = "#FEF3C7"; badgeFg = "#92400E"; badgeText = "ATTENTION";
        } else {
            accentColor = "#10B981";
            barFrom = "#6EE7B7"; barTo = "#059669";
            badgeBg = "#D1FAE5"; badgeFg = "#065F46"; badgeText = "OK";
        }

        const QString zoneCoul = zoneCouleur(p.zone);
        const int pct = (int)(p.tauxRemplissageEstime * 100);

        QFrame *card = new QFrame();
        card->setFixedHeight(100);
        card->setStyleSheet(QString(R"(
            QFrame {
                background: #FFFFFF;
                border-radius: 10px;
                border: 1px solid #E2E8F0;
            }
        )"));

        QHBoxLayout *cardLay = new QHBoxLayout(card);
        cardLay->setContentsMargins(0, 0, 20, 0);
        cardLay->setSpacing(0);

        // Left accent strip
        QFrame *strip = new QFrame();
        strip->setFixedWidth(5);
        strip->setStyleSheet(QString(
                                 "QFrame { background:%1; border:none;"
                                 "border-top-left-radius:10px; border-bottom-left-radius:10px; }"
                                 ).arg(accentColor));
        cardLay->addWidget(strip);
        cardLay->addSpacing(16);

        // Col A: identity
        {
            QVBoxLayout *col = new QVBoxLayout();
            col->setSpacing(4);

            QHBoxLayout *topRow = new QHBoxLayout();
            topRow->setSpacing(6);

            QLabel *idLbl = new QLabel(QString("#%1").arg(p.id));
            idLbl->setStyleSheet(
                "font-size:15px; font-weight:800; color:#1E293B; background:transparent;");

            QLabel *typeLbl = new QLabel(p.typePropriete);
            typeLbl->setStyleSheet(
                "font-size:10px; color:#64748B; background:#F1F5F9;"
                "border-radius:4px; padding:2px 8px; border:1px solid #E2E8F0;");

            QLabel *zoneLbl = new QLabel(zoneLabel(p.zone));
            zoneLbl->setStyleSheet(QString(
                                       "font-size:10px; font-weight:600; color:%1;"
                                       "border:1px solid %1; border-radius:4px; padding:2px 8px; background:transparent;"
                                       ).arg(zoneCoul));
            zoneLbl->setToolTip(QString(
                                    "Zone : %1\nFacteur zone : x%2\nFacteur capacite : x%3\nTaux final : %4%%/j"
                                    ).arg(p.zone)
                                    .arg(p.facteurZone, 0, 'f', 1)
                                    .arg(p.facteurCapacite, 0, 'f', 2)
                                    .arg(p.tauxJournalier * 100.0, 0, 'f', 1));

            topRow->addWidget(idLbl);
            topRow->addWidget(typeLbl);
            topRow->addWidget(zoneLbl);
            topRow->addStretch();
            col->addLayout(topRow);

            QString adresse = p.adresse.length() > 44
                                  ? p.adresse.left(41) + "..." : p.adresse;
            QLabel *adrLbl = new QLabel("  " + adresse);
            adrLbl->setStyleSheet("font-size:11px; color:#475569; background:transparent;");
            adrLbl->setToolTip(p.adresse);
            col->addWidget(adrLbl);

            QLabel *dateLbl = new QLabel(
                QString("  Derniere collecte : il y a %1 jour(s)").arg(p.joursDepuisCollecte));
            dateLbl->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
            col->addWidget(dateLbl);
            col->addStretch();
            cardLay->addLayout(col, 35);
        }

        // Divider
        {
            QFrame *div = new QFrame();
            div->setFrameShape(QFrame::VLine);
            div->setFixedWidth(1);
            div->setStyleSheet("background:#F1F5F9; border:none;");
            cardLay->addSpacing(12);
            cardLay->addWidget(div);
            cardLay->addSpacing(16);
        }

        // Col B: fill bar
        {
            QVBoxLayout *col = new QVBoxLayout();
            col->setSpacing(5);

            QHBoxLayout *labelRow = new QHBoxLayout();
            QLabel *fillLbl = new QLabel("Taux de remplissage");
            fillLbl->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
            QLabel *fillVal = new QLabel(QString("%1%").arg(pct));
            fillVal->setStyleSheet(QString(
                                       "font-size:14px; font-weight:800; color:%1; background:transparent;"
                                       ).arg(accentColor));
            labelRow->addWidget(fillLbl);
            labelRow->addStretch();
            labelRow->addWidget(fillVal);
            col->addLayout(labelRow);

            QProgressBar *bar = new QProgressBar();
            bar->setRange(0, 100);
            bar->setValue(pct);
            bar->setTextVisible(false);
            bar->setFixedHeight(8);
            bar->setStyleSheet(QString(R"(
                QProgressBar { background:#F1F5F9; border-radius:4px; border:none; }
                QProgressBar::chunk {
                    background: qlineargradient(x1:0,y1:0,x2:1,y2:0, stop:0 %1, stop:1 %2);
                    border-radius: 4px;
                }
            )").arg(barFrom, barTo));
            col->addWidget(bar);

            QHBoxLayout *metaRow = new QHBoxLayout();
            QLabel *capLbl = new QLabel(QString("%1 L").arg((int)p.capacite));
            capLbl->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
            QLabel *rateLbl = new QLabel(
                QString("%1%%/j").arg(p.tauxJournalier * 100.0, 0, 'f', 1));
            rateLbl->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
            rateLbl->setToolTip(QString(
                                    "Taux base x facteur zone (x%1) x facteur capacite (x%2)"
                                    ).arg(p.facteurZone, 0, 'f', 1).arg(p.facteurCapacite, 0, 'f', 2));
            metaRow->addWidget(capLbl);
            metaRow->addStretch();
            metaRow->addWidget(rateLbl);
            col->addLayout(metaRow);
            col->addStretch();
            cardLay->addLayout(col, 40);
        }

        // Divider
        {
            QFrame *div = new QFrame();
            div->setFrameShape(QFrame::VLine);
            div->setFixedWidth(1);
            div->setStyleSheet("background:#F1F5F9; border:none;");
            cardLay->addSpacing(12);
            cardLay->addWidget(div);
            cardLay->addSpacing(16);
        }

        // Col C: prediction
        {
            QVBoxLayout *col = new QVBoxLayout();
            col->setSpacing(4);
            col->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

            QLabel *badge = new QLabel(badgeText);
            badge->setAlignment(Qt::AlignCenter);
            badge->setFixedHeight(22);
            badge->setStyleSheet(QString(
                                     "font-size:10px; font-weight:700; letter-spacing:0.8px;"
                                     "color:%1; background:%2; border-radius:4px; padding:0 10px;"
                                     ).arg(badgeFg, badgeBg));
            col->addWidget(badge, 0, Qt::AlignHCenter);

            QString predText, predSub;
            if (p.tauxRemplissageEstime >= 1.0 || p.joursAvantPlein <= 0) {
                predText = "PLEIN"; predSub = "Collecte requise";
            } else if (p.joursAvantPlein == 1) {
                predText = "1 jour"; predSub = "Collecte demain";
            } else {
                predText = QString("%1 j").arg(p.joursAvantPlein);
                predSub  = "avant remplissage";
            }

            QLabel *predLbl = new QLabel(predText);
            predLbl->setAlignment(Qt::AlignCenter);
            predLbl->setStyleSheet(QString(
                                       "font-size:24px; font-weight:900; color:%1; background:transparent;"
                                       ).arg(accentColor));
            col->addWidget(predLbl);

            QLabel *predSubLbl = new QLabel(predSub);
            predSubLbl->setAlignment(Qt::AlignCenter);
            predSubLbl->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
            col->addWidget(predSubLbl);

            cardLay->addLayout(col, 25);
        }

        scrollLay->addWidget(card);
    }

    scrollLay->addStretch();
    scroll->setWidget(scrollContent);
    mainLay->addWidget(scroll);

    // ── Footer ─────────────────────────────────────────────────────
    {
        QHBoxLayout *footRow = new QHBoxLayout();
        footRow->setSpacing(12);

        QLabel *note = new QLabel(
            "  Taux journalier = taux historique x facteur zone x facteur capacite"
            "  -  Survolez les badges de zone pour les details");
        note->setStyleSheet("font-size:10px; color:#94A3B8; background:transparent;");
        footRow->addWidget(note);
        footRow->addStretch();

        QPushButton *closeBtn = new QPushButton("  Fermer");
        closeBtn->setFixedHeight(40);
        closeBtn->setFixedWidth(120);
        closeBtn->setCursor(Qt::PointingHandCursor);
        closeBtn->setStyleSheet(R"(
            QPushButton {
                background: #1B3A57; color: #FFFFFF;
                font-size: 13px; font-weight: 600;
                border: none; border-radius: 8px;
                padding: 0 20px;
            }
            QPushButton:hover  { background: #2C5F7C; }
            QPushButton:pressed{ background: #152D45; }
        )");
        QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
        footRow->addWidget(closeBtn);

        mainLay->addLayout(footRow);
    }

    dlg->exec();
}
