#include "Dialog/MainWindow.h"
#include "DataStructure/Configuration/MSysInfo.h"
#include <QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSplashScreen *splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Icon/recognition.png"));
    splash->show();

    Qt::Alignment topRight = Qt::AlignRight | Qt::AlignTop;
    splash->showMessage(QObject::tr("Setting up the main window..."), topRight, Qt::white);

    splash->showMessage(QObject::tr("Loading data..."), topRight, Qt::white);
    MSysInfo::Instance()->init();

    splash->showMessage(QObject::tr("Connecting device..."), topRight, Qt::white);
    MSysInfo::Instance()->open();

    MainWindow w;
    w.show();

    splash->finish(&w);
    delete splash;

    return a.exec();
}
