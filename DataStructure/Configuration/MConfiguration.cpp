#include "MConfiguration.h"

MConfiguration::MConfiguration( MBasicSettings* basic_settings,  MAdvancedSettings* advanced_settings,MAuthoritySettings *authority_settings){
	basic_settings_ = basic_settings;
	advanced_settings_ = advanced_settings;
    authority_settings_ = authority_settings;
}

MConfiguration::~MConfiguration(){

}

void MConfiguration::createXML(const std::string &file_path){
    static const char* xml =
            "<?xml version=\"1.0\"?>"
            "<BASICCONFIGURATION>"
            "<CAMERATYPE>simulator</CAMERATYPE>"
            "<CAMERACOUNT>1</CAMERACOUNT>"
			"<CAMERAEXPOSURE>5000</CAMERAEXPOSURE>"
			"<CAMERATRIGGER>false</CAMERATRIGGER>"
            "<COMMUNICATIONTYPE>tcp server</COMMUNICATIONTYPE>"
            "<COMMUNICATIONCOUNT>1</COMMUNICATIONCOUNT>"
			"<TCPIP>127.0.0.1</TCPIP>"
			"<TCPPORT>8000</TCPPORT>"
			"<SERIALPORTNUMBER>COM1</SERIALPORTNUMBER>"
			"<BAUDRATE>9600</BAUDRATE>"
			"<PARITYBITS>NONE</PARITYBITS>"
			"<DATABITS>8</DATABITS>"
			"<STOPBITS>1</STOPBITS>"
            "</BASICCONFIGURATION>"
            "<ADVANCEDCONFIGURATION>"
            "</ADVANCEDCONFIGURATION>";
        doc_.Parse(xml);
        doc_.SaveFile(file_path.c_str());
}

bool MConfiguration::loadXML(const std::string &file_path){
    doc_.LoadFile(file_path.c_str());

    if (tinyxml2::XML_SUCCESS != doc_.ErrorID()) {
        return false;
    }

    tinyxml2::XMLElement* titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERATYPE");
    const char *camera_type = titleBasicElement->GetText();
    basic_settings_->set_camera_type(camera_type);

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERACOUNT");
    const char *camera_count = titleBasicElement->GetText();
    basic_settings_->set_camera_count(atoi(camera_count));

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("COMMUNICATIONTYPE");
    const char *communication_type = titleBasicElement->GetText();
    basic_settings_->set_communication_type(communication_type);

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("COMMUNICATIONCOUNT");
    const char *communication_count = titleBasicElement->GetText();
    basic_settings_->set_communication_count(atoi(communication_count));

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERATRIGGER");
	const char *camera_trigger = titleBasicElement->GetText();
    basic_settings_->set_camera_trigger(camera_trigger);

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERAEXPOSURE");
	const char *camera_exposure = titleBasicElement->GetText();
	basic_settings_->set_camera_exposure(camera_exposure);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("TCPIP");
	const char *tcp_ip = titleBasicElement->GetText();
	basic_settings_->set_tcp_ip(tcp_ip);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("TCPPORT");
	const char *tcp_port = titleBasicElement->GetText();
	basic_settings_->set_tcp_port(tcp_port);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("SERIALPORTNUMBER");
	const char *serial_port_number = titleBasicElement->GetText();
	basic_settings_->set_serial_port_number(serial_port_number);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("BAUDRATE");
	const char *baud_rate = titleBasicElement->GetText();
	basic_settings_->set_baud_rate(baud_rate);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("PARITYBITS");
	const char *parity_bits = titleBasicElement->GetText();
	basic_settings_->set_parity_bits(parity_bits);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("DATABITS");
	const char *data_bits = titleBasicElement->GetText();
	basic_settings_->set_data_bits(data_bits);

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("STOPBITS");
	const char *stop_bits = titleBasicElement->GetText();
	basic_settings_->set_stop_bits(stop_bits);

    return true;
}

bool MConfiguration::saveXML(const std::string &file_path){
    doc_.LoadFile(file_path.c_str());
    if (tinyxml2::XML_SUCCESS != doc_.ErrorID())
    {
        return false;
    }

    tinyxml2::XMLElement* titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERATYPE");
    titleBasicElement->SetText(basic_settings_->get_camera_type().c_str());

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERACOUNT");
    titleBasicElement->SetText(std::to_string(basic_settings_->get_camera_count()).c_str());

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("COMMUNICATIONTYPE");
    titleBasicElement->SetText(basic_settings_->get_communication_type().c_str());

    titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("COMMUNICATIONCOUNT");
    titleBasicElement->SetText(std::to_string(basic_settings_->get_communication_count()).c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERATRIGGER");
	titleBasicElement->SetText(basic_settings_->get_camera_trigger().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("CAMERAEXPOSURE");
	titleBasicElement->SetText(basic_settings_->get_camera_exposure().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("TCPIP");
	titleBasicElement->SetText(basic_settings_->get_tcp_ip().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("TCPPORT");
	titleBasicElement->SetText(basic_settings_->get_tcp_port().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("SERIALPORTNUMBER");
	titleBasicElement->SetText(basic_settings_->get_serial_port_number().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("BAUDRATE");
	titleBasicElement->SetText(basic_settings_->get_baud_rate().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("PARITYBITS");
	titleBasicElement->SetText(basic_settings_->get_parity_bits().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("DATABITS");
	titleBasicElement->SetText(basic_settings_->get_data_bits().c_str());

	titleBasicElement = doc_.FirstChildElement("BASICCONFIGURATION")->FirstChildElement("STOPBITS");
	titleBasicElement->SetText(basic_settings_->get_stop_bits().c_str());

    return doc_.SaveFile(file_path.c_str());
}


