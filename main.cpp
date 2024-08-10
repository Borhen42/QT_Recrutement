#include "mainwindow.h"
#include "connection.h"
#include <QMessageBox>
#include <QApplication>
#include <QFile>
#include <QRadioButton>





int main(int argc, char *argv[]) {
    QApplication a(argc, argv);



    // Create database connection
    Connection c;
    bool test = c.createconnect();


    // Create main window
    MainWindow w;


    // Test database connection and display result
    if (test) {


        w.show();

        QMessageBox::information(nullptr, QObject::tr("Database Open"),
                                 QObject::tr("Connection successful.\nClick Cancel to exit."),
                                 QMessageBox::Cancel);
    } else {
        QMessageBox::critical(nullptr, QObject::tr("Database Error"),
                              QObject::tr("Failed to connect to database.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    // Start event loop
    return a.exec();
}
