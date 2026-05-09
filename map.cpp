#include "map.h"
#include <QApplication>
#include <QScreen>
#include <QFontMetrics>
#include <QPainterPath>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QGraphicsDropShadowEffect>
#include <cmath>
#include <algorithm>

// ════════════════════════════════════════════════════════════════
// Constants
// ════════════════════════════════════════════════════════════════
static constexpr double PI = 3.14159265358979323846;

// ════════════════════════════════════════════════════════════════
// OSM coordinate math
// ════════════════════════════════════════════════════════════════
double CarteWidget::lngToTileX(double lng, int z)
{
    return (lng + 180.0) / 360.0 * (1 << z);
}

double CarteWidget::latToTileY(double lat, int z)
{
    double latR = lat * PI / 180.0;
    return (1.0 - std::log(std::tan(latR) + 1.0 / std::cos(latR)) / PI)
           / 2.0 * (1 << z);
}

// ════════════════════════════════════════════════════════════════
// CarteWidget  —  constructor
// ════════════════════════════════════════════════════════════════
CarteWidget::CarteWidget(QWidget *parent) : QWidget(parent)
{
    setMinimumSize(600, 480);
    setMouseTracking(true);
    setCursor(Qt::OpenHandCursor);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setFocusPolicy(Qt::WheelFocus);

    m_nam = new QNetworkAccessManager(this);
    connect(m_nam, &QNetworkAccessManager::finished,
            this,  &CarteWidget::onTileDownloaded);

    // Pulse timer for selected marker animation
    m_pulseTimer = new QTimer(this);
    m_pulseTimer->setInterval(30);
    connect(m_pulseTimer, &QTimer::timeout, this, [this]() {
        m_pulsePhase += 0.08;
        if (m_pulsePhase > 2 * PI) m_pulsePhase -= 2 * PI;
        update();
    });
    m_pulseTimer->start();
}

CarteWidget::~CarteWidget()
{
    m_nam->deleteLater();
}

// ════════════════════════════════════════════════════════════════
// Data setters
// ════════════════════════════════════════════════════════════════
void CarteWidget::setConteneurs(const QList<Conteneur> &liste)
{
    m_conteneurs = liste;
    m_hover    = -1;
    m_selected = -1;
    applyFilter();
    emitStats();
    update();
}

void CarteWidget::setInfoLabel(QLabel *label) { m_infoLabel = label; }

void CarteWidget::setFilterEtat(const QString &etat)
{
    m_filterEtat = etat;
    m_hover    = -1;
    m_selected = -1;
    applyFilter();
    emitStats();
    update();
}

void CarteWidget::setOptimized(bool opt)
{
    m_optimized = opt;
    if (opt) computeRoute();
    update();
}

// ════════════════════════════════════════════════════════════════
// Filter & stats
// ════════════════════════════════════════════════════════════════
void CarteWidget::applyFilter()
{
    m_visible.clear();
    for (const Conteneur &c : m_conteneurs) {
        if (!m_filterEtat.isEmpty()) {
            QString etat = c.getEtat().toLower();
            if (m_filterEtat == "operationnel"
                && !(!etat.contains("hors") && !etat.contains("maintenance")))
                continue;
            if (m_filterEtat == "maintenance"
                && !etat.contains("maintenance"))
                continue;
            if (m_filterEtat == "horsservice"
                && !etat.contains("hors"))
                continue;
        }
        m_visible.append(c);
    }
    if (m_optimized) computeRoute();
}

void CarteWidget::emitStats()
{
    int total = m_conteneurs.size();
    int ok = 0, maint = 0, hs = 0;
    for (const Conteneur &c : m_conteneurs) {
        QString e = c.getEtat().toLower();
        if (e.contains("hors"))        hs++;
        else if (e.contains("maintenance")) maint++;
        else                               ok++;
    }
    emit statsChanged(total, ok, maint, hs);
}

// ════════════════════════════════════════════════════════════════
// Coordinate helpers
// ════════════════════════════════════════════════════════════════
QPointF CarteWidget::gpsToPixel(double lat, double lng) const
{
    double cx = lngToTileX(m_centerLng, m_zoom);
    double cy = latToTileY(m_centerLat, m_zoom);
    double px = lngToTileX(lng, m_zoom);
    double py = latToTileY(lat, m_zoom);
    double dx = (px - cx) * TILE_SIZE;
    double dy = (py - cy) * TILE_SIZE;
    return QPointF(width() / 2.0 + dx, height() / 2.0 + dy);
}

void CarteWidget::pixelToGps(QPointF px, double &lat, double &lng) const
{
    double cx = lngToTileX(m_centerLng, m_zoom);
    double cy = latToTileY(m_centerLat, m_zoom);
    double tx = cx + (px.x() - width()  / 2.0) / TILE_SIZE;
    double ty = cy + (px.y() - height() / 2.0) / TILE_SIZE;
    int n = 1 << m_zoom;
    lng = tx / n * 360.0 - 180.0;
    double latR = std::atan(std::sinh(PI * (1.0 - 2.0 * ty / n)));
    lat = latR * 180.0 / PI;
}

// ════════════════════════════════════════════════════════════════
// Zoom controls
// ════════════════════════════════════════════════════════════════
void CarteWidget::zoomIn()
{
    if (m_zoom < ZOOM_MAX_OSM) { m_zoom++; m_tileCache.clear(); update(); }
}

void CarteWidget::zoomOut()
{
    if (m_zoom > ZOOM_MIN_OSM) { m_zoom--; m_tileCache.clear(); update(); }
}

void CarteWidget::resetView()
{
    m_zoom      = 7;
    m_centerLat = 33.8869;
    m_centerLng = 9.5375;
    m_tileCache.clear();
    m_selected = -1;
    update();
}

