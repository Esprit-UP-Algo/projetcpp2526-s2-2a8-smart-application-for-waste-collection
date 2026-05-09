#include "connection.h"

Connection::Connection() {}

bool Connection::createconnect() {
  bool test = false;
  QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
  db.setDatabaseName("source_prjet2A"); // Insert your ODBC data source name
  db.setUserName("maryem");              // Insert username
  db.setPassword("MARYOUMA01");          // Insert password

  if (db.open()) {
    test = true;
  } else {
    qDebug() << "Connection failed:" << db.lastError().text();
  }

  return test;
}
