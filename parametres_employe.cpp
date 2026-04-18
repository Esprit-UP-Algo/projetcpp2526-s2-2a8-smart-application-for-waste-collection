#include "parametres_employe.h"
#include "login.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <QProcess>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QMessageBox>

// ============================================================
// Utilitaire — envoyer email (copie de login.cpp)
// ============================================================
static void envoyerEmailParametres(const QString &dest,
                                   const QString &sujet,
                                   const QString &corps)
{
    const QString GMAIL_USER = "hafnaouimaryem44@gmail.com";
    const QString GMAIL_PASS = "sawxjnmqalzupwbd";

    QString tmpPath = QDir::tempPath() + "/sm_param.txt";
    QFile f(tmpPath);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Text)) return;
    QTextStream out(&f);
    out << "From: SmartMarket <" << GMAIL_USER << ">\r\n";
    out << "To: " << dest << "\r\n";
    out << "Subject: " << sujet << "\r\n";
    out << "\r\n";
    out << corps;
    f.close();

    QProcess process;
    QStringList args;
    args << "--ssl-reqd"
         << "--url" << "smtps://smtp.gmail.com:465"
         << "--user" << QString("%1:%2").arg(GMAIL_USER, GMAIL_PASS)
         << "--mail-from" << GMAIL_USER
         << "--mail-rcpt" << dest
         << "--upload-file" << tmpPath
         << "--silent";
    process.start("curl", args);
    process.waitForFinished(15000);
    QFile::remove(tmpPath);
}

// ============================================================
// Styles communs
// ============================================================
static QString editStyle()
{
    return "QLineEdit { background:#2A2A3E; border:1px solid #3A3A5C; border-radius:8px;"
           "padding:10px 14px; font-size:13px; color:white; }"
           "QLineEdit:focus { border:1px solid #2C5F7C; }";
}
static QString lblStyle()
{
    return "QLabel { color:#A0AEC0; font-size:12px; background:transparent; }";
}
static void showMsg(QWidget *parent, const QString &titre,
                    const QString &msg, const QString &type)
{
    QString couleur = "#2C5F7C", icone = "ℹ️";
    if (type == "success") { couleur = "#1A7A4A"; icone = "✅"; }
    if (type == "error")   { couleur = "#C0392B"; icone = "❌"; }

    QDialog *d = new QDialog(parent);
    d->setFixedSize(400, 180);
    d->setStyleSheet("QDialog { background:#1E1E2E; border-radius:12px; }");
    QVBoxLayout *vl = new QVBoxLayout(d);
    vl->setContentsMargins(0,0,0,20); vl->setSpacing(0);

    QWidget *hdr = new QWidget(); hdr->setFixedHeight(55);
    hdr->setStyleSheet(QString("background:%1; border-top-left-radius:12px;"
                               "border-top-right-radius:12px;").arg(couleur));
    QHBoxLayout *hl = new QHBoxLayout(hdr); hl->setContentsMargins(18,0,18,0);
    QLabel *lt = new QLabel(icone + "  " + titre);
    lt->setStyleSheet("color:white; font-size:14px; font-weight:bold; background:transparent;");
    hl->addWidget(lt); vl->addWidget(hdr);

    QLabel *lm = new QLabel(msg);
    lm->setAlignment(Qt::AlignCenter); lm->setWordWrap(true);
    lm->setStyleSheet("color:#C8C8D8; font-size:13px; background:transparent; padding:12px 20px;");
    vl->addWidget(lm); vl->addStretch();

    QPushButton *ok = new QPushButton("OK");
    ok->setFixedSize(90, 36);
    ok->setStyleSheet(QString("background:%1; color:white; border:none;"
                              "border-radius:8px; font-weight:600;").arg(couleur));
    QObject::connect(ok, &QPushButton::clicked, d, &QDialog::accept);
    QHBoxLayout *bl = new QHBoxLayout();
    bl->addStretch(); bl->addWidget(ok); bl->addStretch();
    vl->addLayout(bl);
    d->exec();
}

