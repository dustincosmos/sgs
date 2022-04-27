#ifndef ENDSCENE_H
#define ENDSCENE_H

#include <QWidget>

class endScene : public QWidget
{
    Q_OBJECT
public:
    explicit endScene(QWidget *parent = nullptr);
    void setWinner(bool f);
private:
    bool flag=1;
protected:
    void paintEvent(QPaintEvent* ev);
signals:

};

#endif // ENDSCENE_H
