#ifndef COMMANDSET_CPP
#define COMMANDSET_CPP

#include <mainwindow.h>
#include <QPushButton>
#include <QMediaPlayer>
#include "command.cpp"
#include <QString>

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

class list_op : public Command
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
        list_op::getUI()->getList()->disconnect();
    }

    void execute(){
      QObject::connect(list_op::getUI()->getList() , &QListWidget::itemClicked, &(list_op::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(QListWidgetItem * item){
        QString filename = item->text();
        list_op::getUI()->setFile(filename);
        FileInfo::setFile(list_op::getUI()->getFile());
        for(int i = 0 ; i < list_op::getUI()->getList()->count();i++){
            if(list_op::getUI()->getMediaList()->media(i).canonicalUrl().fileName().compare(FileInfo::getName()) == 0){
                list_op::getUI()->getMediaList()->setCurrentIndex(i);
              }
          }
        list_op::getUI()->setStatus(true);
        emit list_op::getUI()->getMidle()->click();
    }
};

class p_to_s : public Command
{

public:
    explicit p_to_s(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~p_to_s(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        p_to_s::getUI()->getPlayer()->disconnect();
    }

    void execute(){
      QObject::connect(p_to_s::getUI()->getPlayer(), &QMediaPlayer::positionChanged, p_to_s::getUI()->getSlider() , &(p_to_s::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(qint64 info){
        p_to_s::getUI()->getSlider()->setValue(info);
    }
};

class s_to_p: public Command
{

public:
    explicit s_to_p (Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~s_to_p(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        s_to_p::getUI()->getSlider()->disconnect();
    }

    void execute(){
      QObject::connect(s_to_p::getUI()->getSlider(), &Slider::valueChanged , s_to_p::getUI()->getPlayer() , &(s_to_p::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(qint64 info){
        //s_to_p::getUI()->getSlider()->setValue(info);
        int min , sec , video;
        sec = info / 1000;
        min = sec / 60;
        sec = sec % 60;
        QString str_min = QString();
        str_min.setNum(min);
        if(min < 10) str_min = "0" + str_min;
        QString str_sec = QString();
        str_sec.setNum(sec);
        if(sec < 10) str_sec = "0" + str_sec;
        QString summary = str_min + ":" + str_sec;
        s_to_p::getUI()->getLabelLeft()->setText( summary );
        video = s_to_p::getUI()->getPlayer()->position();
        int value = s_to_p::getUI()->getSlider()->value()-(video);
        value = value > 0 ? value : -value;
        if(value > 1){
          s_to_p::getUI()->getPlayer()->setPosition(info);
        }
    }
};

class p_to_m : public Command
{

public:
    explicit p_to_m (Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~p_to_m(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        p_to_m::getUI()->getPlayer()->disconnect();
    }

    void execute(){
      QObject::connect(p_to_m::getUI()->getPlayer() , &QMediaPlayer::durationChanged , p_to_m::getUI() , &(p_to_m::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(qint64 info){
       p_to_m::getUI()->setSlider(info);
    }
};

class m_to_m : public Command
{

public:
    explicit m_to_m (Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~m_to_m(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        m_to_m::getUI()->disconnect();
    }

    void execute(){
      QObject::connect(m_to_m::getUI(), &MainWindow::destroyed, m_to_m::getUI() , &(m_to_m::exec));
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
    static void exec(){
       m_to_m::getUI()->save();
    }
};

class a_to_p: public Command
{
public:
    explicit a_to_p(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }

    virtual ~a_to_p(){
        if (receiver != NULL) {
        delete receiver;
        }
    }

    void undo(){
        a_to_p::getUI()->getPre()->disconnect();
    }

    void execute(){
      QObject::connect(a_to_p::getUI()->getPre(), &QAction::triggered, a_to_p::getUI()->getLeft() , &QPushButton::click);
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
};

class a_to_n: public Command
{
public:
    explicit a_to_n(Receiver * rece , MainWindow * _ui) : Command(rece){
        store::ui = _ui;
    }
    virtual ~a_to_n(){
        if (receiver != NULL) {
        delete receiver;
        }
    }
    void undo(){
        a_to_n::getUI()->getNext()->disconnect();
    }

    void execute(){
      QObject::connect(a_to_n::getUI()->getNext(), &QAction::triggered, a_to_n::getUI()->getRight() , &QPushButton::click);
    }

private:
    static MainWindow * getUI(){
        return store::ui;
    }
};

#endif
