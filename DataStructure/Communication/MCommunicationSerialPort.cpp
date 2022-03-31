#include "MCommunicationSerialPort.h"

MCommunicationSerialPort::MCommunicationSerialPort()
    :MCommunicationBase(){
}

MCommunicationSerialPort::~MCommunicationSerialPort()
{
    if(nullptr != serial_port_){
        delete serial_port_;
        serial_port_ = nullptr;
    }
}

MCommunicationSerialPort::MCommunicationSerialPort(MCommunicationSerialPort &&rhs)
    :serial_port_{rhs.serial_port_}{
    rhs.serial_port_ = nullptr;
}

MCommunicationSerialPort& MCommunicationSerialPort::operator=(MCommunicationSerialPort &&rhs){
    if(this == &rhs)
        return *this;
    delete serial_port_;
    serial_port_ = rhs.serial_port_;
    rhs.serial_port_ = nullptr;
    return *this;
}

void MCommunicationSerialPort::open(const QString &serial_port_name,const QString &baud_rate,
                  const QString &data_bits,const QString &parity_bits,const QString &stop_bits){

    serial_port_->setPortName(serial_port_name);

    serial_port_->open(QIODevice::ReadWrite);

    if (baud_rate == "1200") {
		serial_port_->setBaudRate(QSerialPort::Baud1200);
	}
    else if (baud_rate == "2400") {
		serial_port_->setBaudRate(QSerialPort::Baud2400);
	}
    else if (baud_rate == "4800") {
		serial_port_->setBaudRate(QSerialPort::Baud4800);
	}
    else if (baud_rate == "9600") {
		serial_port_->setBaudRate(QSerialPort::Baud9600);
	}
    else if (baud_rate == "19200") {
		serial_port_->setBaudRate(QSerialPort::Baud19200);
	}
    else if (baud_rate == "38400") {
		serial_port_->setBaudRate(QSerialPort::Baud38400);
	}
    else if (baud_rate == "57600") {
		serial_port_->setBaudRate(QSerialPort::Baud57600);
	}
    else if (baud_rate == "115200") {
		serial_port_->setBaudRate(QSerialPort::Baud115200);
	}
	else {
		serial_port_->setBaudRate(QSerialPort::UnknownBaud);
	}

    if (data_bits == "5") {
		serial_port_->setDataBits(QSerialPort::Data5);
	}
    else if (data_bits == "6") {
		serial_port_->setDataBits(QSerialPort::Data6);
	}
    else if (data_bits == "7") {
		serial_port_->setDataBits(QSerialPort::Data7);
	}
    else if (data_bits == "8") {
		serial_port_->setDataBits(QSerialPort::Data8);
	}
	else {
		serial_port_->setDataBits(QSerialPort::UnknownDataBits);
	}
	
    if (parity_bits == "NoParity") {
		serial_port_->setParity(QSerialPort::NoParity);
	}
    else if (parity_bits == "Even") {
		serial_port_->setParity(QSerialPort::EvenParity);
	}
	else if (parity_bits == "Odd") {
		serial_port_->setParity(QSerialPort::OddParity);	
	}
	else if (parity_bits == "Space") {
		serial_port_->setParity(QSerialPort::SpaceParity);
	}
	else if (parity_bits == "Mark") {
		serial_port_->setParity(QSerialPort::MarkParity);
	}
	else {
		serial_port_->setParity(QSerialPort::UnknownParity);
	}

    if (stop_bits == "1") {
		serial_port_->setStopBits(QSerialPort::OneStop);
	}
    else if (stop_bits == "1.5") {
		serial_port_->setStopBits(QSerialPort::OneAndHalfStop);
	}
    else if (stop_bits == "2") {
		serial_port_->setStopBits(QSerialPort::TwoStop);
	}
	else {
		serial_port_->setStopBits(QSerialPort::UnknownStopBits);
	}

    connect(serial_port_,&QSerialPort::readyRead,this,[=](){
        emit sendMsg(serial_port_->readAll());
    });
}

void MCommunicationSerialPort::init() {
    serial_port_ = new QSerialPort;
}

void MCommunicationSerialPort::open(const QString &ip, const quint16 &port){

}

bool MCommunicationSerialPort::isOpen(){
    return serial_port_->isOpen();
}

void MCommunicationSerialPort::sendData(const QString &data) {
    serial_port_->write(data.toLatin1());
}



void MCommunicationSerialPort::close(){
    serial_port_->close();
}
