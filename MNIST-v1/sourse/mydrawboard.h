#ifndef MYDRAWBOARD_H
#define MYDRAWBOARD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QProgressBar>
#include <fstream>
#include <QThread>
#include <windows.h>
#include <string>

class myDrawBoard : public QWidget
{
    Q_OBJECT
public:
    explicit myDrawBoard(QProgressBar *prBar, QWidget *parent = nullptr);
private:
    bool **pixels;
    bool draworerese;
    QProgressBar *pBar;
    double **weights1;
    double **weights2;
    double **weights3;
    double *bias;

    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
};

#endif // MYDRAWBOARD_H
