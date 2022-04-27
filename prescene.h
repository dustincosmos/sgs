#ifndef PRESCENE_H
#define PRESCENE_H

#include <QMainWindow>
#include<QPushButton>
class PreScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit PreScene(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* ev);
private:

    QPushButton *startbtn;
    QPushButton *setbtn;



signals:

};

#endif // PRESCENE_H
