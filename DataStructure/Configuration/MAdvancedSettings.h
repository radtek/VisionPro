#ifndef MADVANCEDSETTINGS_H
#define MADVANCEDSETTINGS_H

#include <string>

class MAdvancedSettings{
public:
    explicit MAdvancedSettings();
    ~MAdvancedSettings();

    MAdvancedSettings(const MAdvancedSettings& rhs)= delete ;
    MAdvancedSettings& operator=(const MAdvancedSettings& rhs) = delete;
    MAdvancedSettings(MAdvancedSettings&& rhs)= delete ;
    MAdvancedSettings& operator=(MAdvancedSettings&& rhs) = delete;
};

#endif // MADVANCEDSETTINGS_H
