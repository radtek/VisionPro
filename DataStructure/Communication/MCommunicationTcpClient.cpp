#include "MCommunicationTcpClient.h"

MCommunicationTcpClient::MCommunicationTcpClient():
    MCommunicationBase(){
}

MCommunicationTcpClient::~MCommunicationTcpClient(){
    if(nullptr != tcp_socket_){
        delete tcp_socket_;
        tcp_socket_ = nullptr;
    }
}

MCommunicationTcpClient::MCommunicationTcpClient(MCommunicationTcpClient &&rhs)
    :tcp_socket_{rhs.tcp_socket_}{
    rhs.tcp_socket_ = nullptr;
}

MCommunicationTcpClient& MCommunicationTcpClient::operator=(MCommunicationTcpClient &&rhs){
    if(this == &rhs)
        return *this;
    //std::swap(tcp_socket_, rhs.tcp_socket_);
    delete tcp_socket_;
    tcp_socket_ = rhs.tcp_socket_;
    rhs.tcp_socket_ = nullptr;
    return *this;
}

void MCommunicationTcpClient::init(){
    tcp_socket_ = new QTcpSocket(this);   
}

void MCommunicationTcpClient::open(const QString &ip, const quint16 &port){
    tcp_socket_->connectToHost(ip, port);
    while(true){
        if (tcp_socket_->waitForConnected(500)){
            break;
        }else{
            tcp_socket_->connectToHost(ip, port);
        }
    }
    connect(tcp_socket_,&QTcpSocket::readyRead,this,[=](){
        emit sendMsg(tcp_socket_->readAll());
    });
}

void MCommunicationTcpClient::open(const QString &serial_port_name,const QString &baud_rate,
          const QString &data_bits,const QString &parity_bits,const QString &stop_bits){

}

bool MCommunicationTcpClient::isOpen(){
    return tcp_socket_->isOpen();
}

void MCommunicationTcpClient::sendData(const QString &data){
    if(nullptr == tcp_socket_ )
        return;
    tcp_socket_->write(data.toUtf8().data());
}


void MCommunicationTcpClient::close(){
    if(nullptr == tcp_socket_ )
        return;
    tcp_socket_->disconnectFromHost();
    tcp_socket_->close();
}

