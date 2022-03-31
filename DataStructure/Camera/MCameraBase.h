#ifndef MCAMERABASE_H
#define MCAMERABASE_H

#include "HalconCpp.h"
#include <algorithm>

class MCameraBase{
public:
    virtual ~MCameraBase();

    MCameraBase(const MCameraBase &rhs) = delete;
    MCameraBase& operator=(const MCameraBase &rhs) = delete;

    MCameraBase(MCameraBase &&rhs);
    MCameraBase& operator=(MCameraBase &&rhs);

    virtual void init() = 0;
    virtual void open() = 0;
    virtual bool is_open() = 0;
    virtual bool snap(HalconCpp::HObject &image) = 0;
    virtual void close() = 0;

	virtual void set_trigger_mode(bool trigger_mode) = 0;
    virtual void set_exposure(double exposure) = 0;
    virtual void set_image_mode(const int &image_mode) = 0;

protected:
    explicit MCameraBase();

};

#endif // MCAMERABASE_H
