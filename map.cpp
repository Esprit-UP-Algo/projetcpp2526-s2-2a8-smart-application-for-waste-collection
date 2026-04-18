#include "map.h"
#include <QApplication>
#include <QScreen>
#include <QFontMetrics>
#include <QPainterPath>

// ============================================================
// CarteWidget
// ============================================================

CarteWidget::CarteWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(700, 500);
    setMouseTracking(true);
    setCursor(Qt::CrossCursor);
}

void CarteWidget::setConteneurs(const QList<Conteneur> &liste)
{
    m_conteneurs = liste;
    m_hover    = -1;
    m_selected = -1;
    update();
}

void CarteWidget::setInfoLabel(QLabel *label)
{
    m_infoLabel = label;
}

// ── Conversion GPS → pixel ───────────────────────────────────────
QPointF CarteWidget::gpsToPixel(double lat, double lng) const
{
    int W = width()  > 0 ? width()  : 700;
    int H = height() > 0 ? height() : 500;
    const double margin = 55.0;
    double x = margin + (lng - LNG_MIN) / (LNG_MAX - LNG_MIN) * (W - 2*margin);
    double y = margin + (LAT_MAX - lat) / (LAT_MAX - LAT_MIN) * (H - 2*margin);
    return QPointF(x, y);
}

// ── Icône poubelle ───────────────────────────────────────────────
void CarteWidget::drawTrashIcon(QPainter &p, QPointF center,
                                QColor color, bool hovered,
                                bool selected, int id)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    double scale = hovered ? 1.4 : (selected ? 1.3 : 1.0);
    double W = 22 * scale;
    double H = 26 * scale;
    double cx = center.x();
    double cy = center.y();

    // Ombre
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 50));
    p.drawEllipse(QPointF(cx + 2, cy + H/2 + 4), W * 0.45, 5 * scale);

    QColor bodyColor = color;
    QColor lidColor  = color.darker(115);

    // Anneau de sélection
    if (selected) {
        p.setPen(QPen(QColor(255, 220, 0), 3));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(QPointF(cx, cy), W * 0.72 + 6, H * 0.65 + 6);
    }

    // Corps principal
    QPainterPath body;
    double bx = cx - W/2;
    double by = cy - H/2 + 6 * scale;
    double bw = W;
    double bh = H - 6 * scale;
    body.addRoundedRect(bx, by, bw, bh, 4 * scale, 4 * scale);
    p.setPen(Qt::NoPen);
    p.setBrush(bodyColor);
    p.drawPath(body);

    // Lignes verticales
    p.setPen(QPen(bodyColor.darker(130), 1.5 * scale));
    double lineY1 = by + bh * 0.2;
    double lineY2 = by + bh * 0.85;
    for (int i = -1; i <= 1; i++) {
        double lx = cx + i * (W * 0.22);
        p.drawLine(QPointF(lx, lineY1), QPointF(lx, lineY2));
    }

    // Couvercle
    QPainterPath lid;
    double lx = cx - W * 0.58;
    double ly = cy - H/2;
    double lw = W * 1.16;
    double lh = 7 * scale;
    lid.addRoundedRect(lx, ly, lw, lh, 3 * scale, 3 * scale);
    p.setPen(Qt::NoPen);
    p.setBrush(lidColor);
    p.drawPath(lid);

    // Poignée
    p.setPen(QPen(lidColor.darker(120), 2 * scale, Qt::SolidLine, Qt::RoundCap));
    p.setBrush(Qt::NoBrush);
    p.drawLine(QPointF(cx - W * 0.18, ly - 1 * scale),
               QPointF(cx + W * 0.18, ly - 1 * scale));

    // Numéro
    p.setPen(Qt::white);
    QFont f("Segoe UI", qMax(7.0, 8.0 * scale), QFont::Bold);
    p.setFont(f);
    QRectF txtRect(cx - W/2, by, W, bh);
    p.drawText(txtRect, Qt::AlignCenter, QString::number(id));

    p.restore();
}

