#ifndef MCAMERASIMULATOR_H
#define MCAMERASIMULATOR_H

#include "MCameraBase.h"

class MCameraSimulator : public MCameraBase{
public:
    explicit MCameraSimulator();
    ~MCameraSimulator();

    MCameraSimulator(const MCameraSimulator &rhs);
    MCameraSimulator& operator=(const MCameraSimulator &rhs);
    MCameraSimulator(MCameraSimulator &&rhs);
    MCameraSimulator& operator=(MCameraSimulator &&rhs);

    void init() override;
    void open() override;
    bool is_open() override;
    bool snap(HalconCpp::HObject &h_object_) override;
    void close() override;

    void set_trigger_mode(bool trigger_mode) override;
    void set_exposure(double exposure) override;
    void set_image_mode(const int &image_mode) override;

private:
    int *camera_id_;
    int image_mode_;
};

#endif // MCAMERASIMULATOR_H