// ════════════════════════════════════════════════════════════════
// OSM tile fetching
// ════════════════════════════════════════════════════════════════
void CarteWidget::requestTile(int z, int x, int y)
{
    int n = 1 << z;
    // Wrap x only
    x = ((x % n) + n) % n;
    if (y < 0 || y >= n) return;

    TileKey key{z, x, y};
    if (m_tileCache.contains(key) || m_pending.contains(key)) return;
    m_pending.insert(key);

    // Use CartoDB Positron tiles — clean style, no maritime boundary rings
    static int subdomain = 0;
    char sub = 'a' + (subdomain++ % 4);   // CartoDB has 4 subdomains: a-d
    QString url = QString("https://%1.basemaps.cartocdn.com/light_all/%2/%3/%4.png")
                      .arg(sub).arg(z).arg(x).arg(y);

    QNetworkRequest req(url);
    req.setRawHeader("User-Agent", "WasteCollectionApp/1.0 Qt/MapWidget");
    // Store key in request so we can recover it on reply
    req.setAttribute(QNetworkRequest::User,
                     QVariant::fromValue(QList<int>{z, x, y}));
    m_nam->get(req);
}

void CarteWidget::onTileDownloaded(QNetworkReply *reply)
{
    reply->deleteLater();
    auto list = reply->request()
                    .attribute(QNetworkRequest::User)
                    .value<QList<int>>();
    if (list.size() < 3) return;
    TileKey key{list[0], list[1], list[2]};
    m_pending.remove(key);

    if (reply->error() != QNetworkReply::NoError) return;

    QPixmap pm;
    if (!pm.loadFromData(reply->readAll())) return;

    m_tileCache[key] = pm;
    update();
}

// ════════════════════════════════════════════════════════════════
// Draw OSM tiles
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawTiles(QPainter &p)
{
    int W = width(), H = height();
    double cx = lngToTileX(m_centerLng, m_zoom);
    double cy = latToTileY(m_centerLat, m_zoom);

    // Tile coords of top-left corner
    double x0 = cx - W / (2.0 * TILE_SIZE);
    double y0 = cy - H / (2.0 * TILE_SIZE);

    int txMin = (int)std::floor(x0);
    int tyMin = (int)std::floor(y0);
    int txMax = (int)std::ceil(x0 + W / (double)TILE_SIZE);
    int tyMax = (int)std::ceil(y0 + H / (double)TILE_SIZE);

    int n = 1 << m_zoom;

    for (int ty = tyMin; ty <= tyMax; ty++) {
        for (int tx = txMin; tx <= txMax; tx++) {
            int wx = (int)std::round((tx - x0) * TILE_SIZE);
            int wy = (int)std::round((ty - y0) * TILE_SIZE);
            QRect dst(wx, wy, TILE_SIZE, TILE_SIZE);

            int wrappedX = ((tx % n) + n) % n;
            if (ty < 0 || ty >= n) continue;

            TileKey key{m_zoom, wrappedX, ty};

            if (m_tileCache.contains(key)) {
                p.drawPixmap(dst, m_tileCache[key]);
            } else {
                // Placeholder
                p.fillRect(dst, QColor("#E8EEF4"));
                p.setPen(QColor("#C5D0DC"));
                p.drawRect(dst);
                requestTile(m_zoom, tx, ty);
            }
        }
    }
}

// ════════════════════════════════════════════════════════════════
// Route optimization  (nearest-neighbor TSP heuristic)
// ════════════════════════════════════════════════════════════════
double CarteWidget::haversineKm(double lat1, double lng1,
                                double lat2, double lng2)
{
    double dLat = (lat2 - lat1) * PI / 180.0;
    double dLng = (lng2 - lng1) * PI / 180.0;
    double a = std::sin(dLat/2)*std::sin(dLat/2)
               + std::cos(lat1*PI/180.0)*std::cos(lat2*PI/180.0)
                     * std::sin(dLng/2)*std::sin(dLng/2);
    return 6371.0 * 2.0 * std::atan2(std::sqrt(a), std::sqrt(1-a));
}

