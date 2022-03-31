#include "MCameraSimulator.h"

MCameraSimulator::MCameraSimulator()
    :MCameraBase(),camera_id_(new int (-1)), image_mode_(0){

}

MCameraSimulator::~MCameraSimulator(){
    if(nullptr != camera_id_){
        delete camera_id_;
        camera_id_ = nullptr;
    }
}

MCameraSimulator::MCameraSimulator(const MCameraSimulator &rhs)
    :camera_id_(new int(*rhs.camera_id_)),image_mode_(rhs.image_mode_)
{
    //std::copy(rhs.camera_id_, rhs.camera_id_+1, camera_id_);

}

MCameraSimulator& MCameraSimulator::operator=(const MCameraSimulator &rhs){
    if(this == &rhs)
        return *this;
    int *newp = new int(*rhs.camera_id_);
    delete camera_id_;
    camera_id_ = newp;
    //std::copy(rhs.camera_id_, rhs.camera_id_+1, camera_id_);
    image_mode_ = rhs.image_mode_;
    return *this;
}

MCameraSimulator::MCameraSimulator(MCameraSimulator &&rhs)
    :camera_id_(rhs.camera_id_),image_mode_(rhs.image_mode_){
    rhs.camera_id_ = nullptr;
    rhs.image_mode_ = 0;
}

MCameraSimulator& MCameraSimulator::operator=(MCameraSimulator &&rhs){
    if(this == &rhs)
        return *this;
    //std::swap(camera_id_, rhs.camera_id_);
    delete camera_id_;
    camera_id_ = rhs.camera_id_;
    rhs.camera_id_ = nullptr;

    image_mode_ = rhs.image_mode_;
    rhs.image_mode_ = 0;
    return *this;
}

void MCameraSimulator::init(){
    camera_id_ = new int(-1);
    image_mode_ = 0;
}

void MCameraSimulator::open() {

}

bool MCameraSimulator::is_open(){
    return true;
}

bool MCameraSimulator::snap(HalconCpp::HObject &h_object_){
	try {
		HalconCpp::ReadImage(&h_object_, "D:/Projects/VisionPro/yolo.jpg");
		switch (image_mode_) {
		case 0:
			HalconCpp::RotateImage(h_object_, &h_object_, 0, "constant");
			break;
		case 1:
			HalconCpp::RotateImage(h_object_, &h_object_, 90, "constant");
			break;
		case 2:
			HalconCpp::RotateImage(h_object_, &h_object_, 180, "constant");
			break;
		case 3:
			HalconCpp::RotateImage(h_object_, &h_object_, 270, "constant");
			break;
		case 4:
			HalconCpp::MirrorImage(h_object_, &h_object_, "row");
			break;
		case 5:
			HalconCpp::MirrorImage(h_object_, &h_object_, "column");
			break;
		default:
			break;

		}
	}
	catch (...) {
		false;
	}
    return true;
}

void MCameraSimulator::close(){

}


void MCameraSimulator::set_trigger_mode(bool trigger_mode){

}

void MCameraSimulator::set_exposure(double exposure) {


}

void MCameraSimulator::set_image_mode(const int &image_mode){
    image_mode_ = image_mode;
}
