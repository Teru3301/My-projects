#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow mWindow;
    mWindow.setFixedWidth(600);
    mWindow.setFixedHeight(420);
    mWindow.show();

    return app.exec();
}
