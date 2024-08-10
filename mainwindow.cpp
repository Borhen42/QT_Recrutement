#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "formateur.h"
#include "formation.h"
#include <QMessageBox>
#include <QSqlQuery>


Formation formation;
Formateur formateur;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView_formations->setModel(formation.afficher());
    ui->tableView_formateur->setModel(formateur.afficher());
    populateFormateurComboBox();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ajouter_f_clicked()
{
    // Récupérer les valeurs des champs de l'interface utilisateur
       QString titre = ui->lineEdit_titre->text();
       QString description = ui->lineEdit_description->text();
       int duree = ui->spinBox_duree->value();
       QDate date_de_debut = ui->dateEdit_date_de_debut->date();
       QDate date_de_fin = ui->dateEdit_date_de_fin->date();

       // Récupérer l'id du formateur sélectionné dans le QComboBox
       int formateur_id = ui->comboBox_formateur->currentData().toInt();

       // Vérifier si tous les champs sont remplis
       if (titre.isEmpty() || description.isEmpty() || duree == 0 || formateur_id == 0) {
           QMessageBox::warning(this, "Champ(s) manquant(s)", "Veuillez remplir tous les champs.");
           return;
       }

       // Créer une instance de la classe Formation avec les données récupérées
       Formation formation(titre, description, duree, date_de_debut, date_de_fin, formateur_id);

       // Appeler la méthode ajouter() pour insérer les données dans la base de données
       bool success = formation.ajouter();

       // Afficher un message en fonction du résultat de l'opération
       if (success) {
           QMessageBox::information(this, "Succès", "La formation a été ajoutée avec succès.");
           // Optionnel : Effacer les champs après ajout
           ui->lineEdit_titre->clear();
           ui->lineEdit_description->clear();
           ui->spinBox_duree->setValue(0);
           ui->dateEdit_date_de_debut->setDate(QDate::currentDate());
           ui->dateEdit_date_de_fin->setDate(QDate::currentDate());
           ui->comboBox_formateur->setCurrentIndex(0);
           // Optionnel : Mettre à jour l'affichage des formations
           ui->tableView_formations->setModel(formation.afficher());
       } else {
           QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout de la formation.");
       }
}

void MainWindow::on_supp_f_clicked()
{
    // at least one selected index
        QModelIndexList selectedIndexes = ui->tableView_formations->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            // get id from selected row
            int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

            // Call delete function
            bool supprime = formation.supprimer(id);

            if (supprime) {
                ui->tableView_formations->setModel(formation.afficher());
                QMessageBox::information(this, "Suppression réussie", "Formation supprimée avec succès.");
            } else {
                QMessageBox::warning(this, "Échec de la suppression", "Échec de la suppression de la formation.");
            }
        } else {
            QMessageBox::warning(this, "Aucune formation sélectionnée", "Veuillez sélectionner une formation à supprimer.");
        }
}

