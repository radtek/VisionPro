#include "MLog.h"

MLog *MLog::instance_ = nullptr;

MLog::MLog(QObject *parent)
    : QObject(parent){

}

MLog::~MLog(){
    if(instance_ != nullptr){
        delete instance_;
        instance_ = nullptr;
    }
}

MLog *MLog::Instance(){
    if(nullptr == instance_)
        instance_ = new MLog;
    return instance_;
}

void MLog::log_message(const QString& message, const QString &level)
{
   QTime current_time =QTime::currentTime();
   QString current_time_ = current_time.toString("hh:mm:ss");
   emit send_log(current_time_, message, level);
}
