#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include<QJsonObject>
#include<QDebug>
#define CODE_ERROR -1
#define ACCOUNT_ERROR -2
#define USER 1
using namespace std;

class Instruction
{
private:
    QString Command;
    QString Message;
    QJsonObject Data;
public:
    Instruction() {}
    Instruction(QJsonObject jsonObj);
    int CommandType(){
        if(this->Command=="USER")
        {
            return USER;
        }
        else if(this->Command == "CODE_ERROR")
        {
            return CODE_ERROR;
        }
        else if(this->Command == "ACCOUNT_ERROR")
        {
            return ACCOUNT_ERROR;
        }
    }
};

#endif // INSTRUCTION_H