void MainWindow::on_modfi_f_clicked()
{
    int id = ui->idFormation->text().toInt();
       QString titre = ui->lineEdit_titre->text();
       QString description = ui->lineEdit_description->text();
       int duree = ui->spinBox_duree->value();
       QDate date_de_debut = ui->dateEdit_date_de_debut->date();
       QDate date_de_fin = ui->dateEdit_date_de_fin->date();

       // Récupérer l'id du formateur sélectionné dans le QComboBox
       int formateur_id = ui->comboBox_formateur->currentData().toInt();

       // Input validation
       if (titre.isEmpty() || description.isEmpty() || date_de_debut.isNull() || date_de_fin.isNull() || formateur_id == 0) {
           QMessageBox::critical(nullptr, QObject::tr("Validation Error"),
                                 QObject::tr("Veuillez remplir tous les champs."),
                                 QMessageBox::Ok);
           return;
       }

       // Créer une instance de la classe Formation avec les données récupérées
       Formation formation(id, titre, description, duree, date_de_debut, date_de_fin, formateur_id);

       // Appeler la méthode modifier() pour mettre à jour les données dans la base de données
       bool test = formation.modifier(id);

       if (test) {
           // Mettre à jour l'affichage des formations
           ui->tableView_formations->setModel(formation.afficher());

           // Effacer les champs après modification
           ui->idFormation->clear();
           ui->lineEdit_titre->clear();
           ui->lineEdit_description->clear();
           ui->spinBox_duree->setValue(0);
           ui->dateEdit_date_de_debut->setDate(QDate::currentDate());
           ui->dateEdit_date_de_fin->setDate(QDate::currentDate());
           ui->comboBox_formateur->setCurrentIndex(0);

           QMessageBox::information(nullptr, QObject::tr("Modifier une formation"),
                                    QObject::tr("Formation modifiée.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
       } else {
           QMessageBox::information(nullptr, QObject::tr("ERREUR"),
                                    QObject::tr("ERREUR.\n"
                                                "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void MainWindow::on_tableView_formations_doubleClicked(const QModelIndex &index)
{
    int row = index.row();

        // Retrieve the data from the selected row
        int id = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 0)).toInt();
        QString titre = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 1)).toString();
        QString description = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 2)).toString();
        int duree = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 3)).toInt();
        QDate dateDebut = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 4)).toDate();
        QDate dateFin = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 5)).toDate();
        int formateur_id = ui->tableView_formations->model()->data(ui->tableView_formations->model()->index(row, 6)).toInt(); // Assuming formateur_id is the 6th column

        // Set the data to the respective UI elements
        ui->idFormation->setText(QString::number(id));
        ui->lineEdit_titre->setText(titre);
        ui->lineEdit_description->setText(description);
        ui->spinBox_duree->setValue(duree);
        ui->dateEdit_date_de_debut->setDate(dateDebut);
        ui->dateEdit_date_de_fin->setDate(dateFin);

        // Set the formateur name in the QComboBox
        int indexComboBox = ui->comboBox_formateur->findData(formateur_id);
        if (indexComboBox != -1) {
            ui->comboBox_formateur->setCurrentIndex(indexComboBox);
        }

}

void MainWindow::on_ajouter_fr_clicked()
{
    // Récupérer les valeurs des champs de l'interface utilisateur
        QString nom = ui->lineEdit_nom->text();
        QString email = ui->lineEdit_mail->text();
        QString telephone = ui->lineEdit_tel->text();
        QString specialite = ui->lineEdit_specalite->text();
        int experience = ui->spinBox_exp->value();

        // Vérifier si tous les champs sont remplis
        if (nom.isEmpty() || email.isEmpty() || telephone.isEmpty() || specialite.isEmpty() || experience == 0) {
            QMessageBox::warning(this, "Champ(s) manquant(s)", "Veuillez remplir tous les champs.");
            return;
        }

        // Créer une instance de la classe Formateur avec les données récupérées
        Formateur formateur(nom, email, telephone, specialite, experience);

        // Appeler la méthode ajouter() pour insérer les données dans la base de données
        bool success = formateur.ajouter();

        // Afficher un message en fonction du résultat de l'opération
        if (success) {
            QMessageBox::information(this, "Succès", "Le formateur a été ajouté avec succès.");
            // Optionnel : Effacer les champs après ajout
            ui->lineEdit_nom->clear();
            ui->lineEdit_mail->clear();
            ui->lineEdit_tel->clear();
            ui->lineEdit_specalite->clear();
            ui->spinBox_exp->setValue(0);
            // Optionnel : Mettre à jour l'affichage des formateurs
            ui->tableView_formateur->setModel(formateur.afficher());
        } else {
            QMessageBox::critical(this, "Erreur", "Une erreur est survenue lors de l'ajout du formateur.");
        }

}

