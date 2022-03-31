#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "DataStructure/Configuration/MSysInfo.h"

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public QWidget{
    Q_OBJECT
public:
    explicit SettingsWidget(QWidget *parent = nullptr);
    ~SettingsWidget();
    void init();
	void show_tcp_control(const bool &status);
	void show_serial_port_control(const bool &status);
private slots:
    void on_comboCameraType_currentIndexChanged(const QString &arg1);
    void on_comboCameraCount_currentIndexChanged(const QString &arg1);
    void on_comboCommunicationType_currentIndexChanged(const QString &arg1);
    void on_comboCommunicationCount_currentIndexChanged(const QString &arg1);
	void on_lineEditIP_textChanged(const QString &arg1);
	void on_lineEditPort_textChanged(const QString &arg1);
    void on_comboSerialPortNumber_currentIndexChanged(const QString &arg1);
    void on_comboBaudRate_currentIndexChanged(const QString &arg1);
    void on_comboParityBit_currentIndexChanged(const QString &arg1);
    void on_comboDataBit_currentIndexChanged(const QString &arg1);
    void on_comboStopBit_currentIndexChanged(const QString &arg1);

private:
    Ui::SettingsWidget *ui;
};

#endif // SETTINGSWIDGET_H
