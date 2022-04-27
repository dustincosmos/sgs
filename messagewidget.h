#ifndef MESSAGEWIDGET_H
#define MESSAGEWIDGET_H

#include <QWidget>
#include <QTextEdit>
class messageWidget : public QTextEdit
{
    Q_OBJECT
public:
    explicit messageWidget(QWidget *parent = nullptr);
    void MOUT(std::string s);

signals:

};

#endif // MESSAGEWIDGET_H
