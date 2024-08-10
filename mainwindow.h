#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formation.h"
#include "formateur.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ajouter_f_clicked();

    void on_supp_f_clicked();

    void on_modfi_f_clicked();

    void on_tableView_formations_doubleClicked(const QModelIndex &index);

    void on_ajouter_fr_clicked();

    void on_modfi_fr_clicked();

    void on_supp_fr_clicked();

    void on_tableView_formateur_doubleClicked(const QModelIndex &index);
    void populateFormateurComboBox();

    void on_lineEdit_textChanged( QString text);

    void on_tri_fr_clicked();

private:
    Ui::MainWindow *ui;
   Formation formation;
   Formateur formateur;
};
#endif // MAINWINDOW_H
