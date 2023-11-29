#include "mainwindow.h"
#include "mydrawboard.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    progress = new int[10];
    for (int i = 0; i < 10; ++i) progress[i] = 10;


    const int amount = 10;

    QWidget *centralWidget = new QWidget;
    QGridLayout *gridAll = new QGridLayout;
    QProgressBar *progressBar = new QProgressBar[amount];
    QLabel *nums[amount];
    QHBoxLayout *elements[amount];
    QGridLayout *groupElements = new QGridLayout;

    setCentralWidget(centralWidget);
    centralWidget->setLayout(gridAll);

    for(int i = 0; i < amount; ++i)
    {
        //цифры
        nums[i] = new QLabel("  " + QString::number(i) + " ");
        //прогрес бары
        //progressBar[i] = new QProgressBar;
        progressBar[i].setRange(0, 100);
        progressBar[i].setValue(progress[i]);
        //группы цифры + бары
        elements[i] = new QHBoxLayout;
        elements[i]->addWidget(nums[i]);
        elements[i]->addWidget(&progressBar[i]);
        groupElements->addLayout(elements[i], i, 0);
    }

    myDrawBoard *board = new myDrawBoard(progressBar);

    gridAll->addWidget(board, 0, 0);
    gridAll->addLayout(groupElements, 0, 1);

    //применение css стилей
    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    centralWidget->setStyleSheet(file.readAll());
}

MainWindow::~MainWindow()
{
}