// ── paintEvent ──────────────────────────────────────────────────
void CarteWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    int W = width(), H = height();

    // ── Fond dégradé (mer)
    QLinearGradient bg(0, 0, W, H);
    bg.setColorAt(0.0, QColor("#B8D4EC"));
    bg.setColorAt(1.0, QColor("#7AAECF"));
    p.fillRect(rect(), bg);

    // ════════════════════════════════════════════════════════════
    // POLYGONE TUNISIE — coordonnées précises
    // ════════════════════════════════════════════════════════════
    QPolygonF tunisie;
    tunisie
        // ── Nord : Cap Blanc
        << gpsToPixel(37.349,  9.751)
        << gpsToPixel(37.280,  9.900)
        << gpsToPixel(37.230, 10.120)
        << gpsToPixel(37.155, 10.285)
        << gpsToPixel(37.080, 10.450)
        // ── Péninsule du Cap Bon
        << gpsToPixel(36.980, 10.600)
        << gpsToPixel(36.945, 11.020)
        << gpsToPixel(36.900, 11.085)
        << gpsToPixel(36.830, 11.115)
        << gpsToPixel(36.750, 11.105)
        << gpsToPixel(36.715, 11.100)
        << gpsToPixel(36.650, 11.060)
        << gpsToPixel(36.600, 11.035)
        << gpsToPixel(36.530, 10.960)
        << gpsToPixel(36.460, 10.880)
        // ── Côte est : Hammamet → Sousse
        << gpsToPixel(36.380, 10.780)
        << gpsToPixel(36.280, 10.700)
        << gpsToPixel(36.170, 10.720)
        << gpsToPixel(36.080, 10.740)
        << gpsToPixel(35.980, 10.760)
        << gpsToPixel(35.850, 10.800)
        << gpsToPixel(35.730, 10.820)
        // ── Mahdia → Sfax
        << gpsToPixel(35.600, 10.900)
        << gpsToPixel(35.480, 11.020)
        << gpsToPixel(35.350, 11.060)
        << gpsToPixel(35.170, 11.070)
        << gpsToPixel(35.000, 11.065)
        << gpsToPixel(34.920, 11.050)
        << gpsToPixel(34.800, 11.040)
        << gpsToPixel(34.740, 11.020)
        // ── Gabès → Médenine
        << gpsToPixel(34.580, 10.900)
        << gpsToPixel(34.420, 10.760)
        << gpsToPixel(34.220, 10.520)
        << gpsToPixel(34.050, 10.340)
        << gpsToPixel(33.940, 10.200)
        << gpsToPixel(33.880, 10.120)
        << gpsToPixel(33.780, 10.060)
        << gpsToPixel(33.650, 10.010)
        // ── Djerba / Zarzis
        << gpsToPixel(33.540,  9.950)
        << gpsToPixel(33.500,  9.920)
        << gpsToPixel(33.420,  9.840)
        << gpsToPixel(33.350,  9.760)
        << gpsToPixel(33.250,  9.660)
        << gpsToPixel(33.200,  9.560)
        // ── Sud : Tataouine → désert libyen
        << gpsToPixel(33.060,  9.450)
        << gpsToPixel(32.900,  9.320)
        << gpsToPixel(32.700,  9.180)
        << gpsToPixel(32.500,  9.100)
        << gpsToPixel(32.300,  9.070)
        << gpsToPixel(32.100,  9.050)
        << gpsToPixel(31.900,  9.040)
        << gpsToPixel(31.700,  9.042)
        << gpsToPixel(31.500,  9.050)
        << gpsToPixel(31.300,  9.065)
        << gpsToPixel(31.100,  9.080)
        << gpsToPixel(30.850,  9.120)
        << gpsToPixel(30.600,  9.180)
        << gpsToPixel(30.500,  9.220)
        // ── Frontière algérienne (remontée vers le nord-ouest)
        << gpsToPixel(30.300,  9.520)
        << gpsToPixel(30.500,  9.520)
        << gpsToPixel(30.800,  9.500)
        << gpsToPixel(31.200,  9.380)
        << gpsToPixel(31.600,  9.220)
        << gpsToPixel(32.000,  8.560)
        << gpsToPixel(32.300,  8.420)
        << gpsToPixel(32.600,  8.310)
        << gpsToPixel(33.000,  8.190)
        << gpsToPixel(33.300,  8.155)
        << gpsToPixel(33.600,  8.130)
        << gpsToPixel(33.900,  8.145)
        << gpsToPixel(34.200,  8.170)
        << gpsToPixel(34.500,  8.215)
        << gpsToPixel(34.800,  8.270)
        << gpsToPixel(35.100,  8.320)
        << gpsToPixel(35.400,  8.345)
        << gpsToPixel(35.700,  8.360)
        << gpsToPixel(36.000,  8.375)
        << gpsToPixel(36.300,  8.385)
        << gpsToPixel(36.550,  8.390)
        << gpsToPixel(36.800,  8.415)
        << gpsToPixel(37.000,  8.480)
        << gpsToPixel(37.150,  8.560)
        << gpsToPixel(37.250,  8.680)
        // ── Retour au Cap Blanc
        << gpsToPixel(37.310,  9.100)
        << gpsToPixel(37.349,  9.400)
        << gpsToPixel(37.349,  9.751);

    // Remplissage terre
    p.setPen(Qt::NoPen);
    p.setBrush(QColor("#D4E8B0"));
    p.drawPolygon(tunisie);

    // Bordure côtière
    p.setPen(QPen(QColor("#6B9E3E"), 1.8));
    p.setBrush(Qt::NoBrush);
    p.drawPolygon(tunisie);

    // ── Grille légère
    p.setPen(QPen(QColor(255, 255, 255, 40), 1, Qt::DashLine));
    for (int x = 55; x < W; x += 70) p.drawLine(x, 0, x, H);
    for (int y = 55; y < H; y += 70) p.drawLine(0, y, W, y);

    // ── Titre
    p.setPen(QColor("#1B3A57"));
    p.setFont(QFont("Segoe UI", 12, QFont::Bold));
    p.drawText(12, 26, "🗺  Carte des Conteneurs — Tunisie");

    // ── Labels latitude / longitude
    p.setFont(QFont("Segoe UI", 7));
    p.setPen(QColor("#1B3A57"));

    for (double lng = 8.0; lng <= 11.5; lng += 0.5) {
        QPointF pt = gpsToPixel(29.9, lng);
        p.drawText(QPointF(pt.x() - 10, H - 6),
                   QString::number(lng, 'f', 1) + "°E");
    }
    for (double lat = 30.0; lat <= 37.5; lat += 1.0) {
        QPointF pt = gpsToPixel(lat, 7.5);
        p.drawText(QPointF(4, pt.y() + 4),
                   QString::number(lat, 'f', 0) + "°N");
    }

    // ── Villes repères
    struct Ville { double lat, lng; QString nom; };
    QList<Ville> villes = {
                           {36.8190, 10.1658, "Tunis"},
                           {35.8256, 10.6369, "Sousse"},
                           {34.7406, 10.7603, "Sfax"},
                           {36.4610, 10.7357, "Nabeul"},
                           {33.8815, 10.0982, "Gabès"},
                           {33.5000,  9.9167, "Médenine"},
                           {37.2746,  9.8739, "Bizerte"},
                           {35.6781, 10.1000, "Kairouan"},
                           };
    p.setFont(QFont("Segoe UI", 7, QFont::Bold));
    for (const Ville &v : villes) {
        QPointF pos = gpsToPixel(v.lat, v.lng);
        // Point
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#1B3A57"));
        p.drawEllipse(pos, 3, 3);
        // Nom
        p.setPen(QColor("#1B3A57"));
        p.drawText(QPointF(pos.x() + 5, pos.y() - 3), v.nom);
    }

    // ── Dessin des conteneurs
    if (m_conteneurs.isEmpty()) {
        p.setFont(QFont("Segoe UI", 13, QFont::Bold));
        p.setPen(QColor("#C0392B"));
        p.drawText(rect(), Qt::AlignCenter,
                   "⚠️ Aucun conteneur trouvé\n"
                   "Vérifiez que la base de données contient\n"
                   "des coordonnées GPS valides (lat,lng)");
    }

    for (int i = 0; i < m_conteneurs.size(); i++) {
        const Conteneur &c = m_conteneurs[i];
        QString gps = c.getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;

        bool okLat, okLng;
        double lat = parts[0].trimmed().toDouble(&okLat);
        double lng = parts[1].trimmed().toDouble(&okLng);
        if (!okLat || !okLng) continue;
        if (lat < LAT_MIN || lat > LAT_MAX || lng < LNG_MIN || lng > LNG_MAX) continue;

        QPointF pos = gpsToPixel(lat, lng);

        QColor couleur = QColor("#27AE60"); // opérationnel
        if (c.getEtat().contains("maintenance", Qt::CaseInsensitive))
            couleur = QColor("#E67E22");
        else if (c.getEtat().contains("hors", Qt::CaseInsensitive))
            couleur = QColor("#E74C3C");

        bool hovered  = (i == m_hover);
        bool selected = (i == m_selected);

        drawTrashIcon(p, pos, couleur, hovered, selected, c.getId());

        // ── Tooltip au survol
        if (hovered) {
            QString info = QString("🗑️ Conteneur #%1\n"
                                   "📍 %2\n"
                                   "🌍 GPS: %3\n"
                                   "⚙️ État: %4\n"
                                   "📦 Cap.: %5 L")
                               .arg(c.getId())
                               .arg(c.getAdresseComplete().left(35))
                               .arg(gps)
                               .arg(c.getEtat())
                               .arg(c.getCapacite(), 0, 'f', 0);

            QFont tf("Segoe UI", 8);
            p.setFont(tf);
            QFontMetrics fm(tf);
            QStringList lines = info.split('\n');
            int maxW = 0;
            for (auto &l : lines) maxW = qMax(maxW, fm.horizontalAdvance(l));
            int boxW = maxW + 20;
            int boxH = lines.size() * (fm.height() + 2) + 14;

            QRectF box(pos.x() + 18, pos.y() - 12, boxW, boxH);
            if (box.right()  > W - 5) box.moveRight(pos.x() - 18);
            if (box.bottom() > H - 5) box.moveBottom(pos.y() + 12);

            p.setPen(Qt::NoPen);
            p.setBrush(QColor(0, 0, 0, 30));
            p.drawRoundedRect(box.adjusted(3, 3, 3, 3), 8, 8);

            p.setBrush(QColor("#1B2E42"));
            p.setPen(QPen(QColor("#4A8FAD"), 1));
            p.drawRoundedRect(box, 8, 8);

            p.setPen(Qt::white);
            double lineH = fm.height() + 2;
            for (int li = 0; li < lines.size(); li++) {
                p.drawText(QPointF(box.left() + 10,
                                   box.top() + 10 + li * lineH + fm.ascent()),
                           lines[li]);
            }
        }
    }

    // ── Légende
    int legW = 165, legH = 105;
    QRect leg(W - legW - 8, H - legH - 8, legW, legH);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 255, 255, 210));
    p.drawRoundedRect(leg, 10, 10);

    p.setFont(QFont("Segoe UI", 8, QFont::Bold));
    p.setPen(QColor("#1B3A57"));
    p.drawText(leg.adjusted(10, 8, 0, 0), "Légende");

    struct LegItem { QColor c; QString txt; };
    QList<LegItem> items = {
        {QColor("#27AE60"), "Opérationnel"},
        {QColor("#E67E22"), "En maintenance"},
        {QColor("#E74C3C"), "Hors service"}
    };
    int ly = leg.top() + 28;
    for (auto &item : items) {
        p.setPen(Qt::NoPen);
        p.setBrush(item.c);
        p.drawRoundedRect(leg.left() + 10, ly, 12, 12, 3, 3);
        p.setPen(QColor("#374151"));
        p.setFont(QFont("Segoe UI", 8));
        p.drawText(leg.left() + 28, ly + 10, item.txt);
        ly += 22;
    }

    p.setFont(QFont("Segoe UI", 7));
    p.setPen(QColor("#6B7280"));
    p.drawText(leg.adjusted(10, legH - 18, 0, 0),
               QString("%1 conteneur(s) affiché(s)").arg(m_conteneurs.size()));
}

