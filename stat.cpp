#include "stat.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QFrame>

// ================================================================
// === MODULE EMPLOYE — MARYEM ====================================
// ================================================================

void EmployeStat::calculer()
{
    QSqlQuery q;

    if (q.exec("SELECT COUNT(*) FROM EMPLOYES") && q.next())
        totalEmployes = q.value(0).toInt();

    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Email IS NOT NULL") && q.next())
        withEmail = q.value(0).toInt();

    if (q.exec("SELECT COUNT(*) FROM EMPLOYES WHERE Poste IS NOT NULL") && q.next())
        postesDefinis = q.value(0).toInt();

    auto countService = [&](const QString &s) -> int {
        q.prepare("SELECT COUNT(*) FROM EMPLOYES WHERE UPPER(Service) = UPPER(:s)");
        q.bindValue(":s", s);
        if (q.exec() && q.next()) return q.value(0).toInt();
        return 0;
    };
    serviceIT      = countService("IT");
    serviceRH      = countService("RH");
    serviceFinance = countService("Finance");

    if (q.exec("SELECT AVG(Salaire) FROM EMPLOYES") && q.next())
        salaireMoyen = q.value(0).toDouble();
    if (q.exec("SELECT MAX(Salaire) FROM EMPLOYES") && q.next())
        salaireMax = q.value(0).toDouble();
    if (q.exec("SELECT MIN(Salaire) FROM EMPLOYES") && q.next())
        salaireMin = q.value(0).toDouble();
}

void EmployeStat::afficherStatistiques(QWidget *parent)
{
    calculer();

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📊 Statistiques des Employés");
    dlg->setFixedSize(780, 580);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // ── Titre ────────────────────────────────────────────────────
    QLabel *title = new QLabel("📊 Tableau de Bord — Statistiques Employés");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Fabrique de carte KPI ─────────────────────────────────────
    auto makeKPI = [](const QString &icon, const QString &value,
                      const QString &label, const QString &color) -> QFrame* {
        QFrame *card = new QFrame();
        card->setFixedHeight(90);
        card->setStyleSheet(
            QString("QFrame { background-color:%1; border-radius:12px; }").arg(color)
            );
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(14, 10, 14, 10);
        cl->setSpacing(2);
        QLabel *ico = new QLabel(icon + "  " + value);
        ico->setStyleSheet("font-size:22px; font-weight:bold; color:white; background:transparent;");
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        cl->addWidget(ico);
        cl->addWidget(lbl);
        return card;
    };

    // ── Ligne 1 : KPI effectif ────────────────────────────────────
    QHBoxLayout *kpiRow = new QHBoxLayout();
    kpiRow->setSpacing(12);
    kpiRow->addWidget(makeKPI("👥", QString::number(totalEmployes), "Total employés",  "#2C5F7C"));
    kpiRow->addWidget(makeKPI("📧", QString::number(withEmail),     "Email défini",    "#27AE60"));
    kpiRow->addWidget(makeKPI("💼", QString::number(postesDefinis), "Postes définis",  "#E67E22"));
    mainLay->addLayout(kpiRow);

    // ── Ligne 2 : Stats salaires ──────────────────────────────────
    QFrame *salaireCard = new QFrame();
    salaireCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QHBoxLayout *salLay = new QHBoxLayout(salaireCard);
    salLay->setContentsMargins(20, 14, 20, 14);

    auto makeSalStat = [](const QString &lbl, const QString &val) -> QVBoxLayout* {
        QVBoxLayout *vl = new QVBoxLayout();
        QLabel *v = new QLabel(val);
        v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:20px; font-weight:bold; color:#2C5F7C;");
        QLabel *l = new QLabel(lbl);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:11px; color:#6B7280;");
        vl->addWidget(v);
        vl->addWidget(l);
        return vl;
    };

    QLabel *salTitle = new QLabel("💰 Salaire (DT)");
    salTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    salLay->addWidget(salTitle);
    salLay->addStretch();
    salLay->addLayout(makeSalStat("Moyenne", QString::number(salaireMoyen, 'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeSalStat("Maximum", QString::number(salaireMax,   'f', 2)));
    salLay->addSpacing(30);
    salLay->addLayout(makeSalStat("Minimum", QString::number(salaireMin,   'f', 2)));
    mainLay->addWidget(salaireCard);

    // ── Ligne 3 : Répartition par service ────────────────────────
    QFrame *serviceCard = new QFrame();
    serviceCard->setStyleSheet("QFrame { background:white; border-radius:12px; }");
    QVBoxLayout *serviceLay = new QVBoxLayout(serviceCard);
    serviceLay->setContentsMargins(20, 14, 20, 14);
    serviceLay->setSpacing(10);

    QLabel *serviceTitle = new QLabel("🏢 Répartition par Service");
    serviceTitle->setStyleSheet("font-size:13px; font-weight:bold; color:#374151;");
    serviceLay->addWidget(serviceTitle);

    struct ServiceStat { QString name; int count; QString color; };
    QList<ServiceStat> services = {
                                   {"IT",      serviceIT,      "#3B82F6"},
                                   {"RH",      serviceRH,      "#10B981"},
                                   {"Finance", serviceFinance, "#F59E0B"},
                                   };

    QHBoxLayout *serviceRow = new QHBoxLayout();
    serviceRow->setSpacing(16);
    for (auto &s : services) {
        QFrame *sCard = new QFrame();
        sCard->setStyleSheet(
            QString("QFrame { background:%1; border-radius:10px; }").arg(s.color)
            );
        sCard->setFixedHeight(64);
        QVBoxLayout *scl = new QVBoxLayout(sCard);
        scl->setContentsMargins(12, 8, 12, 8);
        QLabel *sv = new QLabel(QString::number(s.count));
        sv->setAlignment(Qt::AlignCenter);
        sv->setStyleSheet("font-size:20px; font-weight:bold; color:white; background:transparent;");
        QLabel *sl = new QLabel(s.name);
        sl->setAlignment(Qt::AlignCenter);
        sl->setStyleSheet("font-size:11px; color:rgba(255,255,255,0.85); background:transparent;");
        scl->addWidget(sv);
        scl->addWidget(sl);
        serviceRow->addWidget(sCard);
    }
    serviceLay->addLayout(serviceRow);
    mainLay->addWidget(serviceCard);

    // ── Bouton Fermer ─────────────────────────────────────────────
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton { background:#2C5F7C; color:white; font-size:14px; font-weight:600;"
        "border:none; border-radius:8px; }"
        "QPushButton:hover { background:#1B3A57; }"
        );
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}


// ================================================================
// === MODULE CLIENT — [NOM DU MEMBRE] ============================
// Implémenter ici ClientStat::calculer() et afficherStatistiques()
// ================================================================


// ================================================================
// === MODULE CONTENEUR — [NOM DU MEMBRE] =========================
// Implémenter ici ConteneurStat::calculer() et afficherStatistiques()
// ================================================================


// ================================================================
// === MODULE COLLECTE — [NOM DU MEMBRE] ==========================
// Implémenter ici CollecteStat::calculer() et afficherStatistiques()
// ================================================================


// ================================================================
// === MODULE RECYCLAGE — [NOM DU MEMBRE] =========================
// Implémenter ici RecyclageStat::calculer() et afficherStatistiques()
// ================================================================
