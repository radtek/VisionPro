#ifndef MAUTHORITYSETTINGS_H
#define MAUTHORITYSETTINGS_H

class MAuthoritySettings{
public:
    explicit MAuthoritySettings();
    ~MAuthoritySettings();

    MAuthoritySettings(const MAuthoritySettings& rhs) = delete;
    MAuthoritySettings& operator=(const MAuthoritySettings& rhs) = delete;
    MAuthoritySettings(MAuthoritySettings&& rhs) = delete;
    MAuthoritySettings& operator=(MAuthoritySettings&& rhs) = delete;
};

#endif // MAUTHORITYSETTINGS_H
