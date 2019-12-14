#ifndef ASSEMBLER_H
#define ASSEMBLER_H
#include <QObject>
#include <bits/stdc++.h>
#include "register_file.h"
using namespace std;

#define opcode 6
#define fun 5
#define main_operand 0
#define I_Format_Fun 100
#define J_Format_Fun 200
class Simulator;
class Assembler : public QObject
{
    Q_OBJECT
    friend class Simulator;
private:
    Register_File* regFile;
    vector<deque<int>> assembled_Instructions;
    vector<string> assembled_Instr_Strings;
    map<string,pair<uint,uint>> operands;
    string operand;
    ofstream file;
    bool verify_operand(string operand_ray2);

public:
    Assembler(Register_File*);
    bool Assemble(vector<string> Instruction);
    int get_16bit_value(string s );
public slots:

    vector<string> get_assembled_strings();
    uint get_opcode(string Operand);
    uint get_fun(string Operand);
    void print(deque<int> x);
    void convert_Assemble_to_String(deque<int>,uint);
    void print_all();
    void File_assembled_instructions(string);

signals:
    uint get_register_num(string);
    uint get_PC();
    uint get_label_address(string);
    int* get_data_address(string);

    bool check_for_word(string s);
    int get_data_word(string s);

};

#endif // ASSEMBLER_H
