#include "MBasicSettings.h"

MBasicSettings::MBasicSettings()
	:camera_type_{ "" }, camera_count_{ 0 }, camera_exposure_{ "" }, camera_trigger_{""},
	communication_type_{ "" }, communication_count_{ 0 }, tcp_ip_{ "" }, tcp_port_{""},
	serial_port_number_{ "" }, baud_rate_{ "" }, parity_bits_{ "" }, data_bits_{ "" }, stop_bits_{""}{

}

MBasicSettings::~MBasicSettings(){

}

MBasicSettings::MBasicSettings(const MBasicSettings& rhs) {
	if (this == &rhs)
		return;
	camera_type_ = rhs.camera_type_;
	camera_count_ = rhs.camera_count_;
	camera_exposure_ = rhs.camera_exposure_;
	camera_trigger_ = rhs.camera_trigger_;
	communication_type_ = rhs.communication_type_;
	communication_count_ = rhs.communication_count_;
	tcp_ip_ = rhs.tcp_ip_;
	tcp_port_ = rhs.tcp_port_;
	serial_port_number_ = rhs.serial_port_number_;
	baud_rate_ = rhs.baud_rate_;
	parity_bits_ = rhs.parity_bits_;
	data_bits_ = rhs.data_bits_;
	stop_bits_ = rhs.stop_bits_;
}

MBasicSettings& MBasicSettings::operator=(const MBasicSettings& rhs) {
	if (this == &rhs)
		return *this;
	camera_type_ = rhs.camera_type_;
	camera_count_ = rhs.camera_count_;
	camera_exposure_ = rhs.camera_exposure_;
	camera_trigger_ = rhs.camera_trigger_;
	communication_type_ = rhs.communication_type_;
	communication_count_ = rhs.communication_count_;
	tcp_ip_ = rhs.tcp_ip_;
	tcp_port_ = rhs.tcp_port_;
	serial_port_number_ = rhs.serial_port_number_;
	baud_rate_ = rhs.baud_rate_;
	parity_bits_ = rhs.parity_bits_;
	data_bits_ = rhs.data_bits_;
	stop_bits_ = rhs.stop_bits_;
	return *this;
}

void MBasicSettings::set_camera_type(const std::string &camera_type){
    camera_type_ = camera_type;
}

std::string MBasicSettings::get_camera_type() const{
    return camera_type_;
}

void MBasicSettings::set_camera_count(const int &camera_count){
    camera_count_ = camera_count;
}

int MBasicSettings::get_camera_count() const{
    return camera_count_;
}

void MBasicSettings::set_camera_exposure(const std::string &camera_exposure) {
	camera_exposure_ = camera_exposure;
}

std::string MBasicSettings::get_camera_exposure() const {
	return camera_exposure_;
}

void MBasicSettings::set_camera_trigger(const std::string &camera_trigger) {
	camera_trigger_ = camera_trigger;
}

std::string MBasicSettings::get_camera_trigger()const {
	return camera_trigger_;
}

void MBasicSettings::set_communication_type(const std::string &communication_type){
    communication_type_ = communication_type;
}

std::string MBasicSettings::get_communication_type() const{
    return communication_type_;
}

void MBasicSettings::set_communication_count(const int &communication_count){
    communication_count_ = communication_count;
}

int MBasicSettings::get_communication_count() const{
    return communication_count_;
}

void MBasicSettings::set_tcp_ip(const std::string &ip) {
	tcp_ip_ = ip;
}

std::string MBasicSettings::get_tcp_ip()const {
	return tcp_ip_;
}

void MBasicSettings::set_tcp_port(const std::string &port) {
	tcp_port_ = port;
}

std::string MBasicSettings::get_tcp_port() {
	return tcp_port_;
}

void MBasicSettings::set_serial_port_number(const std::string &serial_port_number) {
	serial_port_number_ = serial_port_number;
}

std::string MBasicSettings::get_serial_port_number() const {
	return serial_port_number_;
}

void MBasicSettings::set_baud_rate(const std::string &baud_rate) {
	baud_rate_ = baud_rate;
}

std::string MBasicSettings::get_baud_rate() const {
	return baud_rate_;
}

void MBasicSettings::set_parity_bits(const std::string & parity_bits) {
	parity_bits_ = parity_bits;
}

std::string MBasicSettings::get_parity_bits() const {
	return parity_bits_;
}


void MBasicSettings::set_data_bits(const std::string &data_bits) {
	data_bits_ = data_bits;
}

std::string MBasicSettings::get_data_bits() const {
	return data_bits_;
}

void MBasicSettings::set_stop_bits(const std::string &stop_bits) {
	stop_bits_ = stop_bits;
}

std::string MBasicSettings::get_stop_bits() const {
	return stop_bits_;
}
