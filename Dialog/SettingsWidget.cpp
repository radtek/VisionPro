#include "SettingsWidget.h"
#include "ui_settingswidget.h"

SettingsWidget::SettingsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsWidget)
{
    ui->setupUi(this);
    init();
}

SettingsWidget::~SettingsWidget()
{
    delete ui;
}

void SettingsWidget::init(){
	std::string camera_type = MSysInfo::Instance()->basic_settings_->get_camera_type();
    ui->comboCameraType->addItem(tr("simulator"));
    ui->comboCameraType->addItem(tr("hik vision"));
	ui->comboCameraType->setCurrentText(QString::fromStdString(camera_type));

	int camera_count = MSysInfo::Instance()->basic_settings_->get_camera_count();
    for(int i = 1 ; i < 5; i++)
        ui->comboCameraCount->addItem(QString::number(i));
	ui->comboCameraCount->setCurrentText(QString::number(camera_count));

	std::string communication_type = MSysInfo::Instance()->basic_settings_->get_communication_type();
	ui->comboCommunicationType->addItem(tr("tcp server"));
	ui->comboCommunicationType->addItem(tr("tcp client"));
	ui->comboCommunicationType->addItem(tr("serial port"));
	ui->comboCommunicationType->setCurrentText(QString::fromStdString(communication_type));

	int communicatin_count = MSysInfo::Instance()->basic_settings_->get_communication_count();
    ui->comboCommunicationCount->addItem(tr("1"));
	ui->comboCommunicationCount->setCurrentText(QString::number(communicatin_count));

	std::string ip = MSysInfo::Instance()->basic_settings_->get_tcp_ip();
	ui->lineEditIP->setText(QString::fromStdString(ip));
	std::string port = MSysInfo::Instance()->basic_settings_->get_tcp_port();
	ui->lineEditPort->setText(QString::fromStdString(port));

	std::string serial_port_number = MSysInfo::Instance()->basic_settings_->get_serial_port_number();
	foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
		ui->comboSerialPortNumber->addItem(info.portName());
	ui->comboSerialPortNumber->setCurrentText(QString::fromStdString(serial_port_number));

	std::string baud_rate = MSysInfo::Instance()->basic_settings_->get_baud_rate();
	ui->comboBaudRate->addItem(tr("1200"));
	ui->comboBaudRate->addItem(tr("2400"));
	ui->comboBaudRate->addItem(tr("4800"));
	ui->comboBaudRate->addItem(tr("9600"));
	ui->comboBaudRate->addItem(tr("19200"));
	ui->comboBaudRate->addItem(tr("38400"));
	ui->comboBaudRate->addItem(tr("57600"));
	ui->comboBaudRate->addItem(tr("115200"));
	ui->comboBaudRate->addItem(tr("UnknownBaud"));
	ui->comboBaudRate->setCurrentText(QString::fromStdString(baud_rate));

	std::string parity_bits = MSysInfo::Instance()->basic_settings_->get_parity_bits();
	ui->comboParityBit->addItem(tr("NoParity"));
	ui->comboParityBit->addItem(tr("Even"));
	ui->comboParityBit->addItem(tr("Odd"));
	ui->comboParityBit->addItem(tr("Space"));
	ui->comboParityBit->addItem(tr("Mark"));
	ui->comboParityBit->addItem(tr("UnknownParity"));
	ui->comboParityBit->setCurrentText(QString::fromStdString(parity_bits));

	std::string data_bits = MSysInfo::Instance()->basic_settings_->get_data_bits();
	ui->comboDataBit->addItem(tr("5"));
	ui->comboDataBit->addItem(tr("6"));
	ui->comboDataBit->addItem(tr("7"));
	ui->comboDataBit->addItem(tr("8"));
	ui->comboDataBit->addItem(tr("UnknownDataBits"));
	ui->comboDataBit->setCurrentText(QString::fromStdString(data_bits));

	std::string stop_bits = MSysInfo::Instance()->basic_settings_->get_stop_bits();
	ui->comboStopBit->addItem(tr("1"));
	ui->comboStopBit->addItem(tr("1.5"));
	ui->comboStopBit->addItem(tr("2"));
	ui->comboStopBit->addItem(tr("UnknownStopBits"));
	ui->comboStopBit->setCurrentText(QString::fromStdString(stop_bits));
}

