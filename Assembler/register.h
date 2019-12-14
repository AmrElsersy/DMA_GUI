#ifndef REGISTER_H
#define REGISTER_H
#include <bits/stdc++.h>
using namespace std;
#include <QObject>
class Register : public QObject
{
    Q_OBJECT
private:
    string name;
    int value ;
    uint num ;
public:
    Register(string Name,uint Num,int Value=0);
    void clear();
public slots:
    void setValue(int);
    int getValue();
    uint getNum();
    string getName();

};

#endif // REGISTER_H

void clean_from_space(string& s);
