#include "connection.h"

Connection::Connection()
{
}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Projet2A"); // Nom de la source de données ODBC
    db.setUserName("cuirea"); // Nom d'utilisateur Oracle
    db.setPassword("0000"); // Mot de passe - À REMPLIR!
    
    if (db.open())
        test = true;
    
    return test;
}
