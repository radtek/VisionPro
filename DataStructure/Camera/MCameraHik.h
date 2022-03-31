#ifndef MCAMERAHIK_H
#define MCAMERAHIK_H

#include "MCameraBase.h"
#include "MvCameraControl.h"
#include <stdio.h>
#include <string.h>

class MCameraHik : public MCameraBase{
public:
    explicit MCameraHik();
    ~MCameraHik();
    MCameraHik(const MCameraHik &rhs) = delete;
    MCameraHik& operator=(const MCameraHik &rhs) = delete;

    MCameraHik(MCameraHik &&rhs) ;
    MCameraHik& operator=(MCameraHik &&rhs);

    void init() override;
    void open() override;
    bool is_open() override;
    bool snap(HalconCpp::HObject& image) override;
    void close() override;

	void set_trigger_mode(bool trigger_mode) override;
    void set_exposure(double exposure) override;
    void set_image_mode(const int &image_mode) override;
	
private:
	MV_CC_DEVICE_INFO_LIST stDeviceList;
	void* handle;
    int image_mode_;  
};

#endif // MCAMERAHIK_H
