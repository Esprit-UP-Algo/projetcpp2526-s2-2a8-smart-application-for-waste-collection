#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineF>
#include <QImage>
#include <QPixmap>
#include <QRect>
#include <QMap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QPropertyAnimation>
#include <QComboBox>
#include <QScrollArea>
#include <QFrame>
#include <QCheckBox>
#include <QProgressBar>
#include "conteneur.h"

// ─────────────────────────────────────────────────────────────
// OSM tile cache key
// ─────────────────────────────────────────────────────────────
struct TileKey {
    int z, x, y;
    bool operator==(const TileKey &o) const { return z==o.z && x==o.x && y==o.y; }
    bool operator<(const TileKey &o)  const {
        if (z != o.z) return z < o.z;
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
};
inline uint qHash(const TileKey &k, uint seed = 0) {
    return qHash(k.z * 1000000 + k.x * 1000 + k.y, seed);
}

// ─────────────────────────────────────────────────────────────
// CarteWidget  — OSM tile map with full interactivity
// ─────────────────────────────────────────────────────────────
class CarteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CarteWidget(QWidget *parent = nullptr);
    ~CarteWidget();

    void setConteneurs(const QList<Conteneur> &liste);
    void setInfoLabel(QLabel *label);
    void setFilterEtat(const QString &etat);   // "" = all

    // Zoom controls
    void zoomIn();
    void zoomOut();
    void resetView();
    void setOptimized(bool opt);

    // Route stats
    double getRouteTotalKm() const { return m_routeKm; }
    int    getRouteStops()   const { return m_routeStops; }

signals:
    void conteneurSelected(const Conteneur &c);
    void routeCalculated(double km, int stops);
    void statsChanged(int total, int ok, int maint, int hs);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private slots:
    void onTileDownloaded(QNetworkReply *reply);

private:
    // ── State ──────────────────────────────────────────────────
    bool             m_optimized   = false;
    QList<Conteneur> m_conteneurs;          // all loaded
    QList<Conteneur> m_visible;             // after filter
    QVector<int>     m_routeOrder;          // TSP indices into m_visible
    int              m_hover       = -1;
    int              m_selected    = -1;
    QString          m_filterEtat;
    double           m_routeKm    = 0.0;
    int              m_routeStops = 0;
    QLabel          *m_infoLabel  = nullptr;

    // ── OSM tiles ──────────────────────────────────────────────
    QNetworkAccessManager *m_nam  = nullptr;
    QMap<TileKey, QPixmap> m_tileCache;
    QSet<TileKey>          m_pending;
    static constexpr int   TILE_SIZE = 256;

    // ── Zoom / pan (OSM-style) ─────────────────────────────────
    int     m_zoom     = 7;               // OSM zoom level 1-18
    double  m_centerLat = 33.8869;        // Tunisia centre
    double  m_centerLng = 9.5375;
    bool    m_panning   = false;
    QPoint  m_panStart;
    double  m_panLat0, m_panLng0;

    static constexpr int ZOOM_MIN_OSM = 5;
    static constexpr int ZOOM_MAX_OSM = 17;

    // ── Bounding box Tunisie ───────────────────────────────────
    const double LAT_MIN = 29.8, LAT_MAX = 37.6;
    const double LNG_MIN =  7.4, LNG_MAX = 11.8;

    // ── Coordinate helpers ─────────────────────────────────────
    // GPS → OSM tile coordinates (fractional)
    static double lngToTileX(double lng, int z);
    static double latToTileY(double lat, int z);
    // GPS → widget pixel
    QPointF gpsToPixel(double lat, double lng) const;
    // Widget pixel → GPS
    void pixelToGps(QPointF px, double &lat, double &lng) const;

    // ── Tile helpers ───────────────────────────────────────────
    void requestTile(int z, int x, int y);
    void drawTiles(QPainter &p);

    // ── Drawing helpers ────────────────────────────────────────
    void drawMarker(QPainter &p, QPointF center, QColor color,
                    bool hovered, bool selected, int id, double capacite, const QString &etat);
    void drawTooltip(QPainter &p, QPointF pos, const Conteneur &c);
    void drawRoute(QPainter &p);
    void drawLegend(QPainter &p);
    void drawScale(QPainter &p);
    void drawZoomBadge(QPainter &p);

    // ── Route optimization (nearest-neighbor TSP) ─────────────
    void computeRoute();
    static double haversineKm(double lat1, double lng1, double lat2, double lng2);

    // ── Filter ─────────────────────────────────────────────────
    void applyFilter();
    void emitStats();

    // ── Pulse animation ────────────────────────────────────────
    QTimer  *m_pulseTimer = nullptr;
    double   m_pulsePhase = 0.0;
};

// ─────────────────────────────────────────────────────────────
// SidePanel  — info + stats card shown beside the map
// ─────────────────────────────────────────────────────────────
class SidePanel : public QWidget
{
    Q_OBJECT
public:
    explicit SidePanel(QWidget *parent = nullptr);
    void showConteneur(const Conteneur &c);
    void showRoute(double km, int stops);
    void showStats(int total, int ok, int maint, int hs);
    void clearSelection();

private:
    QLabel *m_titleLbl   = nullptr;
    QLabel *m_detailsLbl = nullptr;
    QLabel *m_routeLbl   = nullptr;
    QFrame *m_statFrame  = nullptr;
    QLabel *m_statOk     = nullptr;
    QLabel *m_statMaint  = nullptr;
    QLabel *m_statHs     = nullptr;
    QLabel *m_statTotal  = nullptr;
    QProgressBar *m_pbOk    = nullptr;
    QProgressBar *m_pbMaint = nullptr;
    QProgressBar *m_pbHs    = nullptr;
};

// ─────────────────────────────────────────────────────────────
// Map Dialog
// ─────────────────────────────────────────────────────────────
class Map : public QDialog
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);
    void setOptimized(bool opt);

private:
    CarteWidget *m_carte    = nullptr;
    SidePanel   *m_side     = nullptr;
    QLabel      *m_infoBox  = nullptr;
    QComboBox   *m_cmbFilter = nullptr;
    QLabel      *m_compteur  = nullptr;

    void buildToolbar(QHBoxLayout *lay);
};

#endif // MAP_H
