#include "register.h"

Register::Register(string Name,uint Num, int Value)
{
    this->name = Name;
    this->value = Value;
    this->num = Num;
}

void Register::clear()
{
    this->value = 0;
}

void Register::setValue(int Value)
{
    this->value = Value;
}

int Register::getValue()
{
    return this->value;
}

uint Register::getNum()
{
    return this->num;
}

string Register::getName()
{
    return this->name;
}

void clean_string_from(string& s,string rubish)
{
    uint n = s.length();
    int pos = s.find_first_of(rubish);
    while(pos != string::npos)
    {
        s.erase(pos,1);
        pos = s.find_first_of(rubish);
    }

}
