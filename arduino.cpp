#include "arduino.h"
#include <QDebug>

Arduino::Arduino()
    : m_connection(new ArduinoConnection())
{}

// ─── Envoi vers Arduino (OUTPUT) ────────
int Arduino::write_to_arduino(QByteArray data)
{
    QSerialPort* serial = m_connection->getSerial();
    if (serial && serial->isWritable()) {
        serial->write(data);
        return 0;   // ✅ envoyé
    }
    qDebug() << "Erreur : impossible d'écrire sur le port !";
    return -1;      // ❌ erreur
}

// ─── Lecture depuis Arduino (INPUT) ─────
QByteArray Arduino::read_from_arduino()
{
    QSerialPort* serial = m_connection->getSerial();
    if (serial && serial->isReadable()) {
        m_data = serial->readAll();
        return m_data;
    }
    return "";
}

// ─── Accès à la connexion ────────────────
ArduinoConnection* Arduino::connection()
{
    return m_connection;
}