// ============================================================
// Changer Mot de Passe
// ============================================================
void Parametres_employe::changerMotDePasse(QWidget *parent)
{
    QDialog *d = new QDialog(parent);
    d->setWindowTitle("🔑 Changer le mot de passe");
    d->setFixedSize(460, 370);
    d->setStyleSheet("QDialog { background:#1E1E2E; }");

    QVBoxLayout *vl = new QVBoxLayout(d);
    vl->setContentsMargins(0,0,0,24); vl->setSpacing(0);

    // Header
    QWidget *hdr = new QWidget(); hdr->setFixedHeight(62);
    hdr->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-top-left-radius:14px; border-top-right-radius:14px;");
    QHBoxLayout *hl = new QHBoxLayout(hdr); hl->setContentsMargins(22,0,22,0);
    QLabel *lt = new QLabel("🔑  Nouveau mot de passe");
    lt->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hl->addWidget(lt); vl->addWidget(hdr);

    // Body
    QWidget *body = new QWidget();
    QVBoxLayout *bl = new QVBoxLayout(body);
    bl->setContentsMargins(30,20,30,10); bl->setSpacing(10);

    QLabel *lE = new QLabel("📧 Votre email :"); lE->setStyleSheet(lblStyle());
    QLineEdit *inEmail = new QLineEdit(); inEmail->setStyleSheet(editStyle());
    inEmail->setPlaceholderText("exemple@mail.com");

    QLabel *lM1 = new QLabel("🔑 Nouveau mot de passe :"); lM1->setStyleSheet(lblStyle());
    QLineEdit *inMdp1 = new QLineEdit(); inMdp1->setStyleSheet(editStyle());
    inMdp1->setEchoMode(QLineEdit::Password);
    inMdp1->setPlaceholderText("Nouveau mot de passe");

    QLabel *lM2 = new QLabel("🔑 Confirmer :"); lM2->setStyleSheet(lblStyle());
    QLineEdit *inMdp2 = new QLineEdit(); inMdp2->setStyleSheet(editStyle());
    inMdp2->setEchoMode(QLineEdit::Password);
    inMdp2->setPlaceholderText("Confirmer mot de passe");

    bl->addWidget(lE);  bl->addWidget(inEmail);
    bl->addWidget(lM1); bl->addWidget(inMdp1);
    bl->addWidget(lM2); bl->addWidget(inMdp2);
    vl->addWidget(body); vl->addStretch();

    // Boutons
    QHBoxLayout *btnL = new QHBoxLayout();
    btnL->setContentsMargins(30,0,30,0); btnL->setSpacing(12);
    QPushButton *btnAnn = new QPushButton("✗ Annuler");
    btnAnn->setFixedHeight(42);
    btnAnn->setStyleSheet("background:#374151; color:white; font-size:13px;"
                          "font-weight:600; border:none; border-radius:8px;");
    QPushButton *btnOk = new QPushButton("✓ Valider");
    btnOk->setFixedHeight(42);
    btnOk->setStyleSheet("background:#2C5F7C; color:white; font-size:13px;"
                         "font-weight:600; border:none; border-radius:8px;");
    btnL->addWidget(btnAnn); btnL->addWidget(btnOk);
    vl->addLayout(btnL);

    QObject::connect(btnAnn, &QPushButton::clicked, d, &QDialog::reject);
    QObject::connect(btnOk, &QPushButton::clicked, d, [=]() {

        QString email = inEmail->text().trimmed();
        QString mdp1  = inMdp1->text().trimmed();
        QString mdp2  = inMdp2->text().trimmed();

        if (email.isEmpty() || mdp1.isEmpty() || mdp2.isEmpty()) {
            showMsg(d, "Erreur", "Tous les champs sont obligatoires !", "error"); return;
        }
        if (mdp1 != mdp2) {
            showMsg(d, "Erreur", "Les mots de passe ne correspondent pas !", "error"); return;
        }
        if (mdp1.length() < 6) {
            showMsg(d, "Erreur", "Minimum 6 caractères requis !", "error"); return;
        }

        // Vérifier email en BD
        QSqlQuery chk;
        chk.prepare("SELECT Nom, Prenom FROM EMPLOYES WHERE Email = :e");
        chk.bindValue(":e", email);
        if (!chk.exec() || !chk.next()) {
            showMsg(d, "Erreur", "Aucun compte trouvé avec cet email !", "error"); return;
        }
        QString nom = chk.value(0).toString() + " " + chk.value(1).toString();

        // Mettre à jour BD
        QSqlQuery upd;
        upd.prepare("UPDATE EMPLOYES SET MDP = :mdp WHERE Email = :e");
        upd.bindValue(":mdp", mdp1);
        upd.bindValue(":e",   email);
        if (!upd.exec()) {
            showMsg(d, "Erreur", "Impossible de modifier le mot de passe.", "error"); return;
        }
        QSqlDatabase::database().commit();

        // Envoyer email confirmation
        QString corps = QString(
                            "Bonjour %1,\r\n\r\n"
                            "Votre mot de passe a ete modifie avec succes.\r\n\r\n"
                            "Nouveau mot de passe : %2\r\n\r\n"
                            "Cordialement,\r\nSmartMarket\r\n"
                            ).arg(nom, mdp1);
        envoyerEmailParametres(email, "Confirmation changement de mot de passe", corps);

        showMsg(d, "Succès", "✅ Mot de passe modifié !\nEmail de confirmation envoyé.", "success");
        d->accept();
    });
    d->exec();
}

