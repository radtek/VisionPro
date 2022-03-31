#include "MThreadTask.h"

MThreadTask::MThreadTask(MCameraBase *camera, MCommunicationBase *communication,QObject *parent)
    :camera_(camera),communication_(communication),QObject(parent),stopped_(true),recv_msg_(""){
    task_thread_ = std::thread(&MThreadTask::run, this);
	connect(communication_, &MCommunicationBase::sendMsg, [=](const QString &data) {
		recv_msg_ = data;
	});
}

MThreadTask::~MThreadTask()
{
	communication_->disconnect();	
    if (task_thread_.joinable()) {
        task_thread_.detach();
    }
}

void MThreadTask::run(){
    while(true){
        if(!stopped_){          
            if ("T1" != recv_msg_) {
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
				continue;
			}

            MLog::Instance()->log_message("recv msg", "info");
            recv_msg_ = "";
			HalconCpp::HObject image;
            if (false == camera_->snap(image))
			{

			}
			emit send_image_to_main_window(image);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        continue;
    }
}

void MThreadTask::start(){
    stopped_ = false;
}

void MThreadTask::stop(){
    stopped_ = true;
}

bool MThreadTask::isRunning() const{
    return !stopped_;
}


