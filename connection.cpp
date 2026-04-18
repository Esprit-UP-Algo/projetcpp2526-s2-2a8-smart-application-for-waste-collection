#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    bool test = false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2A"); // Insert your ODBC data source name
    db.setUserName("maryem");              // Insert username
    db.setPassword("MARYOUMA01");          // Insert password

    if (db.open())
        test = true;

    return test;
}
