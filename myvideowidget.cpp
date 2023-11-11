#include "myvideowidget.h"
#include <iostream>

MyVideoWidget::MyVideoWidget(QWidget*)
{

}

void MyVideoWidget::mouseDoubleClickEvent(QMouseEvent* event) {
    if(event->button()==Qt::LeftButton) {
        if(isFullScreen()) {
            showNormal();
            std::cout<<"I work :)"<<std::endl;
        } else {
            showFullScreen();
        }
    }
}
