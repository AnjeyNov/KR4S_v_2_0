#include "file.h"

QHBoxLayout *File::getOutLay() const
{
    return outLay;
}

void File::setOutLay(QHBoxLayout *value)
{
    outLay = value;
}

void File::pressDel()
{
    emit del(*absolutePath);
}

void File::pressCopy()
{
    emit copy(*name, *absolutePath);
}

File::File(QString name, QString absolutePath, QWidget *parent) : QWidget(parent)
{
    this->name = new QString(name);
    this->absolutePath = new QString(absolutePath);

    this->outLay = new QHBoxLayout();
    this->label = new QLabel(name);
    this->label->setMinimumWidth(150);
    this->outLay->addWidget(label);
    this->copyButton = new QPushButton("Copy");
    this->outLay->addWidget(copyButton);
    this->deleteButton = new QPushButton("Delete");
    this->outLay->addWidget(deleteButton);

    connect(deleteButton, SIGNAL(clicked(bool)), this, SLOT(pressDel()));
    connect(copyButton, SIGNAL(clicked(bool)), this, SLOT(pressCopy()));
}

