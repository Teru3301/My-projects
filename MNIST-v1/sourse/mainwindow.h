#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QVector>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QProgressBar>
#include <QFile>
#include <QWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    int *progress;
    //QProgressBar *progressBar;

    //void paintEvent(QPaintEvent *event);
};
#endif // MAINWINDOW_H
