#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QVideoWidget>
#include <QMediaPlayer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void selectFileMenu(QAction *action);
    void playVideo(qint64 pos = 0);
signals:
    void exitApp();
    void playFromStart();
    void pickFile();
    void fileUpdated(QUrl);
    void setPositionToStart();
    void setPosition(qint64);
    void setVolume(int);
    void setMuted(bool);
    void play();
    void pause();
    void stop();

private:
    Ui::MainWindow *ui;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;

    //void videoUpdated();
};
#endif // MAINWINDOW_H
