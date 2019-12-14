#ifndef SIMULATOR_H
#define SIMULATOR_H
#include <fstream>
#include <bits/stdc++.h>
#include <QObject>

#include "assembler.h"
#include "register_file.h"
#include <QProcess>
#include <QThread>
#include <QCoreApplication>

#define PC_         this->Program_Counter->getValue() /4
#define Set_PC(x)  this->Program_Counter->setValue((x)*4)
#define SYSCALL "syscall"
#define DELAY 5

#define PATH_PC_DEBUG ""
using namespace std;
class GUI;

class Simulator : public QObject
{
    Q_OBJECT
    friend class MainWindow;
private:
    Assembler* assembler;
    Register_File* register_file;
    Register* Program_Counter;

    ifstream file;
    string code_path;
    uint address;

    string file_assembly_path , file_assembly_path_pipeline;
    string file_regFile_path  , file_regFile_path_pipeline;
    string file_dataMemory_path, file_dataMemory_path_pipeline;
    QString modelsim_path;
    QString modelsim_pipeline_path;
    QString modelsim_command;
    QString modelsim_pipeline_command;
    QProcess* modelsim_process ;
    QProcess* modelsim_pipeline_process ;

    QString python_path;
    QString mode;

    uint index;
    uint max_clocks;

    vector<string> code;
    vector<string> code_from_editor;
    vector<uint> lines;
    vector<uint> PCs;
    vector<vector<string>> instructions;
    map<string,uint> Lables;
    map<string,string> data_asciiz;
    map<string,int> data_word;


public:

    void debugg_pc();
    void updateState(int);
    Simulator();
    ~Simulator();
    void Simulate();
    void Simulate(string path);
    void Split_Instruction(string s, uint i);
    uint Read_Data_Editor(vector<string>);
    void Read_Instruction_Editor();
    void Observer_Pattern();
    void Assemble_Instructions();
    void ALU_Logic();
    void clear();
    void Modelsim();
    void ASSEMBLY(vector<string>);

private:
    bool check_for_specials(string);
    bool check_for_Lable(string,uint,uint);
    vector<string> split_string(string s,string splitter);
    void print(vector<string>);
    void print(map<string,uint>);
    void print(deque<string> x);
    void print_all();

signals:
    void regfile_lines(string );
    void data_memory_lines(string);
    void updateDataMem(int); // updates both data memory and data_mem table
    void updateRegFile(int);
    vector<string> getInstruction_Editor();
    void Assemble_Instruction(vector<string>);
    void ALU_Instruction(vector<string>);
    void print_assembled_instruction();
    void print_registers();
    void update_assembled_instruction();
    void update_registers();
    void update_data_memory();
    void clear_data_memory();
    void Output_Print(string);
    void file_assembled_instructions(string path);
    void file_regFile_lines(string path);
    void file_regFile_data();
    void file_dataMemory_lines(string path);
    void file_dataMemory_data();
    void update_Text_Editor(vector<string>);
    void clearTextEditor();
    void show(vector<string>);
    void updatePipelineAssemblyCode(vector<string>);
    void highlight(uint);

public slots:
    void set_Program_Counter(string label);
    void set_Program_Counter(int adress);
    uint get_Label(string);
    vector<string> get_instructions();
    bool check_data_words(string s);
    int get_dataWord(string s);
    void update_GUI();

};

#endif // SIMULATOR_H
