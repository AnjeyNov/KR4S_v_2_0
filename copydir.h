#ifndef COPYDIR_H
#define COPYDIR_H
#include <QThread>
#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>

class CopyDir : public QThread
{
    Q_OBJECT
public:
    CopyDir();
};

#endif // COPYDIR_H
