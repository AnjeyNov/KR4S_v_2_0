#include "dir.h"

QString Dir::getName() const
{
    return *name;
}

void Dir::setName(QString value)
{
    *name = value;
}

QString Dir::getAbsolutePath() const
{
    return *absolutePath;
}

void Dir::setAbsolutePath(QString value)
{
    *absolutePath = value;
}

void Dir::initIn()
{
    QDir dir(*absolutePath);
    QStringList dirSL(dir.entryList(QDir::Dirs));
    dirList = new QList<Dir*>;
    for(int i=2; i<dirSL.size(); i++){
        Dir *tmp = new Dir(dirSL.at(i), *absolutePath +"/" + dirSL.at(i), this);
        inLay->addLayout(tmp->getOutLay());
        dirList->append(tmp);
        connect(tmp, SIGNAL(del(QString)), this, SLOT(goDel(QString)));
    }
    QStringList fileSL(dir.entryList(QDir::Files));
    fileList = new QList<File*>;
    for(int i=0; i<fileSL.size(); i++){
        File *tmp = new File(fileSL.at(i), *absolutePath +"/" + fileSL.at(i));
        inLay->addLayout(tmp->getOutLay());
        fileList->append(tmp);
    }
}

void Dir::destroyIN()
{
    for (int i = 0; i < inLay->count();){
        QLayoutItem *item = inLay->itemAt(i);
        if (item->layout() != NULL)
            delete inLay->takeAt(i);
        else i++;
    }
    while(!dirList->empty()){
        dirList->pop_back();
    }
    while (!fileList->empty()){
        fileList->pop_back();
    }
}

QHBoxLayout *Dir::getOutLay() const
{
    return outLay;
}

void Dir::setOutLay(QHBoxLayout *value)
{
    outLay = value;
}

Dir *Dir::getPrev() const
{
    return prev;
}

Dir::Dir(QWidget *parent) : QWidget(parent)
{

}

Dir::Dir(QString name, QString absolutePath, Dir *prev, QWidget *parent) : QWidget(parent)
{
    this->name = new QString(name);
    this->absolutePath = new QString(absolutePath);
    this->prev = new Dir();
    this->prev = prev;

    this->outLay = new QHBoxLayout();
    this->label = new QLabel(name);
    this->label->setMinimumWidth(150);
    this->outLay->addWidget(label);
    this->openButton = new QPushButton("Open");
    this->outLay->addWidget(openButton);
    this->copyButton = new QPushButton("Copy");
    this->outLay->addWidget(copyButton);
    this->deleteButton = new QPushButton("Delete");
    this->outLay->addWidget(deleteButton);

    inLay = new QVBoxLayout();
    this->setLayout(inLay);

    connect(openButton, SIGNAL(clicked(bool)), this, SLOT(pressOpen()));
    connect(deleteButton,SIGNAL(clicked(bool)), this, SLOT(pressDelete()));

}

void Dir::pressOpen()
{
    initIn();
    emit open(this);
}

void Dir::pressDelete()
{
    emit del(this->getAbsolutePath());
}

void Dir::goDel(QString dir)
{
    DeleteDir *del = new DeleteDir(dir);
    del->run();
    del->wait();
    this->destroyIN();
    this->initIn();

}
