#ifndef INVOKER_CPP
#define INVOKER_CPP

#include "Command.cpp"
#include <algorithm>
#include <vector>

using std::vector;

enum HISTORY { SET , UNDO , RUN , REDO } ;
struct record{
    HISTORY item;
    Command * command_1 = NULL;
    Command * command_2 = NULL;
};

class Invoker{

public :

    explicit Invoker(){};
    virtual ~Invoker(){};

    void setCommand(Command* command){
        vec.push_back(command);
        record atom;
        atom.item = SET;
        atom.command_1 = command;
        atom.command_2 = NULL;
        log(atom);
        point++;
    }

    void runCommand(){
        while(vec.size() != 0){
            vec[0] -> execute();
            vec.erase(vec.begin());
        }
        record atom;
        atom.item = RUN;
        atom.command_1 = NULL;
        atom.command_2 = NULL;
        log(atom);
        point++;
    }

    void undo(Command * command){
        for (int i = 0; i < vec.size(); i++){
            if(command == vec[i] && history[point - 1].item == UNDO){
                vec.erase(vec.begin() + i);
                point --;
                return;
            };
        }
        record atom;
        atom.item = UNDO;
        atom.command_1 = command;
        atom.command_2 = NULL;
        log(atom);
    }

    void redo(Command * pre , Command * now){
        vector<Command*>::iterator result = find( vec.begin(), vec.end(), pre);
        if(result != vec.end()){
            vec[distance(vec.begin() , result)] = now;
        }
        record atom;
        atom.item = REDO;
        atom.command_1 = pre;
        atom.command_2 = now;
        log(atom);
        point++;
    }

private:

    vector<Command*> vec;
    vector<record> history;

    void log(record item){
        history.push_back(item);
    }

    int point = 0;
};
#endif
