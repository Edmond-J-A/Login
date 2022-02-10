#include<instruction.h>

Instruction::Instruction(QJsonObject jsonObj)
{
    if(jsonObj.contains("command"))
    {
        QJsonValue value = jsonObj.value("command");
        if(value.isString())
        {
            this->Command=value.toString();
            qDebug() << this->Command;
        }
    }

    if(jsonObj.contains("message"))
    {
        QJsonValue value = jsonObj.value("message");
        if(value.isString())
        {
            this->Message=value.toString();
            qDebug()<<this->Message;
        }
    }

    if(jsonObj.contains("data"))
    {
        QJsonValue value = jsonObj.value("data");
        if(value.isObject())
        {
            this->Data=value.toObject();
            qDebug() << this->Data;
        }
    }
}
