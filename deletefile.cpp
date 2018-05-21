#include "deletefile.h"

DeleteFile::DeleteFile(QString name, QThread *parent) : QThread(parent)
{
    this->strname = name;
}
