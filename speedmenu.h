#ifndef SPEEDMENU_H
#define SPEEDMENU_H

#include <QMenu>

class SpeedMenu : public QMenu
{
    Q_OBJECT
public:
    SpeedMenu(QWidget* parent=nullptr);
    ~SpeedMenu();
signals:
    void speedChanged(const double& speed);
private:
    QAction* speed05;
    QAction* speed1;
    QAction* speed15;
    QAction* speed2;

private slots:
    void speedChanged05();
    void speedChanged1();
    void speedChanged15();
    void speedChanged2();
};

#endif // SPEEDMENU_H
