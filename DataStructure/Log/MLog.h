#ifndef MLOG_H
#define MLOG_H

#include <QString>
#include <QTime>
#include <QObject>

class MLog : public QObject{
    Q_OBJECT
public:
    explicit MLog(QObject *parent = nullptr);
    ~MLog();

    MLog(const MLog &rhs) = delete;
    MLog& operator=(const MLog &rhs) = delete;
    MLog(MLog &&rhs) = delete;
    MLog&& operator=(MLog &&rhs) = delete;

    static MLog *Instance();
    void log_message(const QString& message, const QString &level);
signals:
    void send_log(QString timer, QString message, QString level);

private:
    static MLog *instance_;
};

#endif // MLOG_H
