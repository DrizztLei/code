#ifndef RECEIVER_CPP
#define RECEIVER_CPP

#include "command.cpp"
#include <QDebug>
#include <QPushButton>
#include <QMediaPlayer>
#include <QListWidget>
#include "mainwindow.h"

class MainWindow;
class play;

class Receiver{
public:
    explicit Receiver(){}

    void play_music(QPushButton * button , void(*function)(bool)){
        QObject::connect(button , &QPushButton::clicked , function);
    }

    void play_pre(QPushButton * left , QMediaPlayer * player ,void(*function)(bool)){
        QObject::connect(left , &QPushButton::clicked , player , function);
    }

    void play_next(QPushButton * right , QMediaPlayer * player ,void(*function)(bool)){
        QObject::connect(right, &QPushButton::clicked , player , function);
    }

    void open(QAction* action , void(QAction::*triggered)(bool) , void(*funtion)(bool)){
        QObject::connect(action , triggered , funtion);
    }

    void list(QListWidget * list , void(QListWidget::*clicked)(QListWidgetItem* ) ,void(*function)(QListWidgetItem *)){
        QObject::connect(list , clicked , function);
    }

    void player_to_slider(QMediaPlayer * player ,void(QMediaPlayer::*changed)(qint64) , QSlider * slider , void(*ref)(qint64)){
        QObject::connect(player , changed , slider , ref);
    }

    void slider_to_player(QSlider * slider , void(QSlider::*changed)(int), QMediaPlayer* player , void(*ref)(qint64)){
        QObject::connect(slider , changed , player , ref);
    }

    void player_to_main(QMediaPlayer * player , void(QMediaPlayer::*changed)(qint64) , QMainWindow * window , void(*function)(qint64)){
        QObject::connect(player , changed , window , function);
    }

    void main_to_save(QMainWindow * windows , void(QObject::*destory)(QObject*), QMainWindow * ui , void(*save)()){
        QObject::connect(windows , destory , ui , save);
    }

    void action_to_pre(QAction* pre ,void(QAction::*triggered)(bool) , QPushButton * button , void(QPushButton::*clicked)()){
        QObject::connect(pre , triggered , button , clicked);
    }

    void action_to_next(QAction* next ,void(QAction::*triggered)(bool) , QPushButton * button , void(QPushButton::*clicked)()){
        QObject::connect(next, triggered , button , clicked);
    }

    void action_to_exit(QAction* exit ,void(QAction::*triggered)(bool), QMainWindow * window , bool(QWidget::*close)()){
        QObject::connect(exit , triggered , window , close);
    }

};
#endif
