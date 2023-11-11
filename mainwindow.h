#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include "myvideowidget.h"
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMediaPlayer* player;
    MyVideoWidget* videoWidget;
    QString styleSheet;
    QTimer* timer;

    bool loadStyleSheet();
    void initializeUI();

private slots:
    void onStateChanged(QMediaPlayer::State newState);
    void updateTimeLabel();
    void onPlayButtonClicked();
    void changeVolume(const int& volume);
    void updateSlider(qint64 position);
    void on_openButton_clicked();
    void setRange(qint64 duration);
    void onStop();

};
#endif // MAINWINDOW_H
