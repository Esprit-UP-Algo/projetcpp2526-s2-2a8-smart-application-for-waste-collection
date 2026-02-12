#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_20_clicked();

    void on_pushButton_29_clicked();

    void on_pushButton_17_clicked();

    void on_pushButton_30_clicked();

    void on_pushButton_31_clicked();

    void on_cnx_clicked();

    void on_cnx1_clicked();

    void on_cnxemp_clicked();

    void on_dec_clicked();

    void on_mdp_clicked();

    void on_retour_2_clicked();

    void on_acceuil_2_clicked();

    void on_pushButton_40_clicked();

    void on_dec_2_clicked();

    void on_pushButton_28_clicked();

    void on_pushButton_client_ajouter_clicked();
private:
    void afficherWidgetAjoutEmploye();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