// ============================================================
// Changer Email
// ============================================================
void Parametres_employe::changerEmail(QWidget *parent)
{
    QDialog *d = new QDialog(parent);
    d->setWindowTitle("📧 Changer l'email");
    d->setFixedSize(460, 370);
    d->setStyleSheet("QDialog { background:#1E1E2E; }");

    QVBoxLayout *vl = new QVBoxLayout(d);
    vl->setContentsMargins(0,0,0,24); vl->setSpacing(0);

    QWidget *hdr = new QWidget(); hdr->setFixedHeight(62);
    hdr->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-top-left-radius:14px; border-top-right-radius:14px;");
    QHBoxLayout *hl = new QHBoxLayout(hdr); hl->setContentsMargins(22,0,22,0);
    QLabel *lt = new QLabel("📧  Changer l'adresse email");
    lt->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hl->addWidget(lt); vl->addWidget(hdr);

    QWidget *body = new QWidget();
    QVBoxLayout *bl = new QVBoxLayout(body);
    bl->setContentsMargins(30,20,30,10); bl->setSpacing(10);

    QLabel *lEA = new QLabel("📧 Email actuel :"); lEA->setStyleSheet(lblStyle());
    QLineEdit *inEmailAct = new QLineEdit(); inEmailAct->setStyleSheet(editStyle());
    inEmailAct->setPlaceholderText("email.actuel@mail.com");

    QLabel *lEN = new QLabel("📧 Nouvel email :"); lEN->setStyleSheet(lblStyle());
    QLineEdit *inEmailNew = new QLineEdit(); inEmailNew->setStyleSheet(editStyle());
    inEmailNew->setPlaceholderText("nouvel.email@mail.com");

    QLabel *lEC = new QLabel("📧 Confirmer nouvel email :"); lEC->setStyleSheet(lblStyle());
    QLineEdit *inEmailConf = new QLineEdit(); inEmailConf->setStyleSheet(editStyle());
    inEmailConf->setPlaceholderText("confirmer.email@mail.com");

    bl->addWidget(lEA);  bl->addWidget(inEmailAct);
    bl->addWidget(lEN);  bl->addWidget(inEmailNew);
    bl->addWidget(lEC);  bl->addWidget(inEmailConf);
    vl->addWidget(body); vl->addStretch();

    QHBoxLayout *btnL = new QHBoxLayout();
    btnL->setContentsMargins(30,0,30,0); btnL->setSpacing(12);
    QPushButton *btnAnn = new QPushButton("✗ Annuler");
    btnAnn->setFixedHeight(42);
    btnAnn->setStyleSheet("background:#374151; color:white; font-size:13px;"
                          "font-weight:600; border:none; border-radius:8px;");
    QPushButton *btnOk = new QPushButton("✓ Valider");
    btnOk->setFixedHeight(42);
    btnOk->setStyleSheet("background:#2C5F7C; color:white; font-size:13px;"
                         "font-weight:600; border:none; border-radius:8px;");
    btnL->addWidget(btnAnn); btnL->addWidget(btnOk);
    vl->addLayout(btnL);

    QObject::connect(btnAnn, &QPushButton::clicked, d, &QDialog::reject);
    QObject::connect(btnOk, &QPushButton::clicked, d, [=]() {

        QString emailAct  = inEmailAct->text().trimmed();
        QString emailNew  = inEmailNew->text().trimmed();
        QString emailConf = inEmailConf->text().trimmed();

        if (emailAct.isEmpty() || emailNew.isEmpty() || emailConf.isEmpty()) {
            showMsg(d, "Erreur", "Tous les champs sont obligatoires !", "error"); return;
        }
        if (emailNew != emailConf) {
            showMsg(d, "Erreur", "Les deux emails ne correspondent pas !", "error"); return;
        }
        if (!emailNew.contains("@") || !emailNew.contains(".")) {
            showMsg(d, "Erreur", "Nouvel email invalide !", "error"); return;
        }

        // Vérifier email actuel
        QSqlQuery chk;
        chk.prepare("SELECT Nom, Prenom FROM EMPLOYES WHERE Email = :e");
        chk.bindValue(":e", emailAct);
        if (!chk.exec() || !chk.next()) {
            showMsg(d, "Erreur", "Email actuel introuvable !", "error"); return;
        }
        QString nom = chk.value(0).toString() + " " + chk.value(1).toString();

        // Nouveau MDP automatique
        QString nouveauMdp = Login::genererMotDePasse();

        // Mettre à jour BD
        QSqlQuery upd;
        upd.prepare("UPDATE EMPLOYES SET Email = :en, MDP = :mdp WHERE Email = :ea");
        upd.bindValue(":en",  emailNew);
        upd.bindValue(":mdp", nouveauMdp);
        upd.bindValue(":ea",  emailAct);
        if (!upd.exec()) {
            showMsg(d, "Erreur", "Impossible de modifier l'email.", "error"); return;
        }
        QSqlDatabase::database().commit();

        // Envoyer email sur le NOUVEAU mail
        QString corps = QString(
                            "Bonjour %1,\r\n\r\n"
                            "Vous avez change votre adresse email sur SmartMarket.\r\n\r\n"
                            "Nouvel email         : %2\r\n"
                            "Nouveau mot de passe : %3\r\n\r\n"
                            "Utilisez ces identifiants pour votre prochaine connexion.\r\n\r\n"
                            "Cordialement,\r\nSmartMarket\r\n"
                            ).arg(nom, emailNew, nouveauMdp);
        envoyerEmailParametres(emailNew, "Changement d'email SmartMarket", corps);

        showMsg(d, "Succès",
                "✅ Email modifié !\nNouveau mot de passe envoyé à :\n" + emailNew, "success");
        d->accept();
    });
    d->exec();
}

