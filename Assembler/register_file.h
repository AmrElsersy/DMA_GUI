#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H
#include <bits/stdc++.h>
#include <QObject>
#include "register.h"

using namespace std;

#define WORD_SIZE sizeof(int)
#define MEMORYSIZE 8191
#define STACK_SIZE (MEMORYSIZE)

class Register_File : public QObject
{
    Q_OBJECT

private:
    map<string,Register*> Registers;
    vector<string> lines;
    stack<int> Stack_Pointer;
    ifstream file ;
public:
    Register_File(QObject *parent = nullptr);
    void add_register(string Name,uint Num , int Value = 0 );
    void clear();
    int get_regClocks();
    vector<string> split_string(string s,string splitter);

public slots:
    map<string,Register*> registers_reading();
    int read_register(string name);
    uint get_register_num(string name);
    void write_register(string name,int Value=0);
    void write_register(uint address , int value= 0);
    void print_all();
    void set_lines(string);
    // mlhosh 3aza
    void push(string name);
    void pop (string name);
    void stack_write(string name);
    void stack_read (string name);
    //
    void read_regFile_data();
    void read_regFile_data(int);
    void updateRegFilePipeline(string);

signals:
};

#endif // REGISTER_FILE_H
