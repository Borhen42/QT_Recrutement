#include "formation.h"
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>

// Constructors
Formation::Formation() {}

Formation::Formation(int id, QString titre, QString description, int duree, QDate date_de_debut, QDate date_de_fin, int formateur_id)
    : id(id), titre(titre), description(description), duree(duree), date_de_debut(date_de_debut), date_de_fin(date_de_fin), formateur_id(formateur_id) {}

Formation::Formation(QString titre, QString description, int duree, QDate date_de_debut, QDate date_de_fin, int formateur_id)
    : titre(titre), description(description), duree(duree), date_de_debut(date_de_debut), date_de_fin(date_de_fin), formateur_id(formateur_id) {}

// Getters
int Formation::getID() {
    return id;
}

QString Formation::getTitre() {
    return titre;
}

QString Formation::getDescription() {
    return description;
}

int Formation::getDuree() {
    return duree;
}

QDate Formation::getDateDeDebut() {
    return date_de_debut;
}

QDate Formation::getDateDeFin() {
    return date_de_fin;
}

int Formation::getFormateurID() {
    return formateur_id;
}

// Setters
void Formation::setID(int id) {
    this->id = id;
}

void Formation::setTitre(QString titre) {
    this->titre = titre;
}

void Formation::setDescription(QString description) {
    this->description = description;
}

void Formation::setDuree(int duree) {
    this->duree = duree;
}

void Formation::setDateDeDebut(QDate date_de_debut) {
    this->date_de_debut = date_de_debut;
}

void Formation::setDateDeFin(QDate date_de_fin) {
    this->date_de_fin = date_de_fin;
}

void Formation::setFormateurID(int formateur_id) {
    this->formateur_id = formateur_id;
}

// Database methods
bool Formation::ajouter() {
    QSqlQuery query;

    query.prepare("INSERT INTO formation(titre, description, duree, date_de_debut, date_de_fin, formateur_id) "
                  "VALUES (:titre, :description, :duree, :date_de_debut, :date_de_fin, :formateur_id)");

    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":duree", duree);
    query.bindValue(":date_de_debut", date_de_debut);
    query.bindValue(":date_de_fin", date_de_fin);
    query.bindValue(":formateur_id", formateur_id);

    return query.exec();
}

QSqlQueryModel* Formation::afficher() {
    QSqlQueryModel *model = new QSqlQueryModel();
   model->setQuery("SELECT * FROM formation ORDER BY id");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Titre"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Description"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de début"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date de fin"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Formateur"));

    return model;
}

bool Formation::supprimer(int id) {
    QSqlQuery query;
    query.prepare("DELETE FROM formation WHERE id = :id");
    query.bindValue(":id", id);
    return query.exec();
}

bool Formation::modifier(int id) {
    QSqlQuery query;

    query.prepare("UPDATE formation SET titre = :titre, description = :description, duree = :duree, "
                  "date_de_debut = :date_de_debut, date_de_fin = :date_de_fin, formateur_id = :formateur_id WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":titre", titre);
    query.bindValue(":description", description);
    query.bindValue(":duree", duree);
    query.bindValue(":date_de_debut", date_de_debut);
    query.bindValue(":date_de_fin", date_de_fin);
    query.bindValue(":formateur_id", formateur_id);

    return query.exec();
}
