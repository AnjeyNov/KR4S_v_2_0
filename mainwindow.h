#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dir.h>
#include <QScrollArea>
#include "copydir.h"
#include "copyfile.h"
#include "QErrorMessage"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *beginButton;
    QPushButton *backButton;
    QPushButton *pastButton;
    QHBoxLayout *mainLay;
    QVBoxLayout *leftLay;
    QScrollArea *scroll;
    QString *dirForCopy;
    QString *fileForCopy;
    QString *fileAP;
    Dir *root;
    Dir *currentDir;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setdir(Dir* dir);
    void back();
    void update(QString dir);
    void toRoot();
    void copyDir(QString dir);
    void copyFile(QString file, QString AP);
    void past();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