// ============================================================
// Menu principal Paramètres
// ============================================================
void Parametres_employe::afficher(QWidget *parent)
{
    QDialog *dlg = new QDialog(parent);
    dlg->setWindowTitle("⚙️ Paramètres");
    dlg->setFixedSize(380, 210);
    dlg->setStyleSheet("QDialog { background:#1E1E2E; border-radius:14px; }");

    QVBoxLayout *vl = new QVBoxLayout(dlg);
    vl->setContentsMargins(0,0,0,24); vl->setSpacing(0);

    QWidget *hdr = new QWidget(); hdr->setFixedHeight(62);
    hdr->setStyleSheet(
        "background:qlineargradient(x1:0,y1:0,x2:1,y2:0,stop:0 #1B3A57,stop:1 #2C5F7C);"
        "border-top-left-radius:14px; border-top-right-radius:14px;");
    QHBoxLayout *hl = new QHBoxLayout(hdr); hl->setContentsMargins(22,0,22,0);
    QLabel *lt = new QLabel("⚙️  Paramètres du compte");
    lt->setStyleSheet("font-size:15px; font-weight:bold; color:white; background:transparent;");
    hl->addWidget(lt); vl->addWidget(hdr);

    vl->addSpacing(18);

    QString btnStyle =
        "QPushButton { background:#2C5F7C; color:white; font-size:13px; font-weight:600;"
        "border:none; border-radius:10px; padding:11px 20px; margin:0 30px; }"
        "QPushButton:hover { background:#3A6EA5; }";

    QPushButton *btnMdp   = new QPushButton("🔑  Changer le mot de passe");
    QPushButton *btnEmail = new QPushButton("📧  Changer l'email");
    btnMdp->setStyleSheet(btnStyle);
    btnEmail->setStyleSheet(btnStyle);
    vl->addWidget(btnMdp);
    vl->addSpacing(10);
    vl->addWidget(btnEmail);

    QObject::connect(btnMdp, &QPushButton::clicked, dlg, [=]() {
        dlg->accept();
        Parametres_employe::changerMotDePasse(parent);
    });
    QObject::connect(btnEmail, &QPushButton::clicked, dlg, [=]() {
        dlg->accept();
        Parametres_employe::changerEmail(parent);
    });

    dlg->exec();
}
