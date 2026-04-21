#ifndef MAP_H
#define MAP_H

#include <QDialog>
#include <QWidget>
#include <QPainter>
#include <QMouseEvent>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineF>
#include "conteneur.h"

// =======================
// CarteWidget
// =======================
class CarteWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CarteWidget(QWidget *parent = nullptr);
    void setConteneurs(const QList<Conteneur> &liste);
    void setInfoLabel(QLabel *label);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QList<Conteneur> m_conteneurs;
    int              m_hover    = -1;
    int              m_selected = -1;
    QLabel          *m_infoLabel = nullptr;

    // Bounding box Tunisie — précise
    const double LAT_MIN = 29.8;
    const double LAT_MAX = 37.6;
    const double LNG_MIN =  7.4;
    const double LNG_MAX = 11.8;

    QPointF gpsToPixel(double lat, double lng) const;
    void drawTrashIcon(QPainter &p, QPointF center, QColor color,
                       bool hovered, bool selected, int id);
};

// =======================
// Map Dialog
// =======================
class Map : public QDialog
{
    Q_OBJECT
public:
    explicit Map(QWidget *parent = nullptr);

private:
    CarteWidget *m_carte   = nullptr;
    QLabel      *m_infoBox = nullptr;
};

#endif // MAP_H
