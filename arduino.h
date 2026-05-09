#ifndef ARDUINO_H
#define ARDUINO_H

#include "arduinoconnection.h"
#include <QByteArray>

class Arduino
{
public:
    Arduino();

    int write_to_arduino(QByteArray data);
    QByteArray read_from_arduino();

    // Accès à la connexion
    ArduinoConnection* connection();

private:
    ArduinoConnection* m_connection;
    QByteArray         m_data;
};

#endif // ARDUINO_H
