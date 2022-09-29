#ifndef FUNC_H
#define FUNC_H

#include "head.h"
//класс "список со строчками из файла ЯОД"
class List_str
{
    char *name_FILE;
    vector<string>notformated_String;
public:
    List_str(){}

    void _create(char *fname)
    {
        name_FILE=fname;
        ifstream file;
        file.open(name_FILE);
        string pstr;

        if (!file.is_open()){
            printf ("Ошибка при открытии файла для чтения");
            getchar();
        }

        while(!file.eof())
        {
            getline(file,pstr);
            if(pstr==" "){continue;}
            notformated_String.push_back(pstr);
        }
        file.close();
    }
    void _print()
    {
        for(int i = 0; i <notformated_String.size(); i++)
            cout << notformated_String[i] <<endl;
    }


    vector<string> _get(){return notformated_String;}
};



//класс "список со строчками из файла ЯОД"
class dannie
{
    int num;
    char *buf;
public:
    void create(char *fname)
    {
        char *name_FILE;
        name_FILE=fname;
        ifstream file;
        int n;
        file.open(name_FILE);
        file.seekg(0,ios_base::end);
        n=file.tellg();
        num=n;
        //cout << "Размер файла (в байтах): " <<n<<endl;
        char* buffer=new char[n+1];
        file.seekg(0,ios_base::beg);
        file.read(buffer,n);
        file.close();
        buf=buffer;
    }
    int get_num(){return num;}

    char*get_buf(){return buf;}
};



















#endif // FUNC_H