void SettingsWidget::on_lineEditIP_textChanged(const QString &ip)
{
	MSysInfo::Instance()->basic_settings_->set_tcp_ip(ip.toStdString());
    MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_lineEditPort_textChanged(const QString &port)
{
	MSysInfo::Instance()->basic_settings_->set_tcp_port(port.toStdString());
    MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::show_tcp_control(const bool &status) {
	if (status == true) {
		ui->labelIP->show();
		ui->labelPort->show();
		ui->lineEditIP->show();
		ui->lineEditPort->show();
	}
	else {
		ui->labelIP->hide();
		ui->labelPort->hide();
		ui->lineEditIP->hide();
		ui->lineEditPort->hide();
	}
}

void SettingsWidget::show_serial_port_control(const bool &status) {
	if (status) {
		ui->labelSerialPortNumber->show();	
		ui->labelBaudRate->show();
		ui->labelParityBit->show();
		ui->labelDataBit->show();
		ui->labelStopBit->show();
		ui->comboSerialPortNumber->show();
		ui->comboBaudRate->show();
		ui->comboParityBit->show();
		ui->comboDataBit->show();
		ui->comboStopBit->show();
	}
	else {
		ui->labelSerialPortNumber->hide();
		ui->labelBaudRate->hide();
		ui->labelParityBit->hide();
		ui->labelDataBit->hide();
		ui->labelStopBit->hide();
		ui->comboSerialPortNumber->hide();
		ui->comboBaudRate->hide();
		ui->comboParityBit->hide();
		ui->comboDataBit->hide();
		ui->comboStopBit->hide();
	}
}


void SettingsWidget::on_comboCameraType_currentIndexChanged(const QString &camera_type)
{
	MSysInfo::Instance()->basic_settings_->set_camera_type(camera_type.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboCameraCount_currentIndexChanged(const QString &camera_count)
{
	MSysInfo::Instance()->basic_settings_->set_camera_count(camera_count.toInt());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboCommunicationType_currentIndexChanged(const QString &communication_type)
{
	if (communication_type == "serial port") {
		show_serial_port_control(true);
		show_tcp_control(false);
	}
	else {
		show_serial_port_control(false);
		show_tcp_control(true);
	}
	MSysInfo::Instance()->basic_settings_->set_communication_type(communication_type.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboCommunicationCount_currentIndexChanged(const QString &communication_count)
{
	MSysInfo::Instance()->basic_settings_->set_communication_count(communication_count.toInt());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboSerialPortNumber_currentIndexChanged(const QString &serila_port_number)
{
	MSysInfo::Instance()->basic_settings_->set_serial_port_number(serila_port_number.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboBaudRate_currentIndexChanged(const QString &baud_rate)
{
	MSysInfo::Instance()->basic_settings_->set_baud_rate(baud_rate.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboParityBit_currentIndexChanged(const QString &parity_bit)
{
	MSysInfo::Instance()->basic_settings_->set_parity_bits(parity_bit.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}

void SettingsWidget::on_comboDataBit_currentIndexChanged(const QString &data_bit)
{
	MSysInfo::Instance()->basic_settings_->set_data_bits(data_bit.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
	
}

void SettingsWidget::on_comboStopBit_currentIndexChanged(const QString &stop_bit)
{
	MSysInfo::Instance()->basic_settings_->set_stop_bits(stop_bit.toStdString());
	MSysInfo::Instance()->configuration_->saveXML(MSysInfo::Instance()->get_configuration_xml().toStdString());
}