void CarteWidget::computeRoute()
{
    m_routeOrder.clear();
    m_routeKm    = 0.0;
    m_routeStops = 0;

    // Parse GPS for all visible conteneurs
    struct Pt { int idx; double lat, lng; };
    QVector<Pt> pts;
    for (int i = 0; i < m_visible.size(); i++) {
        QString gps = m_visible[i].getLocalisationGPS().trimmed();
        QStringList p = gps.split(',');
        if (p.size() < 2) continue;
        bool ok1, ok2;
        double lat = p[0].trimmed().toDouble(&ok1);
        double lng = p[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;
        if (lat < LAT_MIN || lat > LAT_MAX || lng < LNG_MIN || lng > LNG_MAX) continue;
        pts.append({i, lat, lng});
    }
    if (pts.size() < 2) return;

    // Nearest-neighbor from index 0
    QVector<bool> visited(pts.size(), false);
    int cur = 0;
    visited[cur] = true;
    m_routeOrder.append(pts[cur].idx);

    for (int step = 1; step < pts.size(); step++) {
        double bestDist = 1e18;
        int    bestNext = -1;
        for (int j = 0; j < pts.size(); j++) {
            if (visited[j]) continue;
            double d = haversineKm(pts[cur].lat, pts[cur].lng,
                                   pts[j].lat,   pts[j].lng);
            if (d < bestDist) { bestDist = d; bestNext = j; }
        }
        if (bestNext < 0) break;
        m_routeKm += bestDist;
        visited[bestNext] = true;
        m_routeOrder.append(pts[bestNext].idx);
        cur = bestNext;
    }
    m_routeStops = m_routeOrder.size();
    emit routeCalculated(m_routeKm, m_routeStops);
}

// ════════════════════════════════════════════════════════════════
// paintEvent
// ════════════════════════════════════════════════════════════════
void CarteWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    p.setRenderHint(QPainter::SmoothPixmapTransform);

    // 1 – tiles
    drawTiles(p);

    // 2 – route
    if (m_optimized && m_routeOrder.size() >= 2)
        drawRoute(p);

    // 3 – markers
    for (int i = 0; i < m_visible.size(); i++) {
        const Conteneur &c = m_visible[i];
        QString gps = c.getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;
        bool ok1, ok2;
        double lat = parts[0].trimmed().toDouble(&ok1);
        double lng = parts[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;
        if (lat < LAT_MIN || lat > LAT_MAX || lng < LNG_MIN || lng > LNG_MAX) continue;

        QPointF pos = gpsToPixel(lat, lng);
        QString etat = c.getEtat().toLower();
        QColor couleur = etat.contains("hors")        ? QColor("#E74C3C")
                         : etat.contains("maintenance") ? QColor("#E67E22")
                                                        : QColor("#27AE60");

        drawMarker(p, pos, couleur, i == m_hover, i == m_selected,
                   c.getId(), c.getCapacite(), c.getEtat());

        // Tooltip
        if (i == m_hover)
            drawTooltip(p, pos, c);
    }

    // 4 – legend, scale, zoom badge
    drawLegend(p);
    drawScale(p);
    drawZoomBadge(p);

    // 5 – attribution
    p.setFont(QFont("Segoe UI", 7));
    p.setPen(QColor(80, 80, 80, 180));
    p.drawText(rect().adjusted(4, 0, -4, -4),
               Qt::AlignBottom | Qt::AlignRight,
               "© OpenStreetMap contributors");
}

// ════════════════════════════════════════════════════════════════
// Marker drawing  (pin-style)
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawMarker(QPainter &p, QPointF center, QColor color,
                             bool hovered, bool selected,
                             int id, double capacite, const QString &etat)
{
    Q_UNUSED(capacite); Q_UNUSED(etat);
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    double scale = hovered ? 1.35 : (selected ? 1.2 : 1.0);
    double r     = 16.0 * scale;
    double cx    = center.x();
    double cy    = center.y();

    // Pulse ring for selected
    if (selected) {
        double pulse = 0.55 + 0.45 * std::sin(m_pulsePhase);
        double pr    = r + 10.0 * pulse;
        QColor pc    = color;
        pc.setAlpha(int(140 * (1.0 - pulse)));
        p.setPen(QPen(pc, 2.5));
        p.setBrush(Qt::NoBrush);
        p.drawEllipse(QPointF(cx, cy - r * 0.2), pr, pr);
    }

    // Drop shadow
    QRadialGradient shadow(cx + 2, cy + r + 3, r * 1.1);
    shadow.setColorAt(0.0, QColor(0, 0, 0, 70));
    shadow.setColorAt(1.0, QColor(0, 0, 0, 0));
    p.setPen(Qt::NoPen);
    p.setBrush(shadow);
    p.drawEllipse(QPointF(cx + 2, cy + r * 0.5), r, r * 0.35);

    // Pin body (teardrop)
    QPainterPath pin;
    pin.moveTo(cx, cy + r * 1.2);           // tip (bottom)
    pin.cubicTo(cx - r * 0.6, cy + r * 0.3,
                cx - r,       cy - r * 0.5,
                cx,           cy - r);       // top arc left
    pin.cubicTo(cx + r,       cy - r * 0.5,
                cx + r * 0.6, cy + r * 0.3,
                cx,           cy + r * 1.2); // back to tip

    // Gradient fill
    QRadialGradient grad(cx - r * 0.25, cy - r * 0.35, r * 1.1);
    grad.setColorAt(0.0, color.lighter(135));
    grad.setColorAt(0.6, color);
    grad.setColorAt(1.0, color.darker(130));
    p.setBrush(grad);
    p.setPen(QPen(color.darker(150), 1.2 * scale));
    p.drawPath(pin);

    // Inner circle (white)
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 255, 255, 220));
    p.drawEllipse(QPointF(cx, cy - r * 0.15), r * 0.52, r * 0.52);

    // ID text
    p.setPen(color.darker(170));
    QFont f("Segoe UI", qMax(6.0, 8.0 * scale), QFont::Bold);
    p.setFont(f);
    QRectF idRect(cx - r * 0.52, cy - r * 0.15 - r * 0.52,
                  r * 1.04, r * 1.04);
    p.drawText(idRect, Qt::AlignCenter, QString::number(id));

    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Tooltip
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawTooltip(QPainter &p, QPointF pos, const Conteneur &c)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    QString etat  = c.getEtat();
    QString etatC = etat.toLower().contains("hors")        ? "#E74C3C"
                    : etat.toLower().contains("maintenance") ? "#E67E22"
                                                             : "#2ECC71";

    QStringList lines = {
        QString("🗑️ Conteneur #%1").arg(c.getId()),
        QString("📍 %1").arg(c.getAdresseComplete().left(32)),
        QString("📦 Capacité : %1 L").arg(c.getCapacite(), 0, 'f', 0),
        QString("⚙️ État : %1").arg(etat),
        QString("📅 Collecte : %1").arg(c.getDateDerniereCollecte())
    };

    QFont tf("Segoe UI", 8);
    p.setFont(tf);
    QFontMetrics fm(tf);
    int lineH = fm.height() + 3;
    int maxW  = 0;
    for (auto &l : lines) maxW = qMax(maxW, fm.horizontalAdvance(l));
    int boxW = maxW + 22;
    int boxH = lines.size() * lineH + 18;

    int W = width(), H = height();
    QRectF box(pos.x() + 22, pos.y() - 30, boxW, boxH);
    if (box.right()  > W - 8) box.moveRight(pos.x() - 22);
    if (box.bottom() > H - 8) box.moveBottom(pos.y() - 6);
    if (box.top()    < 8)     box.moveTop(8);

    // Shadow
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 35));
    p.drawRoundedRect(box.adjusted(4, 4, 4, 4), 10, 10);

    // Background
    QLinearGradient bg(box.topLeft(), box.bottomLeft());
    bg.setColorAt(0.0, QColor("#1E2D3D"));
    bg.setColorAt(1.0, QColor("#15202E"));
    p.setBrush(bg);
    p.setPen(QPen(QColor(etatC), 1.5));
    p.drawRoundedRect(box, 10, 10);

    // Colored top stripe
    QRectF stripe(box.left(), box.top(), box.width(), 5);
    p.setBrush(QColor(etatC));
    p.setPen(Qt::NoPen);
    p.drawRoundedRect(stripe, 10, 10);
    p.drawRect(QRectF(box.left(), box.top() + 2, box.width(), 3));

    // Text
    double ty = box.top() + 12;
    for (int i = 0; i < lines.size(); i++) {
        p.setPen(i == 0 ? QColor(etatC) : QColor("#D0E0F0"));
        if (i == 0) {
            QFont bold = tf; bold.setBold(true); bold.setPointSize(9);
            p.setFont(bold);
        } else {
            p.setFont(tf);
        }
        p.drawText(QPointF(box.left() + 11, ty + fm.ascent()), lines[i]);
        ty += lineH;
    }

    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Route drawing
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawRoute(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);

    // Build pixel path in optimized order
    QVector<QPointF> pts;
    for (int idx : m_routeOrder) {
        if (idx < 0 || idx >= m_visible.size()) continue;
        QString gps = m_visible[idx].getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;
        bool ok1, ok2;
        double lat = parts[0].trimmed().toDouble(&ok1);
        double lng = parts[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;
        pts.append(gpsToPixel(lat, lng));
    }
    if (pts.size() < 2) { p.restore(); return; }

    // Build smooth path through points (Catmull-Rom spline)
    auto catmullRom = [](QPainterPath &path, const QVector<QPointF> &points) {
        if (points.size() < 2) return;
        path.moveTo(points[0]);
        for (int i = 0; i < points.size() - 1; i++) {
            QPointF p0 = points[qMax(i-1, 0)];
            QPointF p1 = points[i];
            QPointF p2 = points[i+1];
            QPointF p3 = points[qMin(i+2, (int)points.size()-1)];
            QPointF cp1 = p1 + (p2 - p0) / 6.0;
            QPointF cp2 = p2 - (p3 - p1) / 6.0;
            path.cubicTo(cp1, cp2, p2);
        }
    };

    QPainterPath routePath;
    catmullRom(routePath, pts);

    // Outer glow
    QPen glowPen(QColor(52, 152, 219, 55), 10, Qt::SolidLine,
                 Qt::RoundCap, Qt::RoundJoin);
    p.setPen(glowPen);
    p.drawPath(routePath);

    // White outline
    p.setPen(QPen(Qt::white, 4.5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.drawPath(routePath);

    // Main route line (animated dash phase via m_pulsePhase)
    QPen routePen(QColor("#3498DB"), 2.8, Qt::CustomDashLine,
                  Qt::RoundCap, Qt::RoundJoin);
    routePen.setDashPattern({7, 4});
    routePen.setDashOffset(m_pulsePhase * 3.0);  // animated flow
    p.setPen(routePen);
    p.drawPath(routePath);

    // Directional arrows on each segment
    p.setPen(Qt::NoPen);
    for (int i = 0; i + 1 < pts.size(); i++) {
        QPointF from = pts[i], to = pts[i+1];
        QPointF mid  = (from * 0.45 + to * 0.55);
        QPointF dir  = to - from;
        double  len  = std::sqrt(dir.x()*dir.x() + dir.y()*dir.y());
        if (len < 30) continue;
        dir /= len;
        QPointF perp(-dir.y(), dir.x());
        QPolygonF arr;
        arr << mid + dir*9 << mid - dir*4 + perp*5 << mid - dir*4 - perp*5;
        p.setBrush(QColor("#2980B9"));
        p.drawPolygon(arr);
    }

    // Step badges
    QFont bf("Segoe UI", 7, QFont::Bold);
    p.setFont(bf);
    QFontMetrics fm(bf);
    for (int i = 0; i < pts.size(); i++) {
        QPointF pt = pts[i];
        QString num = QString::number(i + 1);
        int bw = fm.horizontalAdvance(num) + 10;
        QRectF badge(pt.x() - bw/2.0, pt.y() - 38, bw, 15);
        p.setPen(Qt::NoPen);
        p.setBrush(QColor("#2C3E50"));
        p.drawRoundedRect(badge, 4, 4);
        p.setPen(QColor("#ECF0F1"));
        p.drawText(badge, Qt::AlignCenter, num);
    }

    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Legend
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawLegend(QPainter &p)
{
    p.save();
    p.setRenderHint(QPainter::Antialiasing, true);
    int W = width(), H = height();

    int legW = 180, legH = m_optimized ? 140 : 118;
    QRect leg(W - legW - 10, H - legH - 10, legW, legH);

    // Shadow
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 30));
    p.drawRoundedRect(leg.adjusted(3, 3, 3, 3), 10, 10);

    // Glass panel
    QLinearGradient lgBg(leg.topLeft(), leg.bottomLeft());
    lgBg.setColorAt(0.0, QColor(255, 255, 255, 235));
    lgBg.setColorAt(1.0, QColor(240, 248, 255, 215));
    p.setBrush(lgBg);
    p.setPen(QPen(QColor("#B0C8DE"), 1));
    p.drawRoundedRect(leg, 10, 10);

    // Title
    p.setFont(QFont("Segoe UI", 8, QFont::Bold));
    p.setPen(QColor("#1B3A57"));
    p.drawText(leg.adjusted(12, 8, -8, 0), Qt::AlignTop, "Légende");

    struct LegItem { QColor c; QString txt; };
    QList<LegItem> items = {
        {QColor("#27AE60"), "Opérationnel"},
        {QColor("#E67E22"), "En maintenance"},
        {QColor("#E74C3C"), "Hors service"}
    };

    int ly = leg.top() + 28;
    p.setFont(QFont("Segoe UI", 8));
    for (auto &item : items) {
        // Pin-like dot
        QRadialGradient dot(leg.left()+16, ly+6, 7);
        dot.setColorAt(0.0, item.c.lighter(130));
        dot.setColorAt(1.0, item.c);
        p.setPen(Qt::NoPen);
        p.setBrush(dot);
        p.drawEllipse(QPoint(leg.left()+16, ly+6), 6, 6);
        p.setPen(QColor("#2D3748"));
        p.drawText(leg.left() + 30, ly + 10, item.txt);
        ly += 24;
    }

    if (m_optimized) {
        // Route dash sample
        p.setPen(QPen(QColor("#3498DB"), 2.5, Qt::DashLine));
        p.drawLine(leg.left()+10, ly+6, leg.left()+30, ly+6);
        p.setPen(QColor("#2D3748"));
        p.setFont(QFont("Segoe UI", 8));
        p.drawText(leg.left() + 36, ly + 9, "Route optimisée");
        ly += 22;

        // Distance
        p.setPen(QColor("#6B7280"));
        p.setFont(QFont("Segoe UI", 7, QFont::Bold));
        p.drawText(leg.adjusted(10, legH-28, 0, 0), Qt::AlignTop,
                   QString("Total : %1 km  |  %2 arrêts")
                       .arg(m_routeKm, 0, 'f', 1).arg(m_routeStops));
    }

    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Scale bar
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawScale(QPainter &p)
{
    p.save();
    // Compute metres per pixel at current zoom + latitude
    double metersPerPx = 156543.03392 * std::cos(m_centerLat * PI / 180.0)
                         / (1 << m_zoom);
    // Choose a nice round scale length
    double targetPx = 80.0;
    double targetM  = targetPx * metersPerPx;
    // Round to nice number
    double mag = std::pow(10.0, std::floor(std::log10(targetM)));
    double nice = targetM / mag;
    if (nice < 1.5) nice = 1;
    else if (nice < 3.5) nice = 2;
    else if (nice < 7.5) nice = 5;
    else nice = 10;
    nice *= mag;
    int barPx = (int)(nice / metersPerPx);

    QString label = nice >= 1000 ? QString("%1 km").arg(nice/1000, 0, 'f', 0)
                                 : QString("%1 m").arg((int)nice);

    int bx = 12, by = height() - 28;
    // Background
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255,255,255,180));
    p.drawRoundedRect(bx-4, by-4, barPx+8, 20, 4, 4);

    // Bar
    p.setBrush(QColor("#2C5F7C"));
    p.drawRect(bx, by+6, barPx/2, 5);
    p.setBrush(Qt::white);
    p.drawRect(bx+barPx/2, by+6, barPx/2, 5);
    p.setPen(QPen(QColor("#1B3A57"), 1.2));
    p.setBrush(Qt::NoBrush);
    p.drawRect(bx, by+6, barPx, 5);

    p.setPen(QColor("#1B3A57"));
    p.setFont(QFont("Segoe UI", 7, QFont::Bold));
    p.drawText(bx, by+4, label);

    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Zoom badge
// ════════════════════════════════════════════════════════════════
void CarteWidget::drawZoomBadge(QPainter &p)
{
    p.save();
    QString txt = QString("Zoom %1").arg(m_zoom);
    QFont f("Segoe UI", 8, QFont::Bold);
    p.setFont(f);
    QFontMetrics fm(f);
    int bw = fm.horizontalAdvance(txt) + 14;
    QRect r(10, 10, bw, fm.height()+10);
    p.setPen(Qt::NoPen);
    p.setBrush(QColor(27, 58, 87, 210));
    p.drawRoundedRect(r, 5, 5);
    p.setPen(QColor("#A0D4F0"));
    p.drawText(r, Qt::AlignCenter, txt);
    p.restore();
}

// ════════════════════════════════════════════════════════════════
// Mouse / keyboard events
// ════════════════════════════════════════════════════════════════
void CarteWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Check marker hit first
        for (int i = 0; i < m_visible.size(); i++) {
            QString gps = m_visible[i].getLocalisationGPS().trimmed();
            QStringList parts = gps.split(',');
            if (parts.size() < 2) continue;
            bool ok1, ok2;
            double lat = parts[0].trimmed().toDouble(&ok1);
            double lng = parts[1].trimmed().toDouble(&ok2);
            if (!ok1 || !ok2) continue;
            QPointF pos = gpsToPixel(lat, lng);
            if (QLineF(event->pos(), pos).length() < 20) {
                m_selected = i;
                const Conteneur &c = m_visible[i];
                emit conteneurSelected(c);
                if (m_infoLabel) {
                    QString etatC = c.getEtat().toLower().contains("hors")        ? "#E74C3C"
                                    : c.getEtat().toLower().contains("maintenance") ? "#E67E22"
                                                                                    : "#27AE60";
                    m_infoLabel->setText(
                        QString("<b style='color:#4A9FBD;'>🗑️ Conteneur #%1</b>"
                                " &nbsp;|&nbsp; <b>%2</b><br>"
                                "📍 <b>Zone :</b> %3 &nbsp; "
                                "🌍 <b>GPS :</b> %4 &nbsp; "
                                "📦 <b>Capacité :</b> %5 L &nbsp; "
                                "⚙️ <b>État :</b> <span style='color:%6;'>%7</span> &nbsp; "
                                "🏢 <b>Type :</b> %8 &nbsp; "
                                "📅 <b>Dernière collecte :</b> %9")
                            .arg(c.getId()).arg(c.getEtat())
                            .arg(c.getAdresseComplete())
                            .arg(c.getLocalisationGPS())
                            .arg(c.getCapacite(), 0, 'f', 0)
                            .arg(etatC).arg(c.getEtat())
                            .arg(c.getTypePropriete())
                            .arg(c.getDateDerniereCollecte())
                        );
                }
                update();
                return;
            }
        }
        // Start panning
        m_panning  = true;
        m_panStart = event->pos();
        m_panLat0  = m_centerLat;
        m_panLng0  = m_centerLng;
        m_selected = -1;
        if (m_infoLabel)
            m_infoLabel->setText("👆 Cliquez sur un marqueur pour voir les détails du conteneur");
        setCursor(Qt::ClosedHandCursor);
        update();
    }
    else if (event->button() == Qt::RightButton
             || event->button() == Qt::MiddleButton) {
        m_panning  = true;
        m_panStart = event->pos();
        m_panLat0  = m_centerLat;
        m_panLng0  = m_centerLng;
        setCursor(Qt::ClosedHandCursor);
    }
    event->accept();
}

void CarteWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (m_panning) {
        m_panning = false;
        setCursor(Qt::OpenHandCursor);
    }
    event->accept();
}

void CarteWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (m_panning) {
        // Convert pixel delta → GPS delta
        QPointF oldPx = m_panStart;
        QPointF newPx = event->pos();

        double lat0, lng0, lat1, lng1;
        pixelToGps(oldPx, lat0, lng0);
        pixelToGps(newPx, lat1, lng1);

        m_centerLat = qBound(LAT_MIN, m_panLat0  - (lat1 - lat0), LAT_MAX);
        m_centerLng = qBound(LNG_MIN, m_panLng0  - (lng1 - lng0), LNG_MAX);
        update();
        event->accept();
        return;
    }

    // Hover detection
    int ancien = m_hover;
    m_hover = -1;
    for (int i = 0; i < m_visible.size(); i++) {
        QString gps = m_visible[i].getLocalisationGPS().trimmed();
        QStringList parts = gps.split(',');
        if (parts.size() < 2) continue;
        bool ok1, ok2;
        double lat = parts[0].trimmed().toDouble(&ok1);
        double lng = parts[1].trimmed().toDouble(&ok2);
        if (!ok1 || !ok2) continue;
        QPointF pos = gpsToPixel(lat, lng);
        if (QLineF(event->pos(), pos).length() < 20) {
            m_hover = i;
            setCursor(Qt::PointingHandCursor);
            break;
        }
    }
    if (m_hover == -1) setCursor(Qt::OpenHandCursor);
    if (m_hover != ancien) update();
}

