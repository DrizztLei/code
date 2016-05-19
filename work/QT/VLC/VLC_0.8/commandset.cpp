#ifndef COMMANDSET_CPP
#define COMMANDSET_CPP

#include <mainwindow.h>
#include <QPushButton>
#include "command.cpp"
#include <stdio.h>
namespace store{
    static MainWindow * ui = NULL;
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
        QObject::connect(music_pre::getUI()->getLeft(),&QPushButton::clicked,music_pre::getUI()->getPlayer(),&(music_pre::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        music_pre::getUI()->getMediaList()->setCurrentIndex(music_pre::getUI()->getMediaList()->previousIndex());
        music_pre::getUI()->getPlayer()->play();
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
        music_next::getUI()->getRight()->disconnect();
    }

    void execute(){
        QObject::connect(music_next::getUI()->getRight(),&QPushButton::clicked,music_next::getUI()->getPlayer(),&(music_next::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        music_next::getUI()->getMediaList()->setCurrentIndex(music_next::getUI()->getMediaList()->nextIndex());
        music_next::getUI()->getPlayer()->play();
    }
};

class file_open : public Command
{

public:
    explicit file_open(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~file_open(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        file_open::getUI()->getOpen()->disconnect();
    }

    void execute(){
      QObject::connect(file_open::getUI()->getOpen() , &QAction::triggered, &(file_open::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        file_open::getUI()->openFile();
    }
};


class list_op: public Command
{

public:
    explicit list_op(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~list_op(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        ::getUI()->getOpen()->disconnect();
    }

    void execute(){
      QObject::connect(list_op::getUI()->getOpen() , &QAction::triggered, &(list_op::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(bool flag = false){
        list_op::getUI()->openFile();
    }
};



#endif
