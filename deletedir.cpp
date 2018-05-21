#include "deletedir.h"

DeleteDir::DeleteDir(QString dir, QThread *parent) : QThread(parent)
{
    strdir = dir;
}

int DeleteDir::removeFolder(QString dirname)
{
    QDir dir(dirname);
    int res = 0;
    //Получаем список каталогов
    QStringList lstDirs = dir.entryList(QDir::Dirs |
                                        QDir::AllDirs |
                                        QDir::NoDotAndDotDot);
    //Получаем список файлов
    QStringList lstFiles = dir.entryList(QDir::Files);

    //Удаляем файлы
    foreach (QString entry, lstFiles){
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        QFile::setPermissions(entryAbsPath, QFile::ReadOwner | QFile::WriteOwner);
        QFile::remove(entryAbsPath);
    }

    //Для папок делаем рекурсивный вызов
    foreach (QString entry, lstDirs){
        QString entryAbsPath = dir.absolutePath() + "/" + entry;
        removeFolder(entryAbsPath);
    }

    //Удаляем обрабатываемую папку
    if (!QDir().rmdir(dir.absolutePath())){
        res = 1;
    }
    return res;
}
