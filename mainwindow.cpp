#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QLatin1String>
#include <iostream>
#include <QTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      player(new QMediaPlayer()),
      videoWidget(new MyVideoWidget()),
      timer(new QTimer())
{
    ui->setupUi(this);
    player->setVideoOutput(videoWidget);

    timer->setInterval(500);

    connect(player, &QMediaPlayer::stateChanged, this, &MainWindow::onStateChanged);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimeLabel);
    connect(ui->playButton, &QPushButton::clicked, this, &MainWindow::onPlayButtonClicked);
//    connect(ui->stopButton, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(ui->stopButton, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(ui->pauseButton, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(ui->openButton, &QPushButton::clicked, this, &MainWindow::on_openButton_clicked);

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::updateSlider);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::setRange);
    connect(ui->volumeSlider, &QSlider::valueChanged, this, &MainWindow::changeVolume);

    connect(ui->seekSlider, &QSlider::valueChanged, player, &QMediaPlayer::setPosition);
    initializeUI();
    qDebug() << "Current working directory:" << QDir::currentPath();
    bool styleSheetLoaded=loadStyleSheet();
}

void MainWindow::onStateChanged(QMediaPlayer::State newState) {
    if(newState==QMediaPlayer::StoppedState) {
        timer->stop();
        QTime time = QTime::fromMSecsSinceStartOfDay(0);
        ui->timeLabel->setText(time.toString("hh:mm:ss").append("/"+time.toString("hh:mm:ss")));
        qDebug()<<"Video stopped\n";
    }
}

void MainWindow::updateTimeLabel() {
    qint64 position=player->position();
    qint64 duration = player->duration();
    QTime time = QTime::fromMSecsSinceStartOfDay(position);
    QString finalTimeLabel="";
    finalTimeLabel.append(time.toString("hh:mm:ss"));
    time = QTime::fromMSecsSinceStartOfDay(duration);
    finalTimeLabel.append("/"+time.toString("hh:mm:ss"));
    ui->timeLabel->setText(finalTimeLabel);
}

void MainWindow::onPlayButtonClicked() {
    player->play();
    timer->start();

}

void MainWindow::setRange(qint64 duration) {
    ui->seekSlider->setRange(0, duration);

}

void MainWindow::updateSlider(qint64 position) {
    ui->seekSlider->setValue(position);
}
void MainWindow::on_openButton_clicked() {
    QString file = QFileDialog::getOpenFileName(this, "Open Video File");
    if (!file.isEmpty()) {
        player->setMedia(QUrl::fromLocalFile(file));
    }
}

MainWindow::~MainWindow()
{
    if(videoWidget)delete videoWidget;
    if(player)delete player;
    if(timer)delete timer;
    delete ui;
}

bool MainWindow::loadStyleSheet()
{
    QFile styleFile("../first_project/styles.qss");
    if(styleFile.open(QFile::ReadOnly)) {
        styleSheet=QLatin1String(styleFile.readAll());
        ui->playButton->setStyleSheet(styleSheet);
        ui->pauseButton->setStyleSheet(styleSheet);
        ui->stopButton->setStyleSheet(styleSheet);
        ui->centralwidget->setStyleSheet(styleSheet);
        ui->timeLabel->setStyleSheet(styleSheet);
        ui->seekSlider->setStyleSheet(styleSheet);
        ui->volumeSlider->setStyleSheet(styleSheet);

        ui->playButton->setObjectName("PlaybackButton");
        ui->pauseButton->setObjectName("PlaybackButton");
        ui->stopButton->setObjectName("PlaybackButton");
        ui->centralwidget->setObjectName("centralWidget");
        ui->timeLabel->setObjectName("TimeAndDuration");
        ui->seekSlider->setObjectName("seekSlider");
        ui->volumeSlider->setObjectName("volumeSlider");

        styleFile.close();
        return true;
    }
    return false;
}

void MainWindow::initializeUI()
{
    ui->seekSlider->setEnabled(true);
    ui->seekSlider->setMouseTracking(true);

    ui->seekSlider->setSingleStep(1000); // Step by 1 second
    ui->seekSlider->setPageStep(5000);   // Page step by 5 seconds

    ui->videoLayout->addWidget(videoWidget);

}

void MainWindow::changeVolume(const int& volume) {
    player->setVolume(volume);
}

void MainWindow::onStop() {
    ui->seekSlider->setValue(0);
    player->stop();
}
