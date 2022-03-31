#include "CameraWidget.h"
#include "ui_camerawidget.h"

CameraWidget::CameraWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CameraWidget)
{
    ui->setupUi(this);
    init();
}

CameraWidget::~CameraWidget()
{
    if (image_timer_->isActive() == true)
        image_timer_->stop();
    if(nullptr != image_timer_){
        delete image_timer_;
        image_timer_ = nullptr;
    }
    delete ui;
}

void CameraWidget::init(){
    camera_index_ = -1;
    int camera_count = MSysInfo::Instance()->basic_settings_->get_camera_count();
    for(int i = 0 ; i < camera_count; i++)
        ui->comboCameraIndex->addItem("camera " + QString::number(i));
    if(camera_count > 0 )
        ui->comboCameraIndex->setCurrentIndex(0);

    std::string camera_type = MSysInfo::Instance()->basic_settings_->get_camera_type();
    ui->comboCameraType->addItem(QString::fromStdString(camera_type));
    std::string camera_exposure = MSysInfo::Instance()->basic_settings_->get_camera_exposure();
    ui->lineEditExposure->setText(QString::fromStdString(camera_exposure));
    ui->comboTrigger->addItem("false");
    ui->comboTrigger->addItem("true");
    std::string camera_trigger = MSysInfo::Instance()->basic_settings_->get_camera_trigger();
    ui->comboTrigger->setCurrentText(QString::fromStdString(camera_trigger));

    image_timer_ = new QTimer(this);
    connect(image_timer_, &QTimer::timeout, this,&CameraWidget::update_image);
}

void CameraWidget::on_comboCameraIndex_currentIndexChanged(int camera_index)
{
    camera_index_ = camera_index;
}

void CameraWidget::on_comboTrigger_currentIndexChanged(const QString &trigger_mode)
{
    if(-1 == camera_index_)
        return;
    MSysInfo::Instance()->vec_camera_[camera_index_]->set_trigger_mode(
                (static_cast<QVariant>(trigger_mode)).toBool());
}

void CameraWidget::on_lineEditExposure_textChanged(const QString &exposure)
{
    if(-1 == camera_index_)
        return;
    MSysInfo::Instance()->vec_camera_[camera_index_]->set_exposure(exposure.toDouble());
}

void CameraWidget::on_btnGrab_clicked()
{
    if (image_timer_->isActive() == false)
        image_timer_->start(200);
}

void CameraWidget::on_btnStop_clicked()
{
    if (image_timer_->isActive() == true)
        image_timer_->stop();
}

void CameraWidget::on_btnSnap_clicked()
{
    update_image();
}

void CameraWidget::update_image(){
    HalconCpp::HObject himage;
    if(true == MSysInfo::Instance()->vec_camera_[camera_index_]->snap(himage)){
        QImage img;
        if(true == hobject_to_qimage(himage, &img)){
            send_image_to_main_window(img);
        }
    }
}

bool CameraWidget::hobject_to_qimage(HalconCpp::HObject himage, QImage *qimage){
    HalconCpp::HTuple hChannels;
    HalconCpp::HTuple width, height;
    HalconCpp::HTuple htype;
    ConvertImageType(himage, &himage, "byte");//��ͼƬת����byte����
    CountChannels(himage, &hChannels);       //�ж�ͼ��ͨ����

    if (hChannels[0].I() == 1)//��ͨ��ͼ
    {
        HalconCpp::HTuple hv_pointer;
        unsigned char *ptr;
        GetImagePointer1(himage, &hv_pointer, &htype, &width, &height);

        ptr = (unsigned char *)hv_pointer[0].L();

        *qimage = QImage(ptr, width, height, width, QImage::Format_Grayscale8);//��֪���Ƿ����Զ�4�ֽڶ���
    }
    else if (hChannels[0].I() == 3)//��ͨ��ͼ
    {
        HalconCpp::HTuple hv_ptrRed, hv_ptrGreen, hv_ptrBlue;
        GetImagePointer3(himage, &hv_ptrRed, &hv_ptrGreen, &hv_ptrBlue, &htype, &width, &height);

        uchar *ptrRed = (uchar*)hv_ptrRed[0].L();
        uchar *ptrGreen = (uchar*)hv_ptrGreen[0].L();
        uchar *ptrBlue = (uchar*)hv_ptrBlue[0].L();
        int bytesperline = (width * 8 * 3 + 31) / 32 * 4;//����λ��Ϊ8����ͨ��ͼ����ÿ��4�ֽڶ��벹��
        int bytecount = bytesperline * height;//����ͼ��������Ҫ���ֽ���
        uchar* data8 = new uchar[bytecount];
        int lineheadid, pixid;
        for (int i = 0; i < height; i++)
        {
            lineheadid = bytesperline * i;//������ͼ����i�е�������ͼ�������еĵ�ַ
            for (int j = 0; j < width; j++)
            {
                pixid = lineheadid + j * 3;//��������Ϊ��i��j��������id
                data8[pixid] = ptrRed[width*i + j];
                data8[pixid + 1] = ptrGreen[width*i + j];
                data8[pixid + 2] = ptrBlue[width*i + j];
            }
        }
        *qimage = QImage(data8, width, height, QImage::Format_RGB888);
    }
    else{
        return false;
    }
    return true;
}

void CameraWidget::stop_camera_timer(const bool &status) {
	if (status == true) {
		if (image_timer_->isActive() == true)
			image_timer_->stop();
	}
	else {
		if (image_timer_->isActive() == false)
			image_timer_->start(200);
	}
}
