#ifndef DIR_H
#define DIR_H
#include <QWidget>
#include <QString>
#include <QList>
#include <file.h>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "deletedir.h"
#include "deletefile.h"


class Dir : public QWidget
{
    Q_OBJECT
    QString *name;
    QString *absolutePath;
    QVBoxLayout *inLay;
    QHBoxLayout *outLay;
    QLabel *label;
    QPushButton *openButton;
    QPushButton *copyButton;
    QPushButton *deleteButton;
    Dir* prev;


public:
    QList<Dir*> *dirList;
    QList<File*> *fileList;


    explicit Dir(QWidget *parent = 0);
    explicit Dir(QString name, QString absolutePath ,Dir *prev,QWidget *parent = 0);

    QString getName() const;
    void setName(QString value);
    QString getAbsolutePath() const;
    void setAbsolutePath(QString value);
    void initIn();
    void destroyIN();
    QHBoxLayout *getOutLay() const;
    void setOutLay(QHBoxLayout *value);
    Dir *getPrev() const;

signals:
    void open(Dir*);
    void del(QString dir);
    void upDate(QString dir);
    void copy(QString dir);

public slots:
    void pressOpen();
    void pressDelete();
    void pressCopy();
    void goDelDir(QString dir);
    void goDelFile(QString file);
};

#endif // DIR_H
