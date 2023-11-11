#ifndef MYVIDEOWIDGET_H
#define MYVIDEOWIDGET_H
#include <QVideoWidget>
#include <QMouseEvent>


class MyVideoWidget: public QVideoWidget
{
public:
    MyVideoWidget(QWidget* parent=nullptr);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent* event);
};

#endif // MYVIDEOWIDGET_H
