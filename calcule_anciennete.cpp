#include "calcule_anciennete.h"
#include <QSqlQuery>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QAbstractItemView>

// ============================================================
// Constructeur
// ============================================================
Calcule_anciennete::Calcule_anciennete() {}

// ============================================================
// Règle de prime privée
// ============================================================
double Calcule_anciennete::calculerPrime(double salaire, int annees)
{
    // < 1 an   → 0%
    // 1-3 ans  → 5%
    // 3-5 ans  → 10%
    // 5-10 ans → 15%
    // > 10 ans → 20%
    if (annees < 1)  return 0.0;
    if (annees < 3)  return salaire * 0.05;
    if (annees < 5)  return salaire * 0.10;
    if (annees < 10) return salaire * 0.15;
    return salaire * 0.20;
}

// ============================================================
// Métier avancé — Ancienneté + Prime
// ============================================================
void Calcule_anciennete::calculerAncienneteEtPrime(QWidget *parent)
{
    QSqlQuery q;

    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("📅 Ancienneté & Primes des Employés");
    dlg->setFixedSize(860, 600);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(16);

    // ── Titre ────────────────────────────────────────────────────
    QLabel *title = new QLabel("📅 Calcul Automatique — Ancienneté & Primes");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:18px; font-weight:bold; color:white; padding:16px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // ── Table ────────────────────────────────────────────────────
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(6);
    table->setHorizontalHeaderLabels({
        "CIN", "Nom Complet", "Date Embauche",
        "Ancienneté", "Salaire (TND)", "Prime (TND)"
    });
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(
        "QTableWidget { background:white; border-radius:8px; }"
        "QHeaderView::section { background:#2C5F7C; color:white;"
        " padding:6px; font-weight:bold; }"
        "QTableWidget::item:alternate { background:#F0F4F8; }"
        );

    // ── Remplissage ──────────────────────────────────────────────
    q.exec(
        "SELECT CIN, Nom, Prenom, "
        "TO_CHAR(Date_embauche,'DD/MM/YYYY'), "
        "Salaire, Date_embauche "
        "FROM EMPLOYES ORDER BY Date_embauche"
        );

    QDate today = QDate::currentDate();
    int row = 0;

    while (q.next()) {
        QString cin     = q.value(0).toString();
        QString nom     = q.value(1).toString();
        QString prenom  = q.value(2).toString();
        QString dateStr = q.value(3).toString();
        double  salaire = q.value(4).toDouble();
        QDate   dateEmb = q.value(5).toDate();

        int annees = dateEmb.daysTo(today) / 365;
        int mois   = (dateEmb.daysTo(today) % 365) / 30;
        double prime = calculerPrime(salaire, annees);

        QString anciennete = QString("%1 an(s) %2 mois").arg(annees).arg(mois);

        // ── Couleurs foncées + texte lisible ─────────────────────────
        QColor couleur;
        QColor textColor;

        if (annees < 1) {
            couleur   = QColor("#F87171");
            textColor = QColor("#7F1D1D");
        }
        else if (annees < 3) {
            couleur   = QColor("#FBBF24");
            textColor = QColor("#78350F");
        }
        else if (annees < 5) {
            couleur   = QColor("#34D399");
            textColor = QColor("#064E3B");
        }
        else if (annees < 10) {
            couleur   = QColor("#60A5FA");
            textColor = QColor("#1E3A5F");
        }
        else {
            couleur   = QColor("#A78BFA");
            textColor = QColor("#2E1065");
        }

        table->insertRow(row);
        QStringList vals = {
            cin,
            nom + " " + prenom,
            dateStr,
            anciennete,
            QString::number(salaire, 'f', 2),
            QString::number(prime,   'f', 2)
        };
        for (int col = 0; col < 6; col++) {
            QTableWidgetItem *item = new QTableWidgetItem(vals[col]);
            item->setBackground(couleur);
            item->setForeground(textColor);
            item->setTextAlignment(Qt::AlignCenter);
            table->setItem(row, col, item);
        }
        table->setRowHeight(row, 40);
        row++;
    }
    table->resizeColumnsToContents();
    mainLay->addWidget(table);

    // ── Légende ──────────────────────────────────────────────────
    QHBoxLayout *legendLay = new QHBoxLayout();
    auto makeLegend = [](const QString &color, const QString &label) {
        QHBoxLayout *h = new QHBoxLayout();
        QLabel *dot = new QLabel("●");
        dot->setStyleSheet(QString("color:%1; font-size:18px;").arg(color));
        QLabel *lbl = new QLabel(label);
        lbl->setStyleSheet("font-size:11px; color:#374151;");
        h->addWidget(dot); h->addWidget(lbl); h->addSpacing(10);
        return h;
    };
    legendLay->addLayout(makeLegend("#EF4444", "< 1 an  (0%)"));
    legendLay->addLayout(makeLegend("#F59E0B", "1-3 ans (5%)"));
    legendLay->addLayout(makeLegend("#10B981", "3-5 ans (10%)"));
    legendLay->addLayout(makeLegend("#3B82F6", "5-10 ans (15%)"));
    legendLay->addLayout(makeLegend("#8B5CF6", "> 10 ans (20%)"));
    legendLay->addStretch();
    mainLay->addLayout(legendLay);

    // ── Bouton Fermer ────────────────────────────────────────────
    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(42);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;}"
        "QPushButton:hover{background:#1B3A57;}"
        );
    QObject::connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}

