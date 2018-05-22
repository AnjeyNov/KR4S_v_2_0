#include "copydir.h"

CopyDir::CopyDir(QString f, QString t, QThread *parent)
{
    form = f;
    to = t;
}

int CopyDir::getFilesDirsLists(const QString &aRootDir, QStringList &aDirectories,
                                QStringList &aFiles, bool aStripRoot) {
    QDir vDir(aRootDir);

    QString vPath = aRootDir;
    int vLevel = 0;

    QList<QStringList> vDirs;
    QList<int> vIndex;
    QList<QString> vPaths;

    aDirectories.append("");

    vDirs.append(aDirectories);
    aDirectories.clear();
    vIndex.append(0);
    vPaths.append(vPath);

    while (vLevel > -1) {
    int i; bool vUp = false;
    for (i=vIndex.at(vLevel); i < vDirs.at(vLevel).size(); i++) {
        vPath = vPaths.at(vLevel)+vDirs.at(vLevel).at(i)+QLatin1String("/");
        aDirectories.append(vPath);
        // get files
        QDir vLocDir(vPath);
        QStringList vLocFiles = vLocDir.entryList(QDir::Files);
        for (int j=0; j < vLocFiles.size();j++)
            aFiles.append(vPath+vLocFiles.at(j));
        //

        QStringList vNewList = vLocDir.entryList(QDir::AllDirs | QDir::Hidden | QDir::NoDotAndDotDot);
        if (vNewList.size() > 0) {
            vIndex[vLevel] = i+1;
            vLevel++;
            if (vLevel >= vDirs.size()) {
                vDirs.append(vNewList);
                vPaths.append(vPath);
                vIndex.append(0);
            } else {
                vDirs[vLevel] = vNewList;
                vPaths[vLevel] = vPath;
                vIndex[vLevel] = 0;
            }
            vUp = true;
            break;
            }
        }
        if (vUp) continue;
        if (i >= vDirs.at(vLevel).size()) vLevel--;
    }

    aDirectories.removeFirst();

    if (aStripRoot) {
        for (int i=0; i < aDirectories.size();i++)
            aDirectories[i].replace(QDir::toNativeSeparators(QString("%1/").arg(aRootDir)), QLatin1String(""));

        for (int i=0; i < aFiles.size();i++)
            aFiles[i].replace(QDir::toNativeSeparators(QString("%1/").arg(aRootDir)), QLatin1String(""));
    }

    return 0;
}

int CopyDir::copyDirectory(const QString &aFromPath, const QString &aToPath) {
    QStringList vFiles;
    QStringList vDirs;

    QFileInfo vFileFrom(aFromPath);
    QFileInfo vFileTo(aToPath);

    if (!vFileFrom.isDir() || (!vFileTo.isDir())) {
        // error!
        //Can't copy '%1' to '%2'. Some of these paths isn't a directory
        return 1;
    }

    QString vFromPath = QDir::toNativeSeparators(aFromPath);
    QString vToPath = QDir::toNativeSeparators(aToPath);

    getFilesDirsLists(vFromPath, vDirs, vFiles, true);

    if (vToPath.right(1).compare(QDir::toNativeSeparators(QLatin1String("/"))) != 0) {
        vToPath += QDir::toNativeSeparators(QLatin1String("/"));
    }

    if (vFromPath.right(1).compare(QDir::toNativeSeparators(QLatin1String("/"))) == 0) {
        vFromPath.resize(vFromPath.size() - 1);
    }

    QString vTopDir = vFromPath.section(QDir::toNativeSeparators(QLatin1String("/")), -1);
    vFromPath += QDir::toNativeSeparators(QLatin1String("/"));

    QDir vDir(vToPath);

        if (!vDir.mkdir(vTopDir)) {
            //Can't create directory '%1'
            return 1;
        }

        vToPath += vTopDir + QDir::toNativeSeparators(QLatin1String("/"));
        if (!vDir.cd(vTopDir)) {
            //Can't change directory to '%1'
            return 1;
        }


    for (int i=0; i < vDirs.size(); i++) {
        if (!vDir.mkpath(vDirs.at(i))) {
            //Can't create directory '%1'
            return 1;
        }
    }

    for (int i=0; i < vFiles.size(); i++) {
        if (!QFile::copy(QDir::toNativeSeparators(vFromPath+vFiles.at(i)),
            QDir::toNativeSeparators(vToPath+vFiles.at(i)))) {
            //Can't copy file.\n source path:'%1'\n destination path '%2'


            return 1;
        }
    }

    return 0;
}


