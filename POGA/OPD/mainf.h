#ifndef MAINF_H
#define MAINF_H

#include"head.h"
#include"func.h"
#include"class.h"

class mainfile
{
private:
    char *fname;
    char *fname1;
    vector<vector<string>> Data;
public:
    mainfile(){}

    void setpars( char*str)
    {
        fname=str;
    }
    void setdata(char*str)
    {
        fname1=str;
    }


    void start()
    {
        List_str LS;
        LS._create(fname);
        Parser pars(LS._get());
        dannie data;
        data.create(fname1);
        pars.createdata(data);
        Data=pars.getdata();
        //pars.printdata();
    }
    vector<vector<string>> getdata()
    {
      return Data;
    }

    char*getfname(){return fname;}
    char*getfname1(){return fname1;}





};









#endif // MAINF_H
