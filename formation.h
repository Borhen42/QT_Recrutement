#ifndef FORMATION_H
#define FORMATION_H

#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class Formation {
public:
    Formation();
    Formation(int id, QString titre, QString description, int duree, QDate date_de_debut, QDate date_de_fin, int formateur_id);
    Formation(QString titre, QString description, int duree, QDate date_de_debut, QDate date_de_fin, int formateur_id);

    // Getter methods
    int getID();
    QString getTitre();
    QString getDescription();
    int getDuree();
    QDate getDateDeDebut();
    QDate getDateDeFin();
    int getFormateurID();  // New getter for formateur_id

    // Setter methods
    void setID(int id);
    void setTitre(QString titre);
    void setDescription(QString description);
    void setDuree(int duree);
    void setDateDeDebut(QDate date_de_debut);
    void setDateDeFin(QDate date_de_fin);
    void setFormateurID(int formateur_id);  // New setter for formateur_id

    // Database operations
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    bool modifier(int id);

private:
    int id;
    QString titre;
    QString description;
    int duree;
    QDate date_de_debut;
    QDate date_de_fin;
    int formateur_id;  // New attribute
};

#endif // FORMATION_H
