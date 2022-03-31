#ifndef CAMERAWIDGET_H
#define CAMERAWIDGET_H

#include <QWidget>
#include <QTimer>
#include "DataStructure/Configuration/MSysInfo.h"

namespace Ui {
class CameraWidget;
}

class CameraWidget : public QWidget{
    Q_OBJECT
public:
    explicit CameraWidget(QWidget *parent = nullptr);
    ~CameraWidget();
    void init();
	void stop_camera_timer(const bool &status);
    bool hobject_to_qimage(HalconCpp::HObject himage, QImage *qimage);
signals:
    void send_image_to_main_window(const QImage &img);
private slots:
    void on_comboCameraIndex_currentIndexChanged(int index);
    void on_comboTrigger_currentIndexChanged(const QString &arg1);
    void on_lineEditExposure_textChanged(const QString &arg1);
    void on_btnGrab_clicked();
    void on_btnStop_clicked();
    void on_btnSnap_clicked();
    void update_image();
private:
    Ui::CameraWidget *ui;
    int camera_index_;
    QTimer *image_timer_;
};

#endif // CAMERAWIDGET_H
