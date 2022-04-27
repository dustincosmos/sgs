#ifndef COUNTDOWN_H
#define COUNTDOWN_H

#include <QWidget>
#include <QTimer>
class CountDown : public QWidget
{
    Q_OBJECT
public:
    explicit CountDown(QWidget *parent = nullptr);
    void showCountDown();
    void npcCountdown();
private:
    QTimer *c_timer;
    int count;

    QPixmap c_1;
    QPixmap c_2;
    QPixmap c_3;
    QPixmap c_4;
    QPixmap c_5;

    QPixmap c_time;

protected:
    void paintEvent(QPaintEvent* ev);
signals:
    void timeout();
};

#endif // COUNTDOWN_H