void CarteWidget::wheelEvent(QWheelEvent *event)
{
    // Get GPS under cursor before zoom
    QPointF cursorPx;
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    cursorPx = event->position();
#else
    cursorPx = event->pos();
#endif
    double latUnder, lngUnder;
    pixelToGps(cursorPx, latUnder, lngUnder);

    bool zoomedIn = event->angleDelta().y() > 0;
    if (zoomedIn && m_zoom < ZOOM_MAX_OSM)       m_zoom++;
    else if (!zoomedIn && m_zoom > ZOOM_MIN_OSM) m_zoom--;
    else { event->accept(); return; }

    // Re-center so the point under cursor stays fixed
    double afterLat, afterLng;
    pixelToGps(cursorPx, afterLat, afterLng);
    m_centerLat = qBound(LAT_MIN, m_centerLat + (latUnder - afterLat), LAT_MAX);
    m_centerLng = qBound(LNG_MIN, m_centerLng + (lngUnder - afterLng), LNG_MAX);

    m_tileCache.clear();
    update();
    event->accept();
}

void CarteWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    update();
}

// ════════════════════════════════════════════════════════════════
// SidePanel
// ════════════════════════════════════════════════════════════════
SidePanel::SidePanel(QWidget *parent) : QWidget(parent)
{
    setFixedWidth(240);
    setStyleSheet("QWidget { background: #1A2535; border-left: 1px solid #2C3E50; }");

    QVBoxLayout *lay = new QVBoxLayout(this);
    lay->setContentsMargins(0, 0, 0, 0);
    lay->setSpacing(0);

    // Header
    QWidget *hdr = new QWidget();
    hdr->setFixedHeight(44);
    hdr->setStyleSheet("background: qlineargradient(x1:0,y1:0,x2:1,y2:0,"
                       "stop:0 #1B3A57,stop:1 #2C5F7C);");
    QHBoxLayout *hLay = new QHBoxLayout(hdr);
    hLay->setContentsMargins(12, 0, 12, 0);
    QLabel *hdrLbl = new QLabel("📊 Tableau de bord");
    hdrLbl->setStyleSheet("color:white;font-weight:bold;font-size:13px;"
                          "background:transparent;");
    hLay->addWidget(hdrLbl);
    lay->addWidget(hdr);

    // Stats block
    m_statFrame = new QFrame();
    m_statFrame->setStyleSheet("QFrame{background:#1E2D3D;margin:8px;border-radius:8px;}");
    QVBoxLayout *sfLay = new QVBoxLayout(m_statFrame);
    sfLay->setContentsMargins(10, 8, 10, 8);
    sfLay->setSpacing(6);

    auto mkStat = [&](QLabel *&lbl, QProgressBar *&pb,
                      const QString &ico, const QString &color) {
        QHBoxLayout *row = new QHBoxLayout();
        row->setSpacing(6);
        QLabel *ico_lbl = new QLabel(ico);
        ico_lbl->setStyleSheet("background:transparent;font-size:14px;");
        lbl = new QLabel("—");
        lbl->setStyleSheet(QString("color:%1;font-weight:bold;font-size:12px;"
                                   "background:transparent;").arg(color));
        row->addWidget(ico_lbl);
        row->addWidget(lbl);
        row->addStretch();
        sfLay->addLayout(row);
        pb = new QProgressBar();
        pb->setFixedHeight(5);
        pb->setRange(0, 100);
        pb->setValue(0);
        pb->setTextVisible(false);
        pb->setStyleSheet(QString("QProgressBar{background:#2C3E50;border-radius:2px;}"
                                  "QProgressBar::chunk{background:%1;border-radius:2px;}").arg(color));
        sfLay->addWidget(pb);
    };

    m_statTotal = new QLabel("📍 Total : —");
    m_statTotal->setStyleSheet("color:#A0C8E0;font-size:12px;font-weight:bold;"
                               "background:transparent;");
    sfLay->addWidget(m_statTotal);

    mkStat(m_statOk,    m_pbOk,    "🟢 Opérationnel",  "#27AE60");
    mkStat(m_statMaint, m_pbMaint, "🟠 Maintenance",    "#E67E22");
    mkStat(m_statHs,    m_pbHs,    "🔴 Hors service",   "#E74C3C");

    lay->addWidget(m_statFrame);

    // Route info
    m_routeLbl = new QLabel("─ Route non calculée");
    m_routeLbl->setWordWrap(true);
    m_routeLbl->setAlignment(Qt::AlignTop);
    m_routeLbl->setStyleSheet("color:#7FB3CC;font-size:11px;padding:8px 12px;"
                              "background:transparent;");
    lay->addWidget(m_routeLbl);

    // Separator
    QFrame *sep = new QFrame();
    sep->setFixedHeight(1);
    sep->setStyleSheet("background:#2C3E50;margin:0 8px;");
    lay->addWidget(sep);

    // Details card
    m_titleLbl = new QLabel("Sélectionnez un conteneur");
    m_titleLbl->setAlignment(Qt::AlignTop);
    m_titleLbl->setWordWrap(true);
    m_titleLbl->setStyleSheet("color:#A0C8E0;font-size:12px;font-weight:bold;"
                              "padding:10px 12px 4px 12px;background:transparent;");
    lay->addWidget(m_titleLbl);

    m_detailsLbl = new QLabel();
    m_detailsLbl->setAlignment(Qt::AlignTop);
    m_detailsLbl->setWordWrap(true);
    m_detailsLbl->setTextFormat(Qt::RichText);
    m_detailsLbl->setStyleSheet("color:#C8D8E8;font-size:11px;"
                                "padding:0 12px 12px 12px;background:transparent;");
    lay->addWidget(m_detailsLbl);

    lay->addStretch();
}

