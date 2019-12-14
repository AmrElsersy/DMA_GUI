#include "register_file.h"

Register_File::Register_File(QObject *parent) : QObject(parent)
{
    add_register("$zero",0);
    add_register("$at",1);
    add_register("$v0",2);
    add_register("$v1",3);
    add_register("$a0",4);
    add_register("$a1",5);
    add_register("$a2",6);
    add_register("$a3",7);
    add_register("$t0",8);
    add_register("$t1",9);
    add_register("$t2",10);
    add_register("$t3",11);
    add_register("$t4",12);
    add_register("$t5",13);
    add_register("$t6",14);
    add_register("$t7",15);
    add_register("$s0",16);
    add_register("$s1",17);
    add_register("$s2",18);
    add_register("$s3",19);
    add_register("$s4",20);
    add_register("$s5",21);
    add_register("$s6",22);
    add_register("$s7",23);
    add_register("$t8",24);
    add_register("$t9",25);
    add_register("$k0",26);
    add_register("$k1",27);
    add_register("$gp",28);
    add_register("$sp",29);
    add_register("$fp",30);
    add_register("$ra",31);

    this->Stack_Pointer.push(0);
    this->Registers["$sp"]->setValue(  STACK_SIZE  );
}

void Register_File::add_register(string Name, uint Num, int Value )
{
    this->Registers[Name] = new Register(Name,Num,Value);
}

void Register_File::clear()
{
    for (auto it = Registers.begin();it != Registers.end();it ++) {
        it->second->clear();
    }
    this->Registers["$sp"]->setValue(STACK_SIZE);
    this->lines.clear();
}

map<string,Register*> Register_File::registers_reading()
{
    return this->Registers;
}

void Register_File::print_all()
{
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
    for (auto i = this->Registers.begin(); i != this->Registers.end(); i++)
        cout << i->first << " = " << i->second->getValue() << endl;
    cout << "$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
}

void Register_File::push(string name)
{
    if(this->Stack_Pointer.empty())
    {
        cout << "Stack is Empty POP" << endl;
        return;
    }
    if (this->Stack_Pointer.size() >= STACK_SIZE/WORD_SIZE)
    {
        cout << "Stack OverFlow Ray2" << endl;
        return;
    }

    int value = this->Registers[name]->getValue();
    this->Stack_Pointer.push(value);

    this->Registers["$sp"]->setValue( this->Registers["$sp"]->getValue() - WORD_SIZE );
}

void Register_File::pop(string name)
{
    if(this->Stack_Pointer.empty())
    {
        cout << "Stack is Empty POP" << endl;
        return ;
    }

    int value = this->Stack_Pointer.top();
    this->Stack_Pointer.pop();

    this->Registers[name]->setValue(value);
    this->Registers["$sp"]->setValue( this->Registers["$sp"]->getValue() + WORD_SIZE );
}

void Register_File::stack_write(string name)
{
    this->Stack_Pointer.top() = this->Registers[name]->getValue();
}

void Register_File::stack_read(string name)
{
    this->Registers[name]->setValue( this->Stack_Pointer.top());
}
void Register_File::set_lines(string path)
{
    lines.clear();
    this->file.open(path);
    if (!file.is_open())
    {
        cout << "Cannot open RegFile" << endl;
        return;
    }
    string s;
    while(getline(this->file,s)) // read line by line
    {
        this->lines.push_back(s);
    }
    file.close();
}
int Register_File::get_regClocks(){
    return lines.size();
}
void Register_File::read_regFile_data()
{

        if(lines.size() == 0)
        {
            cout << "error in entered file";
            return;
        }
        string s = lines[lines.size()-1];
        if (s == "" || s == " ")
            return;
        vector<string> k = split_string(s," ");
        for (uint i =0 ; i <k.size(); i++)
        {
         vector<string> address_value = split_string(k[i],","); if (address_value.size() == 1) {continue;}
        uint address = uint( stoi(address_value[0]) );
        int value    = stoi (address_value[1] );
        this->write_register(address,value);
        }
}

void Register_File::read_regFile_data(int i)
{
        if(lines.size() == 0)
        {
            cout << "error in entered file";
            return;
        }
        string s = lines[i];
        if (s == "" || s == " ")
            return;
        vector<string> k = split_string(s," ");
        for (uint i =0 ; i <k.size(); i++)
        {
         vector<string> address_value = split_string(k[i],","); if (address_value.size() == 1) {continue;}
        uint address = uint( stoi(address_value[0]) );
        int value    = stoi (address_value[1] );
        this->write_register(address,value);
        }
}

void Register_File::updateRegFilePipeline(string regFileClock)
{
    if (regFileClock == "" || regFileClock == " ")
        return;
    vector<string> s = split_string(regFileClock," ");
    for (uint i =0 ; i <s.size(); i++)
    {
        try {
            vector<string> address_value = split_string(s[i],","); if (address_value.size() == 1) {continue;}
            uint address = uint( stoi(address_value[0]) );
            int value    = stoi (address_value[1] );
            this->write_register(address,value);
        } catch (...) {
            cout << "error in regfile pipeline (" << s[i] << ")" << endl;
        }
    }
}
/*
void Register_File::updateRegsPipeline
}
*/

int Register_File::read_register(string name)
{
    return this->Registers[name]->getValue();
}

uint Register_File::get_register_num(string name)
{
    bool found = false;
    for(auto i = this->Registers.begin() ; i!= this->Registers.end() ; i++)
        if(i->first == name)
            found = true;
    if (!found)
        throw invalid_argument("invalid register name :"+name);

    return this->Registers[name]->getNum();
}

void Register_File::write_register(string name,int Value)
{
    this->Registers[name]->setValue(Value);
}

void Register_File::write_register(uint address, int value)
{
    for (auto it = this->Registers.begin() ; it != this->Registers.end(); it++)
    {
        if(it->second->getNum() == address) // seconed is pointer to Register
        {
            it->second->setValue(value);
            return;
        }
    }
}
vector<string> Register_File :: split_string(string s,string splitter)
{
    vector<string> splitted;
    uint n = s.length();
    int pos = 0;
    int start = pos;
    while (pos != string::npos)
    {
        pos = s.find_first_of(splitter,pos+1);
        string splitted_string = s.substr(start,pos-start);
        splitted.push_back(splitted_string);
        start = pos+1;
    }

    return splitted;}
