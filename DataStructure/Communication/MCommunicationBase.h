#ifndef MCOMMUNICATION_H
#define MCOMMUNICATION_H

#include <QObject>
#include <QString>

class MCommunicationBase : public QObject{
    Q_OBJECT
public:
    virtual ~MCommunicationBase();
    MCommunicationBase(MCommunicationBase &&rhs);
    MCommunicationBase& operator=(MCommunicationBase &&rhs);

    MCommunicationBase(const MCommunicationBase &rhs) = delete;
    MCommunicationBase& operator=(const MCommunicationBase &rhs) = delete;


    virtual void init() = 0;
    virtual void open(const QString &ip, const quint16 &port) = 0;
    virtual void open(const QString &serial_port_name,const QString &baud_rate,
                      const QString &data_bits,const QString &parity_bits,const QString &stop_bits) = 0;
    virtual bool isOpen() = 0;
    virtual void sendData(const QString& data) = 0;  
    virtual void close() = 0;
signals:
    void sendMsg(const QString &data);
protected:
    explicit MCommunicationBase();
};

#endif // MCOMMUNICATION_H
