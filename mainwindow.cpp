#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumWidth(1080);
    this->setMinimumHeight(720);
    this->setWindowTitle("File manager");
    dirForCopy = new QString();
    dirForCopy = NULL;
    fileForCopy = new QString();
    fileForCopy = NULL;
    fileAP = new QString();
    fileAP = NULL;

    mainLay = new QHBoxLayout();
    scroll = new QScrollArea();
    this->centralWidget()->setLayout(mainLay);


    leftLay = new QVBoxLayout();
    beginButton = new QPushButton("To root");
    backButton = new QPushButton("Back");
    pastButton = new QPushButton("Paste");
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
        connect(root->dirList->at(i), SIGNAL(copy(QString)), this, SLOT(copyDir(QString)));
    }
    for(int i=0; i < root->fileList->size(); i++){
        connect(root->fileList->at(i), SIGNAL(copy(QString, QString)), this, SLOT(copyFile(QString, QString)));
    }
    connect(root, SIGNAL(upDate(QString)), this, SLOT(update(QString)));
    scroll->setMinimumWidth(500);
    scroll->setWidget(root);
    connect(backButton, SIGNAL(clicked(bool)), this, SLOT(back()));
    connect(beginButton, SIGNAL(clicked(bool)), this, SLOT(toRoot()));
    connect(pastButton, SIGNAL(clicked(bool)), this, SLOT(past()));
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
        connect(currentDir->dirList->at(i), SIGNAL(copy(QString)), this, SLOT(copyDir(QString)));
    }
    for(int i=0; i < currentDir->fileList->size(); i++){
        connect(currentDir->fileList->at(i), SIGNAL(copy(QString, QString)), this, SLOT(copyFile(QString, QString)));
    }
    connect(currentDir, SIGNAL(upDate(QString)), this, SLOT(update(QString)));
}

void MainWindow::back()
{
    if(currentDir->getAbsolutePath() == "/"){
        return;
    }
    if(currentDir->getPrev()->getAbsolutePath() == "/")
    {
        toRoot();
        return;
    }
    if(currentDir == root)
        return;
    currentDir->destroyIN();
    scroll->takeWidget();
    scroll->setWidget(currentDir->getPrev());
    currentDir = currentDir->getPrev();
    update(currentDir->getAbsolutePath());
}

void MainWindow::update(QString dir)
{
    scroll->takeWidget();
    currentDir->destroyIN();
    currentDir = currentDir->getPrev();
    currentDir->destroyIN();
    currentDir->initIn();
    for(int i = 0; i<currentDir->dirList->size(); i++){
        if(currentDir->dirList->at(i)->getAbsolutePath() == dir){
            currentDir = currentDir->dirList->at(i);
            currentDir->initIn();
            break;
        }
    }
    for(int i=0; i < currentDir->dirList->size(); i++){
        connect(currentDir->dirList->at(i), SIGNAL(open(Dir*)), this, SLOT(setdir(Dir*)));
    }
    connect(currentDir, SIGNAL(upDate(QString)), this, SLOT(update(QString)));
    scroll->setWidget(currentDir);
}

void MainWindow::toRoot()
{
    scroll->takeWidget();
    while (currentDir != NULL){
        currentDir->destroyIN();
        currentDir = currentDir->getPrev();
    }
    root = NULL;
    root = new Dir("", "/", NULL);
    currentDir = root;
    root->initIn();
    for(int i=0; i < root->dirList->size(); i++){
        connect(root->dirList->at(i), SIGNAL(open(Dir*)), this, SLOT(setdir(Dir*)));
    }
    connect(root, SIGNAL(upDate(QString)), this, SLOT(update(QString)));
    scroll->setWidget(root);
}

void MainWindow::copyDir(QString dir)
{
    fileForCopy = NULL;
    dirForCopy = new QString(dir);
}

void MainWindow::copyFile(QString file, QString AP)
{
    dirForCopy = NULL;
    fileForCopy = new QString(file);
    fileAP = new QString(AP);
}

void MainWindow::past()
{
    if(dirForCopy != NULL){
        if(currentDir->getAbsolutePath().contains("//home"))
        {
            CopyDir *thr;
            thr = new CopyDir(*dirForCopy, currentDir->getAbsolutePath());
            thr->run();
            thr->wait();
        } else
        {
            (new QErrorMessage(this))->showMessage("Copy in this fold impossible");
            return;
        }
    }
    if(fileForCopy != NULL){
        if(currentDir->getAbsolutePath().contains("//home"))
        {
            CopyFile *thr;
            thr = new CopyFile(*fileAP, currentDir->getAbsolutePath() + "/" + (*fileForCopy));
            thr->run();
            thr->wait();
        } else {
            (new QErrorMessage(this))->showMessage("Копирование в данную директорию невозможно");
            return;
        }
    }
    update(currentDir->getAbsolutePath());
}
