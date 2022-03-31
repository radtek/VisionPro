#ifndef MSYSINFO_H
#define MSYSINFO_H

#include <QDir>
#include <QString>
#include <string>
#include <vector>
#include "DataStructure/Configuration/MBasicSettings.h"
#include "DataStructure/Configuration/MAdvancedSettings.h"
#include "DataStructure/Configuration/MAuthoritySettings.h"
#include "DataStructure/Configuration/MConfiguration.h"
#include "DataStructure/Communication/MCommunicationBase.h"
#include "DataStructure/Communication/MCommunicationSerialPort.h"
#include "DataStructure/Communication/MCommunicationTcpClient.h"
#include "DataStructure/Communication/MCommunicationTcpServer.h"
#include "DataStructure/Camera/MCameraBase.h"
#include "DataStructure/Camera/MCameraHik.h"
#include "DataStructure/Camera/MCameraSimulator.h"

class MSysInfo{
public:
    ~MSysInfo();
    MSysInfo(const MSysInfo &rhs) = delete;
    MSysInfo& operator=(const MSysInfo &rhs) = delete;
    MSysInfo(MSysInfo &&rhs) = delete;
    MSysInfo& operator=(MSysInfo &&rhs) = delete;

    static MSysInfo *Instance();
    void init();
    bool open();
    bool close();
	QString get_configuration_xml() const;

	std::vector<std::string> split(std::string str, std::string pattern);
	std::vector<MCameraBase*> vec_camera_;
	std::vector<MCommunicationBase*> vec_communication_;

    MBasicSettings *basic_settings_;
    MAdvancedSettings *advanced_settings_;
    MAuthoritySettings *authority_settings_;
    MConfiguration *configuration_;

protected:
    explicit MSysInfo();
private:
    static MSysInfo *instance_;
    QString configuration_xml_;

};

#endif // MSYSINFO_H
