#include "speedmenu.h"
#include <QList>

SpeedMenu::SpeedMenu(QWidget* parent):QMenu("speed",parent)
{
    speed05=new QAction("0.5x",this);
    speed1 =new QAction("1x",this);
    speed15=new QAction("1.5x",this);
    speed2 =new QAction("2x",this);

    this->addActions(QList<QAction*>{speed05, speed1, speed15, speed2});

    connect(speed05, &QAction::triggered, this, &SpeedMenu::speedChanged05);
    connect(speed1, &QAction::triggered, this, &SpeedMenu::speedChanged1);
    connect(speed15, &QAction::triggered, this, &SpeedMenu::speedChanged15);
    connect(speed2, &QAction::triggered, this, &SpeedMenu::speedChanged2);

}

void SpeedMenu::speedChanged05() {
    emit speedChanged(0.5);
}
void SpeedMenu::speedChanged1() {
    emit speedChanged(1);
}
void SpeedMenu::speedChanged15() {
    emit speedChanged(1.5);
}
void SpeedMenu::speedChanged2() {
    emit speedChanged(2);
}


SpeedMenu::~SpeedMenu() {
    if(speed05) delete speed05;
    if(speed1) delete speed1;
    if(speed15) delete speed15;
    if(speed2) delete speed2;
}
