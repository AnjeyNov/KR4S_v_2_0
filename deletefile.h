#ifndef DELETEFILE_H
#define DELETEFILE_H
#include <QThread>
#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>


class DeleteFile : public QThread
{
    Q_OBJECT
    QString strname;
public:
    DeleteFile(QString name, QThread *parent = 0);
    void run() override{
        QFile::setPermissions(strname, QFile::ReadOwner | QFile::WriteOwner);
        QFile::remove(strname);
    }
};

#endif // DELETEFILE_H
