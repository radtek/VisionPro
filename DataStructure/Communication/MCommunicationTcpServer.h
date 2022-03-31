#ifndef MCOMMUNICATIONTCPSERVER_H
#define MCOMMUNICATIONTCPSERVER_H

#include "MCommunicationBase.h"
#include <QTcpSocket>
#include <QTcpServer>

class MCommunicationTcpServer : public MCommunicationBase{
public:
    explicit MCommunicationTcpServer();
    ~MCommunicationTcpServer() override;

    MCommunicationTcpServer(const MCommunicationTcpServer &rhs)=delete;
    MCommunicationTcpServer& operator=(const MCommunicationTcpServer &rhs)=delete;
    MCommunicationTcpServer(MCommunicationTcpServer &&rhs);
    MCommunicationTcpServer& operator=(MCommunicationTcpServer &&rhs);

    void init() override;
    void open(const QString &ip, const quint16 &port) override;
    void open(const QString &serial_port_name,const QString &baud_rate,
              const QString &data_bits,const QString &parity_bits,const QString &stop_bits) override;
    bool isOpen() override;
    void sendData(const QString &data) override;
    void close() override;
private:
    QTcpServer *tcp_server_;
    QTcpSocket *tcp_socket_;
};


#endif // MCOMMUNICATIONTCPSERVER_H