// ── Gestion souris ───────────────────────────────────────────────
void CarteWidget::mouseMoveEvent(QMouseEvent *event)
{
    int ancien = m_hover;
    m_hover = -1;

    for (int i = 0; i < m_conteneurs.size(); i++) {
        QString gps = m_conteneurs[i].getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;
        bool ok1, ok2;
        double lat = parts[0].trimmed().toDouble(&ok1);
        double lng = parts[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;

        QPointF pos = gpsToPixel(lat, lng);
        if (QLineF(event->pos(), pos).length() < 18) {
            m_hover = i;
            setCursor(Qt::PointingHandCursor);
            break;
        }
    }
    if (m_hover == -1) setCursor(Qt::CrossCursor);
    if (m_hover != ancien) update();
}

void CarteWidget::mousePressEvent(QMouseEvent *event)
{
    for (int i = 0; i < m_conteneurs.size(); i++) {
        QString gps = m_conteneurs[i].getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;
        bool ok1, ok2;
        double lat = parts[0].trimmed().toDouble(&ok1);
        double lng = parts[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;

        QPointF pos = gpsToPixel(lat, lng);
        if (QLineF(event->pos(), pos).length() < 18) {
            m_selected = i;
            const Conteneur &c = m_conteneurs[i];

            if (m_infoLabel) {
                m_infoLabel->setText(
                    QString(
                        "<b style='color:#4A9FBD;'>🗑️ Conteneur #%1</b>"
                        " &nbsp;|&nbsp; "
                        "<b>%2</b><br>"
                        "📍 <b>Zone :</b> %3 &nbsp; "
                        "🌍 <b>GPS :</b> %4 &nbsp; "
                        "📦 <b>Capacité :</b> %5 L &nbsp; "
                        "⚙️ <b>État :</b> <span style='color:%6;'>%7</span> &nbsp; "
                        "🏢 <b>Type :</b> %8 &nbsp; "
                        "📅 <b>Dernière collecte :</b> %9"
                        )
                        .arg(c.getId())
                        .arg(c.getEtat())
                        .arg(c.getAdresseComplete())
                        .arg(c.getLocalisationGPS())
                        .arg(c.getCapacite(), 0, 'f', 0)
                        .arg(c.getEtat().contains("hors", Qt::CaseInsensitive)        ? "#E74C3C" :
                                 c.getEtat().contains("maintenance", Qt::CaseInsensitive) ? "#E67E22" : "#27AE60")
                        .arg(c.getEtat())
                        .arg(c.getTypePropriete())
                        .arg(c.getDateDerniereCollecte())
                    );
            }
            update();
            return;
        }
    }
    m_selected = -1;
    if (m_infoLabel)
        m_infoLabel->setText("👆 Cliquez sur une poubelle pour voir les détails du conteneur");
    update();
}

void CarteWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

// ============================================================
// Map Dialog
// ============================================================

Map::Map(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("🗺️ Carte des Conteneurs");
    setMinimumSize(950, 650);
    setStyleSheet("QDialog { background-color: #1E1E2E; }");

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setSpacing(0);

    // ── En-tête
    QWidget *header = new QWidget();
    header->setFixedHeight(52);
    header->setStyleSheet(
        "QWidget{background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #1B3A57,stop:1 #2C5F7C);}");
    QHBoxLayout *hLay = new QHBoxLayout(header);
    hLay->setContentsMargins(20, 0, 20, 0);

    QLabel *titre = new QLabel("🗺️  Carte des Conteneurs — Tunisie");
    titre->setStyleSheet("font-size:15px;font-weight:bold;color:white;background:transparent;");
    hLay->addWidget(titre);
    hLay->addStretch();

    QLabel *compteur = new QLabel();
    compteur->setStyleSheet("color:#A0C8E0;font-size:12px;background:transparent;");
    hLay->addWidget(compteur);
    hLay->addSpacing(20);

    QPushButton *btnFermer = new QPushButton("✕  Fermer");
    btnFermer->setFixedSize(96, 34);
    btnFermer->setStyleSheet(
        "QPushButton{background:#C0392B;color:white;font-size:13px;"
        "font-weight:600;border:none;border-radius:6px;}"
        "QPushButton:hover{background:#E74C3C;}");
    connect(btnFermer, &QPushButton::clicked, this, &QDialog::accept);
    hLay->addWidget(btnFermer);
    mainLay->addWidget(header);

    // ── Carte
    m_carte = new CarteWidget(this);
    mainLay->addWidget(m_carte, 1);

    // ── Bande info bas
    m_infoBox = new QLabel("👆 Cliquez sur une poubelle pour voir les détails du conteneur");
    m_infoBox->setFixedHeight(52);
    m_infoBox->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_infoBox->setWordWrap(true);
    m_infoBox->setTextFormat(Qt::RichText);
    m_infoBox->setStyleSheet(
        "QLabel{background:#2C3E50;color:#ECF0F1;font-size:12px;"
        "padding:6px 16px;border-top:2px solid #2C5F7C;}");
    mainLay->addWidget(m_infoBox);

    m_carte->setInfoLabel(m_infoBox);

    // ── Chargement
    QList<Conteneur> liste = Conteneur::getAll();
    m_carte->setConteneurs(liste);
    compteur->setText(QString("📍 %1 conteneur(s)").arg(liste.size()));
}
