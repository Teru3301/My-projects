#include "mydrawboard.h"
#include "neuralNetwork.h"

myDrawBoard::myDrawBoard(QProgressBar *prBar, QWidget *parent) : QWidget(parent)
{
    this->setMinimumSize(393, 393);
    pBar = prBar;

    std::string path = _pgmptr;
    while (path[path.length()-1] != '\\') path.replace(path.length()-1, 1, "");
    path += "weights.txt";
    while (path.find("\\") != std::string::npos) path.replace(path.find("\\"), 1, "/");

    std::fstream file_weights;
    file_weights.open(path);

    weights1 = new double*[200];
    weights2 = new double*[100];
    weights3 = new double*[10];

    for (int neuron = 0; neuron < 200; neuron++)
    {
        weights1[neuron] = new double[784];
        for (int connect = 0; connect < 784; connect++)
        {
            file_weights >> weights1[neuron][connect];
        }
    }
    for (int neuron = 0; neuron < 100; neuron++)
    {
        weights2[neuron] = new double[200];
        for (int connect = 0; connect < 200; connect++)
        {
            file_weights >> weights2[neuron][connect];
        }
    }
    for (int neuron = 0; neuron < 10; neuron++)
    {
        weights3[neuron] = new double[100];
        for (int connect = 0; connect < 100; connect++)
        {
            file_weights >> weights3[neuron][connect];
        }
    }
    bias = new double[3];
    file_weights >> bias[0] >> bias[1] >> bias[3];

    file_weights.close();

    QThread::sleep (1);

    pixels = new bool*[28];
    for (int hor = 0; hor < 28; ++hor)
    {
        pixels[hor] = new bool[28];
        for (int ver = 0; ver < 28; ++ver)
        {
            pixels[hor][ver] = false;
        }
    }
}

void myDrawBoard::paintEvent(QPaintEvent *)
{
    QPainter *painter = new QPainter(this);
    painter->setPen(qRgb(60, 60, 60));
    painter->setBrush(QBrush(qRgb(50, 50, 50)));
    painter->drawRect(0, 0, 393, 393);
    painter->setBrush(QBrush(qRgb(255, 255, 255)));

    //отрисовка пикселей
    for (int i =  0; i < 28; ++i)
    {
        for (int j = 0; j < 28; ++j)
        {
            if (pixels[i][j]) painter->drawRect(i*14, j*14, 14, 14);
        }
    }
    //горизонтальные линии
    for (int hor = 0; hor < 29; ++hor) painter->drawLine(0, hor*14, 392, hor*14);
    //вертикальные линии
    for (int ver = 0; ver < 29; ++ver) painter->drawLine(ver*14, 0, ver*14, 392);


    painter->setPen(qRgb(0, 0, 0));
    painter->drawLine(0, 56, 393, 56);
    painter->drawLine(0, 337, 393, 337);
    painter->drawLine(56, 0, 56, 393);
    painter->drawLine(337, 0, 337, 393);
}

void myDrawBoard::mousePressEvent(QMouseEvent *event)
{
    draworerese = false;
    if (event->button()==Qt::LeftButton) draworerese = true;
    if (event->button()==Qt::RightButton)
    {
        for (int hor = 0; hor < 28; ++hor)
        {
            pixels[hor] = new bool[28];
            for (int ver = 0; ver < 28; ++ver)
            {
                pixels[hor][ver] = false;
            }
        }
        repaint();
    }
}

void myDrawBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (event->x() >= 0 && event->x()/14 <= 27 && event->y() >= 0 && event->y()/14 <= 27)
    {
        int x = event->x() / 14;
        int y = event->y() / 14;

        pixels[x][y] = draworerese;
        if (x-1 >= 0) pixels[x-1][y] = draworerese;
        if (y-1 >= 0) pixels[x][y-1] = draworerese;
        if (x-1 >= 0 && y-1 >= 0) pixels[x-1][y-1] = draworerese;
        calcs(pixels, pBar, weights1, weights2, weights3, bias);
    }
    repaint();
}
