#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
};

#endif // WIDGET_H
