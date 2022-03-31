#include "CommunicationWidget.h"
#include "ui_communicationwidget.h"

CommunicationWidget::CommunicationWidget(QWidget *parent) :
    QWidget(parent),
    communication_index_(-1),
    ui(new Ui::CommunicationWidget)
{
    ui->setupUi(this);
	init();
}

void CommunicationWidget::init() {
	communication_index_ = 0;
	connect(MSysInfo::Instance()->vec_communication_[communication_index_], &MCommunicationBase::sendMsg, [=](const QString &msg) {
		ui->plainTextEditRecvMsg->appendPlainText(msg);
	});

	timer_led_ = new QTimer(this);
	connect(timer_led_, &QTimer::timeout, this, [=]() {
		bool status = MSysInfo::Instance()->vec_communication_[communication_index_]->isOpen();
		if (status == true)
			set_led(ui->labelLed, 2, 16);
		else
			set_led(ui->labelLed, 1, 16);
	});
	timer_led_->start(200);
}

CommunicationWidget::~CommunicationWidget()
{
	if (timer_led_->isActive() == true)
		timer_led_->stop();
	if (nullptr != timer_led_) {
		delete timer_led_;
		timer_led_ = nullptr;
	}
    delete ui;
}

void CommunicationWidget::stop_communication_timer(const bool &status) {
	if (status == true) {
		if (timer_led_->isActive() == true)
			timer_led_->stop();
	}
	else {
		if (timer_led_->isActive() == false)
			timer_led_->start(200);
	}
}

void CommunicationWidget::on_btnSend_clicked()
{
    QString send_data = ui->plainTextEditSendMsg->toPlainText();
    MSysInfo::Instance()->vec_communication_[communication_index_]->sendData(send_data);
}

void CommunicationWidget::set_led(QLabel* label, int color, int size){
    label->setText("");
    QString min_width = QString("min-width: %1px;").arg(size);              
    QString min_height = QString("min-height: %1px;").arg(size);            
    QString max_width = QString("max-width: %1px;").arg(size);              
    QString max_height = QString("max-height: %1px;").arg(size);                                                                             
    QString border_radius = QString("border-radius: %1px;").arg(size / 2);    
    QString border = QString("border:1px solid black;");                                                                                         
    QString background = "background-color:";
    switch (color) {
        case 0:
        // gray
        background += "rgb(190,190,190)";
        break;
        case 1:
        //red
        background += "rgb(255,0,0)";
        break;
        case 2:
        //green
        background += "rgb(0,255,0)";
        break;
        case 3:
        //yellow
        background += "rgb(255,255,0)";
        break;
        default:
        break;
    }

    const QString SheetStyle = min_width + min_height + max_width + max_height + border_radius + border + background;
    label->setStyleSheet(SheetStyle);
}
