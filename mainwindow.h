#ifndef COLLECTIONWINDOW_H
#define COLLECTIONWINDOW_H

#include <QMainWindow>
#include "ui_collectionwindow.h"

namespace Ui {
class CollectionWindow;
}

class CollectionWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CollectionWindow(QWidget *parent = nullptr);
    ~CollectionWindow();

private slots:
    void on_btnNouvelle_clicked();
    void on_btnOptimiser_clicked();
    void on_btnExporter_clicked();
    void on_searchInput_textChanged(const QString &text);

private:
    Ui::CollectionWindow *ui;
    void loadCollections();
};

#endif
