#ifndef MCOMMUNICATIONSERIALPORT_H
#define MCOMMUNICATIONSERIALPORT_H

#include "MCommunicationBase.h"
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo> 

class MCommunicationSerialPort : public MCommunicationBase{
public:
    explicit MCommunicationSerialPort();
    ~MCommunicationSerialPort() override;

    MCommunicationSerialPort(const MCommunicationSerialPort &rhs) = delete;
    MCommunicationSerialPort& operator=(const MCommunicationSerialPort &rhs)=delete;
    MCommunicationSerialPort(MCommunicationSerialPort &&rhs);
    MCommunicationSerialPort& operator=(MCommunicationSerialPort &&rhs);


    void init() override;
    void open(const QString &ip, const quint16 &port) override;
    void open(const QString &serial_port_name,const QString &baud_rate,
              const QString &data_bits,const QString &parity_bits,const QString &stop_bits) override;
    bool isOpen() override;
    void sendData(const QString &data) override;
    void close() override;

private:
    QSerialPort *serial_port_;
};

#endif // MCOMMUNICATIONSERIALPORT_H