void SidePanel::showStats(int total, int ok, int maint, int hs)
{
    m_statTotal->setText(QString("📍 Total : %1 conteneur(s)").arg(total));
    m_statOk->setText(QString("🟢 Opérationnel : %1").arg(ok));
    m_statMaint->setText(QString("🟠 Maintenance : %1").arg(maint));
    m_statHs->setText(QString("🔴 Hors service : %1").arg(hs));
    if (total > 0) {
        m_pbOk->setValue(ok*100/total);
        m_pbMaint->setValue(maint*100/total);
        m_pbHs->setValue(hs*100/total);
    }
}

void SidePanel::showRoute(double km, int stops)
{
    m_routeLbl->setText(
        QString("🛣️ Route optimisée\n"
                "   📏 Distance : <b>%1 km</b>\n"
                "   🏁 Arrêts : <b>%2</b>")
            .arg(km, 0, 'f', 1).arg(stops)
        );
}

void SidePanel::showConteneur(const Conteneur &c)
{
    QString etat  = c.getEtat();
    QString color = etat.toLower().contains("hors")        ? "#E74C3C"
                    : etat.toLower().contains("maintenance") ? "#E67E22"
                                                             : "#27AE60";
    m_titleLbl->setText(QString("🗑️ Conteneur #%1").arg(c.getId()));
    m_detailsLbl->setText(
        QString("<p style='margin:2px 0;'>📍 <b>%1</b></p>"
                "<p style='margin:2px 0;'>🌍 <span style='color:#A0C8E0;'>%2</span></p>"
                "<p style='margin:2px 0;'>📦 Capacité : <b>%3 L</b></p>"
                "<p style='margin:2px 0;'>🏢 Type : %4</p>"
                "<p style='margin:2px 0;'>⚙️ État : <b style='color:%5;'>%6</b></p>"
                "<p style='margin:2px 0;'>♻️ Recyclable : %7</p>"
                "<p style='margin:2px 0;'>📅 Collecte : %8</p>")
            .arg(c.getAdresseComplete())
            .arg(c.getLocalisationGPS())
            .arg(c.getCapacite(), 0, 'f', 0)
            .arg(c.getTypePropriete())
            .arg(color).arg(etat)
            .arg(c.getAccepteRecyclable())
            .arg(c.getDateDerniereCollecte())
        );
}

