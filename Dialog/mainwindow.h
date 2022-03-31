#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMetaType>
#include "Dialog/CameraWidget.h"
#include "Dialog/CommunicationWidget.h"
#include "Dialog/SettingsWidget.h"
#include "Dialog/StatisticsWidget.h"
#include "DataStructure/Thread/MThreadTask.h"
#include "DataStructure/Configuration/MSysInfo.h"
#include "DataStructure/Log/MLog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void init();
	void HObjectToQImage(HalconCpp::HObject himage, QImage *qimage);
private slots:
	void recv_image_from_task_thread(HalconCpp::HObject image);
    void on_action_start_triggered();
    void on_action_stop_triggered();
    void on_action_reset_triggered();
private:
    Ui::MainWindow *ui;
    CameraWidget *camera_widget_;
    CommunicationWidget *communication_widget_;
    SettingsWidget *settings_widget_;
    StatisticsWidget *statistics_widget_;
    MThreadTask *thread_task_;

};
#endif // MAINWINDOW_H
