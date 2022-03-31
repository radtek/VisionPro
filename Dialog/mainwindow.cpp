#include "Dialog/mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    setWindowIcon(QIcon("Icon/recognition.png"));
    setWindowTitle(tr("南京奥纵智能科技有限公司"));
    setWindowFlags(Qt::CustomizeWindowHint
        | Qt::WindowTitleHint
        | Qt::WindowMinimizeButtonHint
        | Qt::WindowMaximizeButtonHint
        | Qt::WindowCloseButtonHint
    );
    qRegisterMetaType<HalconCpp::HObject>("HalconCpp::HObject");
    init();
}

void MainWindow::init(){
    //init tab widget
    camera_widget_ = new CameraWidget(this);
    communication_widget_ = new CommunicationWidget(this);
    settings_widget_ = new SettingsWidget(this);
    statistics_widget_ = new StatisticsWidget(this);
	ui->tabWidget->insertTab(0, camera_widget_, QIcon("Icon/camera.png"), tr("camera"));
	ui->tabWidget->insertTab(1, communication_widget_, QIcon("Icon/communication.png"), tr("communication"));
	ui->tabWidget->insertTab(2, settings_widget_, QIcon("Icon/settings.png"), tr("settings"));
    ui->tabWidget->insertTab(3,statistics_widget_, QIcon("Icon/statistics.png"),tr("statistics"));
	ui->action_start->setIcon(QIcon("Icon/start.png"));
	ui->action_stop->setIcon(QIcon("Icon/stop.png"));
	ui->action_reset->setIcon(QIcon("Icon/reset.png")); 

    connect(MLog::Instance(), &MLog::send_log, this, [=](QString timer, QString message, QString level){
        QString msg = "[" + timer +"][" + level + "][" + message + "]";
        QListWidgetItem * item = new QListWidgetItem;
        item->setText(msg);
        ui->listWidget->addItem(item);
        ui->listWidget->setCurrentItem(item);
        update();
    });
}


MainWindow::~MainWindow()
{
	if (nullptr != thread_task_) {
		if (thread_task_->isRunning()) {
			thread_task_->stop();
		}
		delete thread_task_;
		thread_task_ = nullptr;
	}
    
	MSysInfo::Instance()->close();
   
    if(nullptr != camera_widget_){
        delete  camera_widget_;
        camera_widget_ = nullptr;
    }
    if(nullptr != communication_widget_){
        delete communication_widget_;
        communication_widget_ = nullptr;
    }
    if(nullptr != settings_widget_){
        delete settings_widget_;
        settings_widget_ = nullptr;
    }
    if(nullptr != statistics_widget_){
        delete statistics_widget_;
        statistics_widget_ = nullptr;
    }

	
    delete ui;
}

void MainWindow::recv_image_from_task_thread(HalconCpp::HObject image) {
	QImage image_;
	HObjectToQImage(image, &image_);
	QPixmap fitpixmap = QPixmap::fromImage(image_).scaled(ui->labelImage->width(), ui->labelImage->height(),
		Qt::KeepAspectRatio, Qt::SmoothTransformation);
	ui->labelImage->setAlignment(Qt::AlignCenter);
	ui->labelImage->setPixmap(fitpixmap);
	static int index = 0;
	statusBar()->showMessage("image index:" + QString::number(++index));
	update();
}

void MainWindow::on_action_start_triggered(){
	if (ui->action_start->isChecked() == false) {
		ui->action_start->setEnabled(false);
		ui->action_stop->setEnabled(true);       
        thread_task_ = new MThreadTask(std::move(MSysInfo::Instance()->vec_camera_[0]),
                                        std::move(MSysInfo::Instance()->vec_communication_[0]),
                this);
		connect(thread_task_, &MThreadTask::send_image_to_main_window, this, &MainWindow::recv_image_from_task_thread);
		if (!thread_task_->isRunning())
			thread_task_->start();
	}
}

void MainWindow::on_action_stop_triggered()
{
	if (ui->action_stop->isChecked() == false) {
		ui->action_start->setEnabled(true);
		if (thread_task_->isRunning())
			thread_task_->stop();
		disconnect(thread_task_, &MThreadTask::send_image_to_main_window, this, &MainWindow::recv_image_from_task_thread);
		if (nullptr != thread_task_) {
			delete thread_task_;
			thread_task_ = nullptr;
		}
	}
}

void MainWindow::on_action_reset_triggered()
{
	
}

void MainWindow::HObjectToQImage(HalconCpp::HObject himage, QImage *qimage) {
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
}


