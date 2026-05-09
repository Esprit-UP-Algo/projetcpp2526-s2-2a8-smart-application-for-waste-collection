#include "arduinoconnection.h"
#include <QDebug>

ArduinoConnection::ArduinoConnection()
    : serial(new QSerialPort()),
      arduino_is_available(false),
      arduino_port_name("")
{}

ArduinoConnection::~ArduinoConnection()
{
    close_arduino();
    delete serial;
}

// ─── Connexion ──────────────────────────
int ArduinoConnection::connect_arduino()
{
    foreach (const QSerialPortInfo &port, QSerialPortInfo::availablePorts()) {
        if (port.hasVendorIdentifier() && port.hasProductIdentifier()) {
            if (port.vendorIdentifier()  == arduino_uno_vendor_id &&
                port.productIdentifier() == arduino_uno_product_id) {
                arduino_is_available = true;
                arduino_port_name = port.portName();
            }
        }
    }

    if (arduino_is_available) {
        serial->setPortName(arduino_port_name);
        if (serial->open(QSerialPort::ReadWrite)) {
            serial->setBaudRate(QSerialPort::Baud9600);
            serial->setDataBits(QSerialPort::Data8);
            serial->setParity(QSerialPort::NoParity);
            serial->setStopBits(QSerialPort::OneStop);
            serial->setFlowControl(QSerialPort::NoFlowControl);
            return 0;   // ✅ connecté
        }
        return 1;       // ❌ port trouvé mais pas ouvert
    }
    return -1;          // ❌ Arduino non trouvé
}

// ─── Fermeture ──────────────────────────
int ArduinoConnection::close_arduino()
{
    if (serial && serial->isOpen()) {
        serial->close();
        return 0;   // ✅ fermé
    }
    return 1;       // ❌ déjà fermé
}

// ─── Accesseurs ─────────────────────────
QSerialPort* ArduinoConnection::getSerial() const
{
    return serial;
}

QString ArduinoConnection::getPortName() const
{
    return arduino_port_name;
}

bool ArduinoConnection::isAvailable() const
{
    return arduino_is_available;
}
