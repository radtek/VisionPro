#include "MCommunicationTcpServer.h"

MCommunicationTcpServer::MCommunicationTcpServer()
    :MCommunicationBase(){
}

MCommunicationTcpServer::~MCommunicationTcpServer() {
    if (nullptr != tcp_server_ ) {
        delete tcp_server_;
        tcp_server_ = nullptr;
    }
}

MCommunicationTcpServer::MCommunicationTcpServer(MCommunicationTcpServer &&rhs)
    :tcp_server_(rhs.tcp_server_), tcp_socket_(rhs.tcp_socket_){
     rhs.tcp_server_ = nullptr;
     rhs.tcp_socket_ = nullptr;

}

MCommunicationTcpServer& MCommunicationTcpServer::operator=(MCommunicationTcpServer &&rhs){
    //std::swap(tcp_server_, rhs.tcp_server_);
    //std::swap(tcp_socket_, rhs.tcp_socket_);
    if(this == &rhs)
        return *this;
    delete tcp_server_;
    tcp_server_ = rhs.tcp_server_;
    rhs.tcp_server_ = nullptr;

    delete tcp_socket_;
    tcp_socket_ = rhs.tcp_socket_;
    tcp_socket_ = nullptr;
    return *this;
}

void MCommunicationTcpServer::init() {
    tcp_server_ = new QTcpServer(this);
    tcp_socket_ = nullptr;
}

void MCommunicationTcpServer::open(const QString &ip, const quint16 &port) {
    tcp_server_->listen(QHostAddress(ip), port);
    connect(tcp_server_, &QTcpServer::newConnection, [=](){
        tcp_socket_ = tcp_server_->nextPendingConnection();
        connect(tcp_socket_,&QTcpSocket::readyRead,[=](){
            emit sendMsg(tcp_socket_->readAll());
        });
    });
}

void MCommunicationTcpServer::open(const QString &serial_port_name,const QString &baud_rate,
          const QString &data_bits,const QString &parity_bits,const QString &stop_bits){

}

bool MCommunicationTcpServer::isOpen() {
	return tcp_server_->isListening();
}

void MCommunicationTcpServer::sendData(const QString &data) {
    if(nullptr == tcp_socket_ )
        return;
    tcp_socket_->write(data.toUtf8().data());
}


void MCommunicationTcpServer::close(){
    if(nullptr == tcp_socket_)
        return;
    tcp_socket_->disconnectFromHost();
    tcp_socket_->close();
}
