#ifndef DELETEDIR_H
#define DELETEDIR_H
#include <QThread>
#include <QString>
#include <QDir>
#include <QFile>
#include <QStringList>

class DeleteDir : public QThread
{
    Q_OBJECT
    QString strdir;
public:
    explicit DeleteDir(QString dir, QThread *parent = 0);
    int removeFolder(QString dir);
    void run() override{
        removeFolder(strdir);
    }
};

#endif // DELETEDIR_H
