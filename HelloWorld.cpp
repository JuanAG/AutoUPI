#include <QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);

    qDebug() << QT_VERSION_STR << "The Qt libraries works";

    return 0;
}