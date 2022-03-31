#ifndef MTHREADTASK_H
#define MTHREADTASK_H

#include <thread>
#include <QObject>
#include <vector>
#include "DataStructure/Camera/MCameraBase.h"
#include "DataStructure/Communication/MCommunicationBase.h"
#include "DataStructure/Log/MLog.h"

class MThreadTask : public QObject{
    Q_OBJECT
public:
    explicit MThreadTask(MCameraBase *camera, MCommunicationBase *communication,QObject *parent = nullptr);
    ~MThreadTask();

    MThreadTask(const MThreadTask &rhs) = delete;
    MThreadTask& operator=(const MThreadTask &rhs) = delete;
    MThreadTask(MThreadTask &&rhs) = delete;
    MThreadTask& operator=(MThreadTask &&rhs) = delete;

    bool isRunning() const;
    void run();
    void start();
    void stop();

signals:
	void send_image_to_main_window(HalconCpp::HObject image);
private:
    volatile bool stopped_;
    std::thread task_thread_;
    QString recv_msg_;
    MCameraBase *camera_;
    MCommunicationBase *communication_;
};

#endif // MTHREADTASK_H
