#ifndef COMMANDSET_CPP
#define COMMANDSET_CPP

#include <mainwindow.h>
#include "mainwindow.cpp"
#include <QPushButton>
#include "command.cpp"

namespace store{
    //MainWindow * ui = NULL;
    int x;
}

class play : public Command
{

public:
    explicit play(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~play(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        play::getUI()->getMidle()->disconnect();
    }

    void execute(){
        QObject::connect(play::getUI()->getMidle(),&QPushButton::clicked,&(play::exec));

    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        if(play::getUI()->getStatus()){
            play::getUI()->setStatus(false);
            play::getUI()->getMidle()->setText("pause");
            play::getUI()->getPlayer()->play();
          }else{
            play::getUI()->setStatus(true);
            play::getUI()->getMidle()->setText("play");
            play::getUI()->getPlayer()->pause();
        }

    }
};

/*
class music_pre : public Command
{

public:
    explicit music_pre(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~music_pre(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        music_pre::getUI()->getLeft()->disconnect();
    }

    void execute(){
        QObject::connect(play::getUI()->getLeft(),music_pre::getUI()->getPlayer(),&(music_pre::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        music_pre::getUI()->getMediaList()->setCurrentIndex(music_pre::getUI()->getMediaList()->previousIndex());
        music_pre::getUI()->getUgetPlayer()->play();
    }
};


class music_next : public Command
{

public:
    explicit music_next(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~music_next(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        music_next::getUI()->getLeft()->disconnect();
    }

    void execute(){
        QObject::connect(play::getUI()->getLeft(),music_pre::getUI()->getPlayer(),&(music_pre::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        music_pre::getUI()->getMediaList()->setCurrentIndex(music_pre::getUI()->getMediaList()->previousIndex());
        music_pre::getUI()->getUgetPlayer()->play();
    }
};
*/
#endif