void MainWindow::on_modfi_fr_clicked()
{
    int id = ui->idFormateur->text().toInt();
        QString nom = ui->lineEdit_nom->text();
        QString email = ui->lineEdit_mail->text();
        QString telephone = ui->lineEdit_tel->text();
        QString specialite = ui->lineEdit_specalite->text();
        int experience = ui->spinBox_exp->value();

        // Validation des champs
        if (nom.isEmpty() || email.isEmpty() || telephone.isEmpty() || specialite.isEmpty()) {
            QMessageBox::critical(nullptr, QObject::tr("Validation Error"),
                                  QObject::tr("Veuillez remplir tous les champs."),
                                  QMessageBox::Ok);
            return;
        }

        Formateur formateur(id, nom, email, telephone, specialite, experience);

        bool success = formateur.modifier(id);

        if (success) {
            ui->tableView_formateur->setModel(formateur.afficher());

            ui->idFormateur->clear();
            ui->lineEdit_nom->clear();
            ui->lineEdit_mail->clear();
            ui->lineEdit_tel->clear();
            ui->lineEdit_specalite->clear();
            ui->spinBox_exp->setValue(0);

            QMessageBox::information(nullptr, QObject::tr("Modifier un formateur"),
                                     QObject::tr("Formateur modifié avec succès.\n"
                                                 "Cliquez sur Annuler pour quitter."),
                                     QMessageBox::Cancel);
        } else {
            QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                                  QObject::tr("Une erreur est survenue.\n"
                                              "Cliquez sur Annuler pour quitter."),
                                  QMessageBox::Cancel);
        }
}

void MainWindow::on_supp_fr_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView_formateur->selectionModel()->selectedIndexes();

        if (!selectedIndexes.isEmpty()) {
            // get id from selected row
            int id = selectedIndexes.at(0).sibling(selectedIndexes.at(0).row(), 0).data().toInt();

            // Call delete function
            bool supprime = formateur.supprimer(id);

            if (supprime) {
                ui->tableView_formateur->setModel(formateur.afficher());
                QMessageBox::information(this, "Suppression réussie", "Formateur supprimé avec succès.");
            } else {
                QMessageBox::warning(this, "Échec de la suppression", "Échec de la suppression du formateur.");
            }
        } else {
            QMessageBox::warning(this, "Aucun formateur sélectionné", "Veuillez sélectionner un formateur à supprimer.");
        }
}

void MainWindow::on_tableView_formateur_doubleClicked(const QModelIndex &index)
{
    int row = index.row();
       int id = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 0)).toInt();
       QString nom = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 1)).toString();
       QString email = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 2)).toString();
       QString telephone = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 3)).toString();
       QString specialite = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 4)).toString();
       int experience = ui->tableView_formateur->model()->data(ui->tableView_formateur->model()->index(row, 5)).toInt();

       ui->idFormateur->setText(QString::number(id));
       ui->lineEdit_nom->setText(nom);
       ui->lineEdit_mail->setText(email);
       ui->lineEdit_tel->setText(telephone);
       ui->lineEdit_specalite->setText(specialite);
       ui->spinBox_exp->setValue(experience);
}

void MainWindow::populateFormateurComboBox() {
    QSqlQuery query("SELECT id, nom FROM formateur");
    while (query.next()) {
        int id = query.value(0).toInt();
        QString name = query.value(1).toString();
        ui->comboBox_formateur->addItem(name, id);
    }
}

void MainWindow::on_lineEdit_textChanged(QString text)
{
    QSqlQueryModel* resultModel = Formateur::rechercherParNom(text);

    if (resultModel) {
        ui->tableView_formateur->setModel(resultModel);
    } else {
        // Gérer l'erreur, par exemple afficher un message d'erreur
        QMessageBox::critical(this, "Erreur de recherche", "Une erreur s'est produite lors de la recherche.");
    }
}

void MainWindow::on_tri_fr_clicked()
{
    // Call the sorting method in your Fournisseur class
        QSqlQueryModel *sortedModel = formateur.tri("nom", Qt::AscendingOrder);

        // Set the sorted model to the table view
        ui->tableView_formateur->setModel(sortedModel);
}
