#include "messagewidget.h"

messageWidget::messageWidget(QWidget *parent) : QTextEdit(parent)
{
    this->setFixedSize(200,200);
}


void messageWidget::MOUT(std::string s)
{
    QString cs = QString::fromStdString(s);
    this->insertPlainText(cs);
    this->insertPlainText("\n");
}