void SidePanel::clearSelection()
{
    m_titleLbl->setText("Sélectionnez un conteneur");
    m_detailsLbl->clear();
}

// ════════════════════════════════════════════════════════════════
// Map Dialog
// ════════════════════════════════════════════════════════════════
Map::Map(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("🗺️ Carte des Conteneurs — Tunisie");
    setMinimumSize(1100, 680);
    resize(1200, 740);
    setStyleSheet("QDialog { background-color: #1A2535; }");

    QVBoxLayout *mainLay = new QVBoxLayout(this);
    mainLay->setContentsMargins(0, 0, 0, 0);
    mainLay->setSpacing(0);

    // ── Toolbar ────────────────────────────────────────────────
    QWidget *toolbar = new QWidget();
    toolbar->setFixedHeight(54);
    toolbar->setStyleSheet(
        "QWidget{background:qlineargradient(x1:0,y1:0,x2:1,y2:0,"
        "stop:0 #0D1F35,stop:0.5 #1B3A57,stop:1 #0D1F35);"
        "border-bottom:1px solid #2C5F7C;}");
    QHBoxLayout *tLay = new QHBoxLayout(toolbar);
    tLay->setContentsMargins(16, 0, 16, 0);
    tLay->setSpacing(8);

    // Title
    QLabel *titre = new QLabel("🗺️  Carte des Conteneurs — Tunisie");
    titre->setStyleSheet("font-size:15px;font-weight:bold;color:white;"
                         "background:transparent;");
    tLay->addWidget(titre);
    tLay->addStretch();

    // Counter
    m_compteur = new QLabel("📍 Chargement...");
    m_compteur->setStyleSheet("color:#A0C8E0;font-size:12px;background:transparent;");
    tLay->addWidget(m_compteur);
    tLay->addSpacing(12);

    // Filter combo
    QLabel *filtLbl = new QLabel("Filtre:");
    filtLbl->setStyleSheet("color:#A0C8E0;font-size:12px;background:transparent;");
    tLay->addWidget(filtLbl);

    m_cmbFilter = new QComboBox();
    m_cmbFilter->setFixedHeight(30);
    m_cmbFilter->setMinimumWidth(145);
    m_cmbFilter->setStyleSheet(
        "QComboBox{background:#1B3A57;color:white;border:1px solid #2C5F7C;"
        "border-radius:5px;padding:3px 10px;font-size:12px;}"
        "QComboBox:hover{background:#2C5F7C;}"
        "QComboBox QAbstractItemView{background:#1B3A57;color:white;"
        "selection-background-color:#2C5F7C;}");
    m_cmbFilter->addItem("🌐 Tous",            "");
    m_cmbFilter->addItem("🟢 Opérationnel",    "operationnel");
    m_cmbFilter->addItem("🟠 Maintenance",     "maintenance");
    m_cmbFilter->addItem("🔴 Hors service",    "horsservice");
    tLay->addWidget(m_cmbFilter);
    tLay->addSpacing(8);

    // Zoom buttons
    const QString btnStyle =
        "QPushButton{background:#1B3A57;color:white;font-size:15px;"
        "font-weight:bold;border:1px solid #2C5F7C;border-radius:5px;"
        "min-width:30px;min-height:30px;}"
        "QPushButton:hover{background:#2C5F7C;}"
        "QPushButton:pressed{background:#4A8FAD;}";

    QPushButton *btnZoomIn  = new QPushButton("＋");
    QPushButton *btnZoomOut = new QPushButton("－");
    QPushButton *btnReset   = new QPushButton("⌂");
    btnZoomIn ->setToolTip("Zoom avant  (molette ↑)");
    btnZoomOut->setToolTip("Zoom arrière (molette ↓)");
    btnReset  ->setToolTip("Réinitialiser la vue");
    for (auto *b : {btnZoomIn, btnZoomOut, btnReset}) b->setStyleSheet(btnStyle);

    // Optimize toggle
    QPushButton *btnOptim = new QPushButton("🛣️ Optimiser");
    btnOptim->setCheckable(true);
    btnOptim->setFixedHeight(30);
    btnOptim->setStyleSheet(
        "QPushButton{background:#276646;color:white;font-size:12px;"
        "font-weight:bold;border:none;border-radius:5px;padding:0 12px;}"
        "QPushButton:hover{background:#34885A;}"
        "QPushButton:checked{background:#1a7a4a;border:1px solid #2ecc71;}");

    tLay->addWidget(btnZoomIn);
    tLay->addWidget(btnZoomOut);
    tLay->addWidget(btnReset);
    tLay->addSpacing(6);
    tLay->addWidget(btnOptim);
    tLay->addSpacing(8);

    QPushButton *btnFermer = new QPushButton("✕  Fermer");
    btnFermer->setFixedSize(88, 30);
    btnFermer->setStyleSheet(
        "QPushButton{background:#C0392B;color:white;font-size:12px;"
        "font-weight:600;border:none;border-radius:5px;}"
        "QPushButton:hover{background:#E74C3C;}");
    connect(btnFermer, &QPushButton::clicked, this, &QDialog::accept);
    tLay->addWidget(btnFermer);

    mainLay->addWidget(toolbar);

    // ── Content row (map + side panel) ────────────────────────
    QHBoxLayout *contentLay = new QHBoxLayout();
    contentLay->setSpacing(0);
    contentLay->setContentsMargins(0, 0, 0, 0);

    m_carte = new CarteWidget(this);
    contentLay->addWidget(m_carte, 1);

    m_side = new SidePanel(this);
    contentLay->addWidget(m_side);

    mainLay->addLayout(contentLay, 1);

    // ── Info bar (bottom) ──────────────────────────────────────
    m_infoBox = new QLabel("👆 Cliquez sur un marqueur pour voir les détails");
    m_infoBox->setFixedHeight(46);
    m_infoBox->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);
    m_infoBox->setWordWrap(false);
    m_infoBox->setTextFormat(Qt::RichText);
    m_infoBox->setStyleSheet(
        "QLabel{background:#0D1F35;color:#A0C8E0;font-size:12px;"
        "padding:4px 16px;border-top:1px solid #2C5F7C;}");
    mainLay->addWidget(m_infoBox);
    m_carte->setInfoLabel(m_infoBox);

    // ── Signal connections ─────────────────────────────────────
    connect(btnZoomIn,  &QPushButton::clicked, m_carte, &CarteWidget::zoomIn);
    connect(btnZoomOut, &QPushButton::clicked, m_carte, &CarteWidget::zoomOut);
    connect(btnReset,   &QPushButton::clicked, m_carte, &CarteWidget::resetView);

    connect(btnOptim, &QPushButton::toggled, this, [this](bool on) {
        m_carte->setOptimized(on);
    });

    connect(m_cmbFilter, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, [this](int idx) {
                m_carte->setFilterEtat(m_cmbFilter->itemData(idx).toString());
            });

    connect(m_carte, &CarteWidget::conteneurSelected,
            m_side, &SidePanel::showConteneur);

    connect(m_carte, &CarteWidget::routeCalculated,
            m_side, &SidePanel::showRoute);

    connect(m_carte, &CarteWidget::statsChanged,
            this, [this](int total, int ok, int maint, int hs) {
                m_compteur->setText(QString("📍 %1 conteneur(s)").arg(total));
                m_side->showStats(total, ok, maint, hs);
            });

    // ── Load data ──────────────────────────────────────────────
    QList<Conteneur> liste = Conteneur::getAll();
    m_carte->setConteneurs(liste);
}

void Map::setOptimized(bool opt)
{
    if (m_carte) m_carte->setOptimized(opt);
}
