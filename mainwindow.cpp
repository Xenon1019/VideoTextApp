#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QApplication>
#include <QAction>
#include <QString>
#include <QUrl>
#include <QVideoWidget>
#include <QMediaPlayer>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    videoWidget = new QVideoWidget(ui->centralwidget);
    ui->videoSection->addWidget(videoWidget);
    mediaPlayer = new QMediaPlayer();
    mediaPlayer->setVideoOutput(videoWidget);


    connect(ui->menuFile, SIGNAL (triggered(QAction*)),
            this, SLOT (selectFileMenu(QAction*)));
    connect(this, SIGNAL (exitApp()), QApplication::instance(), SLOT (quit()));
    connect(this, SIGNAL (playFromStart()), this, SLOT (playVideo()));
    connect(this, SIGNAL (fileUpdated(QUrl)),
            mediaPlayer, SLOT (setSource(QUrl)));
    connect(this, SIGNAL (play()), mediaPlayer, SLOT (play()));
    connect(this, SIGNAL (pause()), mediaPlayer, SLOT (pause()));
    connect(this, SIGNAL (stop()), mediaPlayer, SLOT (stop()));
    connect(this, SIGNAL (setPosition(qint64)), mediaPlayer, SLOT (setPosition(qint64)));
    connect(this, SIGNAL (setVolume(int)), mediaPlayer, SLOT (setVolume(int)));
    connect(this, SIGNAL (setMuted(bool)), mediaPlayer, SLOT (setMuted(bool)));
}

void MainWindow::selectFileMenu(QAction *action) {
    if (action == ui->actionExit) {
        emit exitApp();
    } else if (action == ui->actionAdd_Media) {
        QString fileName = QFileDialog::getOpenFileName(
            this);
        emit fileUpdated(QUrl(fileName));
        emit playFromStart();
    }
}

void MainWindow::playVideo(qint64 pos) {
    emit setPosition(pos);
    emit play();
}

//void MainWindow::videoUpdated() {
//    emit playFromStart();
//}

MainWindow::~MainWindow()
{
    delete ui;
}

