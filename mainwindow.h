#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <dir.h>
#include <QScrollArea>

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
    Dir *root;
    Dir *currentDir;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void setdir(Dir* dir);
    void back();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
