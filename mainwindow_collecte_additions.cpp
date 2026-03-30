// ================================================================
// ==  FONCTIONS MANQUANTES MODULE COLLECTE  ======================
// ==  À AJOUTER À LA FIN DE mainwindow.cpp  ======================
// ==  (ne pas modifier le reste du fichier)  =====================
// ================================================================
// Nécessite ces includes (déjà présents dans mainwindow.cpp) :
//   #include <QtCharts/QChartView>
//   #include <QtCharts/QBarSeries>
//   #include <QtCharts/QBarSet>
//   #include <QtCharts/QBarCategoryAxis>
//   #include <QtCharts/QValueAxis>
//   #include <QtCharts/QChart>
// Ajouter dans mainwindow.cpp en haut si absent :
//   #include <QtCharts/QBarSeries>
//   #include <QtCharts/QBarSet>
//   #include <QtCharts/QBarCategoryAxis>
//   #include <QtCharts/QValueAxis>
// ================================================================


// ================================================================
// === MODULE COLLECTE — RECHERCHE (bouton pushButton_38) =========
// ================================================================
void MainWindow::on_pushButton_38_clicked()
{
    // Récupérer le texte depuis le champ de recherche collecte
    QString recherche = ui->lineEdit_recherche_collecte->text().trimmed();

    if (recherche.isEmpty()) {
        afficherCollectes();
        return;
    }

    // Utiliser la méthode de la classe Collecte
    QList<Collecte> resultats = Collecte::rechercherParMotCle(recherche);

    // Réinitialiser le tableau
    ui->tableWidget_collecte->setRowCount(0);
    ui->tableWidget_collecte->setSortingEnabled(false);

    if (resultats.isEmpty()) {
        showMessage(this, "Recherche",
                    "Aucune collecte trouvée pour : " + recherche, "warning");
        return;
    }

    // Remplir le tableau avec les résultats
    int row = 0;
    for (const Collecte &c : resultats) {
        ui->tableWidget_collecte->insertRow(row);

        QStringList valeurs = {
            QString::number(c.getId()),
            c.getDateCollecte(),
            c.getTypeDechet(),
            QString::number(c.getQuantiteCollectee(), 'f', 2),
            c.getStatut(),
            QString::number(c.getDistanceTotale(), 'f', 2),
            c.getObservations()
        };

        for (int col = 0; col < valeurs.size(); ++col) {
            QString valeur = valeurs[col];

            // Badge Statut
            if (col == 4) {
                QString s = valeur.toLower();
                if      (s == "terminee" || s == "terminée") valeur = "✅ Terminée";
                else if (s == "en cours")  valeur = "⏳ En cours";
                else if (s == "annulee" || s == "annulée")   valeur = "❌ Annulée";
                else if (s == "planifiee" || s == "planifiée") valeur = "📋 Planifiée";
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            if (col == 0) {
                ui->tableWidget_collecte->setItem(row, col, item);
                ui->tableWidget_collecte->setColumnHidden(0, true);
                continue;
            }
            if (col == 2) {
                item->setForeground(QColor("#1B3A57"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }
            if (col == 4) {
                QString s = c.getStatut().toLower();
                if      (s == "terminee" || s == "terminée") item->setForeground(QColor("#1A7A4A"));
                else if (s == "en cours")  item->setForeground(QColor("#E67E22"));
                else if (s == "annulee" || s == "annulée")   item->setForeground(QColor("#C0392B"));
                else    item->setForeground(QColor("#2C5F7C"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }
            if (row % 2 == 0) item->setBackground(QColor("#ffffff"));
            else               item->setBackground(QColor("#f0f4f8"));

            ui->tableWidget_collecte->setItem(row, col, item);
        }
        ui->tableWidget_collecte->setRowHeight(row, 44);
        row++;
    }

    ui->tableWidget_collecte->setSortingEnabled(true);
    showMessage(this, "Recherche",
                QString::number(resultats.size()) + " collecte(s) trouvée(s) pour : " + recherche,
                "success");
}


// ================================================================
// === MODULE COLLECTE — TRI (bouton pushButton_35) ===============
// ================================================================
void MainWindow::on_pushButton_35_clicked()
{
    // Détecter quelle case est cochée (Date ou Zone)
    // Les checkboxes dans le UI s'appellent checkBox_date et checkBox_zone
    // selon ce qui est visible dans l'image de l'interface
    bool trierParDate = ui->checkBox_date->isChecked();
    bool trierParZone = ui->checkBox_zone->isChecked();

    QList<Collecte> liste;

    if (trierParDate) {
        liste = Collecte::trierParDate();
    } else if (trierParZone) {
        liste = Collecte::trierParZone();
    } else {
        // Aucune case cochée → affichage normal
        afficherCollectes();
        return;
    }

    // Réinitialiser le tableau
    ui->tableWidget_collecte->setRowCount(0);
    ui->tableWidget_collecte->setSortingEnabled(false);

    if (liste.isEmpty()) {
        showMessage(this, "Tri", "Aucune collecte disponible.", "warning");
        return;
    }

    // Remplir le tableau
    int row = 0;
    for (const Collecte &c : liste) {
        ui->tableWidget_collecte->insertRow(row);

        QStringList valeurs = {
            QString::number(c.getId()),
            c.getDateCollecte(),
            c.getTypeDechet(),
            QString::number(c.getQuantiteCollectee(), 'f', 2),
            c.getStatut(),
            QString::number(c.getDistanceTotale(), 'f', 2),
            c.getObservations()
        };

        for (int col = 0; col < valeurs.size(); ++col) {
            QString valeur = valeurs[col];

            if (col == 4) {
                QString s = valeur.toLower();
                if      (s == "terminee" || s == "terminée") valeur = "✅ Terminée";
                else if (s == "en cours")  valeur = "⏳ En cours";
                else if (s == "annulee" || s == "annulée")   valeur = "❌ Annulée";
                else if (s == "planifiee" || s == "planifiée") valeur = "📋 Planifiée";
            }

            QTableWidgetItem *item = new QTableWidgetItem(valeur);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);

            if (col == 0) {
                ui->tableWidget_collecte->setItem(row, col, item);
                ui->tableWidget_collecte->setColumnHidden(0, true);
                continue;
            }
            if (col == 2) {
                item->setForeground(QColor("#1B3A57"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }
            if (col == 4) {
                QString s = c.getStatut().toLower();
                if      (s == "terminee" || s == "terminée") item->setForeground(QColor("#1A7A4A"));
                else if (s == "en cours")  item->setForeground(QColor("#E67E22"));
                else if (s == "annulee" || s == "annulée")   item->setForeground(QColor("#C0392B"));
                else    item->setForeground(QColor("#2C5F7C"));
                item->setFont(QFont("Segoe UI", 12, QFont::Bold));
            }
            if (row % 2 == 0) item->setBackground(QColor("#ffffff"));
            else               item->setBackground(QColor("#f0f4f8"));

            ui->tableWidget_collecte->setItem(row, col, item);
        }
        ui->tableWidget_collecte->setRowHeight(row, 44);
        row++;
    }

    ui->tableWidget_collecte->setSortingEnabled(true);
}


// ================================================================
// === MODULE COLLECTE — EXPORT PDF (bouton pushButton_30 zone)  ==
// ================================================================
// Note : le bouton "Exporter en PDF" dans l'interface collecte
// correspond au slot suivant. Si ton bouton UI a un nom différent,
// remplace le nom du slot en conséquence.
// ================================================================
// Ajouter aussi ce slot dans mainwindow.h si absent :
//   void on_bouttonexportercollecte_clicked();
// ================================================================
void MainWindow::on_bouttonexportercollecte_clicked()
{
    QSqlQuery query;
    if (!query.exec(
            "SELECT ID_collecte, TO_CHAR(Date_collecte,'DD/MM/YYYY'), "
            "Type_dechet, Quantite_collectee, Statut, "
            "Distance_totale, Observations "
            "FROM COLLECTES ORDER BY Date_collecte DESC"))
    {
        showMessage(this, "Erreur SQL", query.lastError().text(), "error");
        return;
    }

    // Construire le HTML du rapport PDF
    QString html;
    html += "<html><head><meta charset='utf-8'><style>"
            "body{font-family:Arial,sans-serif;font-size:12px;}"
            "h1{text-align:center;color:#2C5F7C;margin-bottom:5px;}"
            "h3{text-align:center;color:#555;margin-top:0;}"
            "table{width:100%;border-collapse:collapse;margin-top:20px;}"
            "th{background-color:#2C5F7C;color:white;padding:10px;text-align:left;}"
            "td{border:1px solid #ddd;padding:7px;}"
            "tr:nth-child(even){background-color:#f0f4f8;}"
            ".badge-ok{color:#1A7A4A;font-weight:bold;}"
            ".badge-nc{color:#C0392B;font-weight:bold;}"
            ".badge-en{color:#E67E22;font-weight:bold;}"
            ".footer{text-align:center;margin-top:20px;color:#888;font-size:10px;}"
            "</style></head><body>";
    html += "<h1>🚛 Planning des Collectes</h1>";
    html += "<h3>Gestion des Tournées de Collecte — Smart Waste Application</h3>";
    html += "<p style='text-align:center;'>Exporté le : "
            + QDate::currentDate().toString("dd/MM/yyyy") + "</p>";
    html += "<table><tr>"
            "<th>ID</th><th>Date</th><th>Type Déchet</th>"
            "<th>Quantité (kg)</th><th>Statut</th>"
            "<th>Distance (km)</th><th>Observations</th></tr>";

    int total = 0;
    double quantiteTotale = 0.0;
    while (query.next()) {
        QString statut = query.value(4).toString();
        QString badgeClass = "badge-en";
        if (statut.toLower().contains("termin")) badgeClass = "badge-ok";
        else if (statut.toLower().contains("annul")) badgeClass = "badge-nc";

        html += "<tr>";
        html += "<td>" + query.value(0).toString() + "</td>";
        html += "<td>" + query.value(1).toString() + "</td>";
        html += "<td><b>" + query.value(2).toString() + "</b></td>";
        html += "<td>" + QString::number(query.value(3).toDouble(), 'f', 2) + "</td>";
        html += "<td class='" + badgeClass + "'>" + statut + "</td>";
        html += "<td>" + QString::number(query.value(5).toDouble(), 'f', 2) + "</td>";
        html += "<td>" + query.value(6).toString() + "</td>";
        html += "</tr>";
        total++;
        quantiteTotale += query.value(3).toDouble();
    }

    html += "</table>";
    html += "<p style='margin-top:15px;'>"
            "<b>Total collectes :</b> " + QString::number(total) +
            " &nbsp;|&nbsp; <b>Quantité totale :</b> " +
            QString::number(quantiteTotale, 'f', 2) + " kg</p>";
    html += "<p class='footer'>Généré automatiquement par Smart Waste Application</p>";
    html += "</body></html>";

    // Aperçu avant impression
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📄 Export Planning Collectes — PDF");
    dlg->setFixedSize(950, 650);
    QVBoxLayout *layout = new QVBoxLayout(dlg);

    QTextEdit *preview = new QTextEdit();
    preview->setReadOnly(true);
    preview->setHtml(html);
    layout->addWidget(preview);

    QHBoxLayout *btnL = new QHBoxLayout();

    QPushButton *btnImprimer = new QPushButton("🖨️  Enregistrer en PDF");
    btnImprimer->setMinimumHeight(45);
    btnImprimer->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#1B3A57;}");

    QPushButton *btnFermer = new QPushButton("Fermer");
    btnFermer->setMinimumHeight(45);
    btnFermer->setStyleSheet(
        "QPushButton{background:#E5E7EB;color:#374151;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;padding:10px 25px;}"
        "QPushButton:hover{background:#D1D5DB;}");

    btnL->addWidget(btnFermer);
    btnL->addWidget(btnImprimer);
    layout->addLayout(btnL);

    connect(btnFermer, &QPushButton::clicked, dlg, &QDialog::reject);
    connect(btnImprimer, &QPushButton::clicked, this, [=]() {
        QString fichier = QFileDialog::getSaveFileName(
            dlg, "Enregistrer PDF", "planning_collectes.pdf", "PDF (*.pdf)");
        if (!fichier.isEmpty()) {
            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fichier);
            QTextDocument doc;
            doc.setHtml(html);
            doc.print(static_cast<QPagedPaintDevice*>(&printer));
            showMessage(dlg, "Succès",
                        "✅ Planning exporté en PDF avec succès !\n" + fichier,
                        "success");
        }
    });

    dlg->exec();
}


// ================================================================
// === MODULE COLLECTE — OPTIMISATION ITINERAIRE IA ===============
// ================================================================
// Slot pour le bouton d'optimisation d'itinéraire
// Ajouter dans mainwindow.h :  void on_bouttonoptimisercollecte_clicked();
// ================================================================
void MainWindow::on_bouttonoptimisercollecte_clicked()
{
    // Récupérer tous les IDs des collectes disponibles
    QSqlQuery query;
    if (!query.exec("SELECT ID_collecte FROM COLLECTES WHERE UPPER(Statut) = 'PLANIFIÉE' OR UPPER(Statut) = 'PLANIFIEE'")) {
        // Si aucune planifiée, prendre toutes
        if (!query.exec("SELECT ID_collecte FROM COLLECTES ORDER BY ID_collecte"))
        {
            showMessage(this, "Erreur SQL", query.lastError().text(), "error");
            return;
        }
    }

    QList<int> ids;
    while (query.next())
        ids.append(query.value(0).toInt());

    if (ids.isEmpty()) {
        showMessage(this, "Optimisation IA",
                    "Aucune collecte disponible pour optimiser l'itinéraire.", "warning");
        return;
    }

    // Appel de l'algorithme d'optimisation
    QList<int> itineraireOptimise = Collecte::optimiserItineraire(ids);

    // Calculer la distance totale estimée de l'itinéraire optimisé
    double distanceTotaleEstimee = 0.0;
    QList<Collecte> collectesOptimisees;
    for (int id : itineraireOptimise) {
        Collecte c = Collecte::getById(id);
        collectesOptimisees.append(c);
        distanceTotaleEstimee += c.getDistanceTotale();
    }

    // Afficher le résultat dans un dialogue
    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("🤖 Optimisation d'Itinéraire par IA");
    dlg->setFixedSize(700, 600);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *mainLay = new QVBoxLayout(dlg);
    mainLay->setContentsMargins(20, 20, 20, 20);
    mainLay->setSpacing(15);

    QLabel *title = new QLabel("🤖 Itinéraire Optimal — Algorithme IA (Plus Proche Voisin)");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:16px; font-weight:bold; color:white; padding:15px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:12px;"
        );
    mainLay->addWidget(title);

    // Résumé KPI
    QHBoxLayout *kpiRow = new QHBoxLayout();
    auto makeKPI2 = [](const QString &icon, const QString &val, const QString &lbl, const QString &color) {
        QFrame *card = new QFrame();
        card->setFixedHeight(75);
        card->setStyleSheet(QString("QFrame{background:%1;border-radius:10px;}").arg(color));
        QVBoxLayout *cl = new QVBoxLayout(card);
        cl->setContentsMargins(10, 8, 10, 8);
        QLabel *v = new QLabel(icon + " " + val);
        v->setAlignment(Qt::AlignCenter);
        v->setStyleSheet("font-size:18px;font-weight:bold;color:white;background:transparent;");
        QLabel *l = new QLabel(lbl);
        l->setAlignment(Qt::AlignCenter);
        l->setStyleSheet("font-size:10px;color:rgba(255,255,255,0.85);background:transparent;");
        cl->addWidget(v);
        cl->addWidget(l);
        return card;
    };

    kpiRow->addWidget(makeKPI2("🗑️", QString::number(itineraireOptimise.size()), "Collectes optimisées", "#2C5F7C"));
    kpiRow->addWidget(makeKPI2("📏", QString::number(distanceTotaleEstimee, 'f', 1) + " km", "Distance estimée", "#27AE60"));
    mainLay->addLayout(kpiRow);

    // Tableau de l'itinéraire optimisé
    QTableWidget *table = new QTableWidget();
    table->setColumnCount(5);
    table->setHorizontalHeaderLabels({"Étape", "ID", "Type Déchet", "Quantité (kg)", "Distance (km)"});
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setVisible(false);
    table->setShowGrid(false);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(R"(
        QTableWidget { background:#f0f4f8; border:none; font-size:13px; }
        QTableWidget::item { padding:8px; border-bottom:1px solid #dfe6ed; }
        QTableWidget::item:selected { background:#2C5F7C; color:white; }
        QHeaderView::section { background:#2C5F7C; color:white; font-weight:bold; padding:8px; border:none; }
    )");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    int etape = 1;
    for (const Collecte &c : collectesOptimisees) {
        int row = table->rowCount();
        table->insertRow(row);
        table->setItem(row, 0, new QTableWidgetItem(QString("📍 Étape %1").arg(etape++)));
        table->setItem(row, 1, new QTableWidgetItem(QString::number(c.getId())));
        table->setItem(row, 2, new QTableWidgetItem(c.getTypeDechet()));
        table->setItem(row, 3, new QTableWidgetItem(QString::number(c.getQuantiteCollectee(), 'f', 2)));
        table->setItem(row, 4, new QTableWidgetItem(QString::number(c.getDistanceTotale(), 'f', 2)));
        table->setRowHeight(row, 40);
    }
    mainLay->addWidget(table);

    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(40);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;}"
        "QPushButton:hover{background:#1B3A57;}");
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    mainLay->addWidget(closeBtn);

    dlg->exec();
}


// ================================================================
// === MODULE COLLECTE — HISTORIQUE TRANSACTIONS ==================
// ================================================================
// Slot pour afficher l'historique complet des transactions
// Ajouter dans mainwindow.h :  void on_bouttonhistoriquecollecte_clicked();
// ================================================================
void MainWindow::on_bouttonhistoriquecollecte_clicked()
{
    QList<Collecte> historique = Collecte::historique();

    QDialog *dlg = new QDialog(this);
    dlg->setWindowTitle("📋 Historique des Transactions — Collectes");
    dlg->setFixedSize(900, 600);
    dlg->setStyleSheet("QDialog { background-color: #F0F4F8; }");

    QVBoxLayout *layout = new QVBoxLayout(dlg);
    layout->setContentsMargins(15, 15, 15, 15);

    QLabel *title = new QLabel("📋 Historique Complet des Collectes (du plus récent au plus ancien)");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(
        "font-size:15px;font-weight:bold;color:white;padding:12px;"
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-radius:10px;");
    layout->addWidget(title);

    QTableWidget *table = new QTableWidget();
    table->setColumnCount(7);
    table->setHorizontalHeaderLabels({
        "ID", "Date & Heure", "Type Déchet",
        "Quantité (kg)", "Statut", "Distance (km)", "Observations"
    });
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setVisible(false);
    table->setShowGrid(false);
    table->setAlternatingRowColors(true);
    table->setStyleSheet(R"(
        QTableWidget { background:#f0f4f8; border:none; font-size:12px; }
        QTableWidget::item { padding:8px; border-bottom:1px solid #dfe6ed; }
        QTableWidget::item:selected { background:#2C5F7C; color:white; }
        QHeaderView::section { background:#2C5F7C; color:white; font-weight:bold; padding:8px; border:none; }
    )");
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setStretchLastSection(true);

    int row = 0;
    for (const Collecte &c : historique) {
        table->insertRow(row);

        QString statut = c.getStatut();
        QString statutBadge = statut;
        if (statut.toLower().contains("termin"))       statutBadge = "✅ " + statut;
        else if (statut.toLower().contains("en cours")) statutBadge = "⏳ " + statut;
        else if (statut.toLower().contains("annul"))    statutBadge = "❌ " + statut;
        else if (statut.toLower().contains("planif"))   statutBadge = "📋 " + statut;

        QStringList vals = {
            QString::number(c.getId()),
            c.getDateCollecte(),
            c.getTypeDechet(),
            QString::number(c.getQuantiteCollectee(), 'f', 2),
            statutBadge,
            QString::number(c.getDistanceTotale(), 'f', 2),
            c.getObservations()
        };

        for (int col = 0; col < vals.size(); ++col) {
            QTableWidgetItem *item = new QTableWidgetItem(vals[col]);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignLeft);
            if (row % 2 == 0) item->setBackground(QColor("#ffffff"));
            else               item->setBackground(QColor("#f0f4f8"));
            table->setItem(row, col, item);
        }
        table->setRowHeight(row, 40);
        row++;
    }
    layout->addWidget(table);

    QLabel *info = new QLabel(
        QString("📊 Total : %1 transaction(s)  |  Quantité totale : %2 kg")
            .arg(historique.size())
            .arg(Collecte::quantiteTotale(), 0, 'f', 2)
        );
    info->setStyleSheet("font-size:13px;color:#374151;padding:5px;");
    layout->addWidget(info);

    QPushButton *closeBtn = new QPushButton("✕  Fermer");
    closeBtn->setFixedHeight(40);
    closeBtn->setStyleSheet(
        "QPushButton{background:#2C5F7C;color:white;font-size:14px;"
        "font-weight:600;border:none;border-radius:8px;}"
        "QPushButton:hover{background:#1B3A57;}");
    connect(closeBtn, &QPushButton::clicked, dlg, &QDialog::accept);
    layout->addWidget(closeBtn);

    dlg->exec();
}
