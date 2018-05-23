#include "copyfile.h"

CopyFile::CopyFile(QString f, QString t, QThread *parent) : QThread(parent)
{
    form = f;
    to = t;
}

