#ifndef FILE_H
#define FILE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>


class File : public QWidget
{
    Q_OBJECT
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

signals:
    void del(QString file);
    void copy(QString name, QString file);

public slots:
    void pressDel();
    void pressCopy();
};

#endif // FILE_H
