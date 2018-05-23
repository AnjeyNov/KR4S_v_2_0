#ifndef COPYFILE_H
#define COPYFILE_H
#include <QThread>
#include <QString>
#include <QDir>
#include <QFile>

class CopyFile: public QThread
{
    Q_OBJECT
    QString form;
    QString to;
public:
    CopyFile(QString f, QString t, QThread *parent = 0);
    void run() override{
        QFile::copy(QDir::toNativeSeparators(form), QDir::toNativeSeparators(to));
    }
};

#endif // COPYFILE_H
