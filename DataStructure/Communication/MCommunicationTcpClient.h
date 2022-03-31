#ifndef MCOMMUNICATIONTCPCLIENT_H
#define MCOMMUNICATIONTCPCLIENT_H

#include "MCommunicationBase.h"
#include <QTcpSocket>

class MCommunicationTcpClient : public MCommunicationBase{
public:
    explicit MCommunicationTcpClient();
    ~MCommunicationTcpClient() override;

    MCommunicationTcpClient(const MCommunicationTcpClient &rhs)=delete;
    MCommunicationTcpClient& operator=(const MCommunicationTcpClient &rhs)=delete;   
    MCommunicationTcpClient(MCommunicationTcpClient &&rhs);
    MCommunicationTcpClient& operator=(MCommunicationTcpClient &&rhs);

    void init() override;
    void open(const QString &ip, const quint16 &port) override;
    void open(const QString &serial_port_name,const QString &baud_rate, const QString &data_bits,
              const QString &parity_bits,const QString &stop_bits) override ;
    bool isOpen() override;
    void sendData(const QString &data) override;
    void close() override;   
private:
    QTcpSocket *tcp_socket_;
};

#endif // MCOMMUNICATIONTCPCLIENT_H
