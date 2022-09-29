#ifndef CLASS_H
#define CLASS_H

#include "head.h"
#include "func.h"
#include "token.h"
#include "struct.h"


//����� ������
class Parser
{
    vector<string>notF_Str;//����������������� �������


    string namefile;//��� �����(������ �������)
    vector<string>coment;//����������(����


    string rec;//������ RECORDS
    sect Records;//������ RECORDS


    vector<sect> Rbody;//������� RBODY
    vector<vector<string>> DATA;//������ � ������ � �������

    int num_rbody=0;//����� RBODY
public:
    Parser(vector<string> str){ notF_Str=str; start();}

    //������
    void start()
    {
        int i=0;
        namefile=notF_Str[i];
        i++;
        i=createComent(i);
        i=createRecords(i);
        while(i<notF_Str.size())
        {
            if(notF_Str[i].find("RBODY")!=-1) i=createRbody(i);
            i++;
        }


//        for(int j=0;j<num_rbody;j++)
//        {
//            cout<<rec<<endl;
//            Records.print();
//            Records.print();
//            Rbody[j].print();
//            cout<<j+1<<"fffffffffffffffffffffffffffffffffffffffffffffffffff\n\n\n\n";
//        }
    }


    //�������� ���������� � �����
    int createComent(int i)
    {
        string s;
        char str[500];
        while(notF_Str[i].find("RECORDS")==-1)
        {
            strcpy(str, notF_Str[i].c_str());
            int j=0;
            while(j < strlen(str)){
                if(str[j]=='/'){j++;}
                else{
                    s=s+str[j];
                    j++;
                }
            }
            //cout<<s<<endl;
            coment.push_back(s);
            s="";
            i++;
        }
        return i;
    }


    //�������� RECORDS
    int createRecords(int i)
    {
        rec=notF_Str[i];
        i++;
        char str[500];
        while(notF_Str[i].find("RBODY")==-1)
        {
            strcpy(str, notF_Str[i].c_str());
            Tokens T;
            Records.push_elem(T.create_token(str));
            i++;
        }
        return i;
    }




    //�������� RBODY
    int createRbody(int i)
    {
        sect sectr;
        i=sectr.create(i,notF_Str);
        Rbody.push_back(sectr);
        num_rbody++;
        return i;
    }



    //�������� ������� ����� � �������
    void createdata(dannie Data)
    {
        int  pos=0;
        int  count=Data.get_num();
        char *data=Data.get_buf();
        while((pos<count))
        {

            pos=Records.datael(pos,data);
            string str=Records.getmass_el()[Records.getmass_el().size()-1].getdata();
            int i=stoi(str);
            if((i<1)||(i>Rbody.size())) break;
            pos=Rbody[i-1].datael(pos,data);

            vector<string> newvec=Records.getsd();
            vector<string> v=Rbody[i-1].getsd();
            newvec.insert(newvec.end(),v.begin(),v.end());



            DATA.push_back(newvec);
            Records.cleardata();
            Rbody[i-1].cleardata();
        }

    }

    //��������� ����� � �������
    vector<vector<string>> getdata()
    {
        return DATA;
    }





    //������ ����� � �������
    void printdata()
    {
        for(int i=0;i<DATA.size();i++)
        {
            for(int j=0;j<DATA[i].size();j++)
                cout<<DATA[i][j]<<endl;
            cout<<endl<<endl<<endl;
        }
    }









};









#endif // CLASS_H
