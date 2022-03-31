#ifndef MCONFIGURATION_H
#define MCONFIGURATION_H

#include "tinyxml2.h"
#include "DataStructure/Configuration/MBasicSettings.h"
#include "DataStructure/Configuration/MAuthoritySettings.h"
#include "DataStructure/Configuration/MAdvancedSettings.h"

class MConfiguration
{
public:
    explicit MConfiguration(MBasicSettings* basic_settings, MAdvancedSettings* advanced_settings ,MAuthoritySettings *authority_settings);
    ~MConfiguration();

    MConfiguration(const MConfiguration& rhs) = delete;
    MConfiguration& operator=(const MConfiguration& rhs) = delete;
    MConfiguration(MConfiguration&& rhs) = delete;
    MConfiguration& operator=(MConfiguration&& rhs) = delete;

    void createXML(const std::string &file_path);
    bool loadXML(const std::string &file_path);
    bool saveXML(const std::string &file_path);

private:
    tinyxml2::XMLDocument doc_;
	MBasicSettings *basic_settings_;
	MAdvancedSettings *advanced_settings_;
    MAuthoritySettings *authority_settings_;  
};

#endif // MCONFIGURATION_H
