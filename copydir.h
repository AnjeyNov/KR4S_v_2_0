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
    QString form;
    QString to;
public:
    CopyDir(QString f, QString t, QThread *parent = 0);
    int copyDirectory(const QString &aFromPath, const QString &aToPath);
    void run() override{
        copyDirectory(form,to);
    }
    int getFilesDirsLists(const QString &aRootDir, QStringList &aDirectories, QStringList &aFiles, bool aStripRoot);
};

#endif // COPYDIR_H
