#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumWidth(1080);
    this->setMinimumHeight(720);


    mainLay = new QHBoxLayout();
    scroll = new QScrollArea();
    this->centralWidget()->setLayout(mainLay);

    leftLay = new QVBoxLayout();
    beginButton = new QPushButton("To root");
    backButton = new QPushButton("Back");
    pastButton = new QPushButton("Past");
    leftLay->addWidget(beginButton);
    leftLay->addWidget(backButton);
    leftLay->addWidget(pastButton);

    mainLay->addLayout(leftLay);
    mainLay->addWidget(scroll);
    root = new Dir(0,"/", NULL);
    root->initIn();
    currentDir = new Dir();
    currentDir = root;
    for(int i=0; i < root->dirList->size(); i++){
        connect(root->dirList->at(i), SIGNAL(open(Dir*)), this, SLOT(setdir(Dir*)));
    }
    scroll->setMinimumWidth(500);
    scroll->setWidget(root);
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(back()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setdir(Dir *dir)
{
    scroll->takeWidget();
    scroll->setWidget(dir);
    currentDir = dir;
    for(int i=0; i < currentDir->dirList->size(); i++){
        connect(currentDir->dirList->at(i), SIGNAL(open(Dir*)), this, SLOT(setdir(Dir*)));
    }
}

void MainWindow::back()
{
    if(currentDir == root)
        return;
    currentDir->destroyIN();
    scroll->takeWidget();
    scroll->setWidget(currentDir->getPrev());
    currentDir = currentDir->getPrev();
}