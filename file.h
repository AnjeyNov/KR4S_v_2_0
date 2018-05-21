#ifndef FILE_H
#define FILE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>


class File : public QWidget
{
    QString *name;
    QString *absolutePath;
    QHBoxLayout *outLay;
    QLabel *label;
    QPushButton *copyButton;
    QPushButton *deleteButton;
public:
    explicit File(QString name, QString absolutePath ,QWidget *parent=0);
    QHBoxLayout *getOutLay() const;
    void setOutLay(QHBoxLayout *value);
};

#endif // FILE_H
