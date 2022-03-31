#ifndef COMMUNICATIONWIDGET_H
#define COMMUNICATIONWIDGET_H

#include <QWidget>
#include <QString>
#include <QTimer>
#include <QLabel>
#include "DataStructure/Configuration/MSysInfo.h"

namespace Ui {
class CommunicationWidget;
}

class CommunicationWidget : public QWidget{
    Q_OBJECT
public:
    explicit CommunicationWidget(QWidget *parent = nullptr);
    ~CommunicationWidget();
	void init();
	void stop_communication_timer(const bool &status);
private slots:
    void on_btnSend_clicked();
private:
    Ui::CommunicationWidget *ui;
    int communication_index_;
    QTimer *timer_led_;
	void set_led(QLabel* label, int color, int size);

};

#endif // COMMUNICATIONWIDGET_H
