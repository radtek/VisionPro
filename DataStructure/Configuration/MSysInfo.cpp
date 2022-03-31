#include "MSysInfo.h"

MSysInfo *MSysInfo::instance_ = nullptr;

MSysInfo::MSysInfo(){

}

MSysInfo *MSysInfo::Instance(){
    if(nullptr == instance_){
        instance_ = new MSysInfo;
    }
    return instance_;
}

MSysInfo::~MSysInfo(){
    if(nullptr != basic_settings_){
        delete basic_settings_;
        basic_settings_ = nullptr;
    }

    if(nullptr != advanced_settings_){
        delete advanced_settings_;
        advanced_settings_ = nullptr;
    }

    if(nullptr != authority_settings_){
        delete authority_settings_;
        authority_settings_ = nullptr;
    }

    if(nullptr != configuration_){
        delete configuration_;
        configuration_ = nullptr;
    }

	if (nullptr != instance_) {
		delete instance_;
		instance_ = nullptr;
	}
}

void MSysInfo::init(){
    //configuration file
    QDir dir;
    QString configuration_path_ = QDir::currentPath();
    QString my_folder_ = configuration_path_ + "/MyFolder";
    if (!dir.exists(my_folder_)) {
        dir.mkdir(my_folder_);
    }
    QString configuration_folder_ = my_folder_ + "/Configuration";
    configuration_xml_ = configuration_folder_ + "/configuration.xml";
    basic_settings_ = new MBasicSettings;
    advanced_settings_ = new MAdvancedSettings;
    authority_settings_ = new MAuthoritySettings;
    configuration_ = new MConfiguration(basic_settings_, advanced_settings_, authority_settings_);
    if (!dir.exists(configuration_folder_)) {
        dir.mkdir(configuration_folder_);
    }

    QFile file_configuration_xml(configuration_xml_);
    if (!file_configuration_xml.exists())
    {
        configuration_->createXML(configuration_xml_.toStdString());
    }
    configuration_->loadXML(configuration_xml_.toStdString());

	//configuration camera
	int camera_count = basic_settings_->get_camera_count();
	std::string camera_type = basic_settings_->get_camera_type();
	std::string camera_exposure = basic_settings_->get_camera_exposure();
	std::string camera_trigger = basic_settings_->get_camera_trigger();
	for (int i = 0; i < camera_count; ++i) {
		if ("simulator" == camera_type) {
			vec_camera_.push_back(new MCameraSimulator);
		}
		vec_camera_[i]->init();
		vec_camera_[i]->set_exposure(std::atof(camera_exposure.c_str()));
		if(camera_trigger == "true")
			vec_camera_[i]->set_trigger_mode(true);
		else
			vec_camera_[i]->set_trigger_mode(false);
	}
	//configuration communication
	int communication_cout = basic_settings_->get_communication_count();
	std::string communication_type = basic_settings_->get_communication_type();
	

	for (int i = 0; i < communication_cout; ++i) {
		if ("tcp server" == communication_type)
			vec_communication_.push_back(new MCommunicationTcpServer);
		else if ("tcp client" == communication_type)
			vec_communication_.push_back(new MCommunicationTcpClient);
		else if("serial port" == communication_type)
			vec_communication_.push_back(new MCommunicationSerialPort);
		vec_communication_[i]->init();
		
	}
}

QString MSysInfo::get_configuration_xml() const {
	return configuration_xml_;
}

bool MSysInfo::open(){
	std::string communication_type = basic_settings_->get_communication_type();
	for (std::vector<MCameraBase*>::iterator iter = vec_camera_.begin(); iter != vec_camera_.end(); ++iter) {
		(*iter)->open();
	}
	for (std::vector<MCommunicationBase*>::iterator iter = vec_communication_.begin(); iter != vec_communication_.end(); ++iter) {
		if ("tcp server" == communication_type || "tcp client" == communication_type) {
			std::string tcp_ip = basic_settings_->get_tcp_ip();
			std::string tcp_port = basic_settings_->get_tcp_port();
			(*iter)->open(QString::fromStdString(tcp_ip), std::atoi(tcp_port.c_str()));
		}
		else if ("serial port" == communication_type) {
			std::string serial_port_number = MSysInfo::Instance()->basic_settings_->get_serial_port_number();
			std::string baud_rate = MSysInfo::Instance()->basic_settings_->get_baud_rate();
			std::string parity_bits = MSysInfo::Instance()->basic_settings_->get_parity_bits();
			std::string data_bits = MSysInfo::Instance()->basic_settings_->get_data_bits();
			std::string stop_bits = MSysInfo::Instance()->basic_settings_->get_stop_bits();
			(*iter)->open(QString::fromStdString(serial_port_number), QString::fromStdString(baud_rate),
						  QString::fromStdString(parity_bits), QString::fromStdString(data_bits), QString::fromStdString(stop_bits));				
		}	
	}
    return true;
}

bool MSysInfo::close(){
	for (std::vector<MCameraBase*>::iterator iter = vec_camera_.begin(); iter != vec_camera_.end(); ++iter) {
		(*iter)->close();
	}
	for (std::vector<MCommunicationBase*>::iterator iter = vec_communication_.begin(); iter != vec_communication_.end(); ++iter) {
		
		(*iter)->close();
	}
    return true;
}

std::vector<std::string> MSysInfo::split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();
	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}
