#ifndef ARDUINOCONNECTION_H
#define ARDUINOCONNECTION_H

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QString>

class ArduinoConnection
{
public:
    ArduinoConnection();
    ~ArduinoConnection();

    int connect_arduino();
    int close_arduino();

    QSerialPort* getSerial() const;
    QString getPortName() const;
    bool isAvailable() const;

private:
    QSerialPort*  serial;
    QString       arduino_port_name;
    bool          arduino_is_available;

    static const quint16 arduino_uno_vendor_id  = 9025;
    static const quint16 arduino_uno_product_id = 67;
};

#endif // ARDUINOCONNECTION_H
