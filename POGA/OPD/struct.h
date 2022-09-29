#ifndef STRUCT_H
#define STRUCT_H


#include "head.h"
#include "token.h"
using namespace std;



//������ �������
class ELEMENT
{
protected:
    string type;//1��� ������
    string order;//1.5
    string name;//2�������� ������

    struct formsave//3������ ��������
    {
      string nf;//����������������� ������
      string type;//��� ��������
      string num;//����� ����
    }; formsave fs;

    struct formprint//4������ ������������
    {
      string nf;
      string type;
      string num;
    }; formprint fp;

    struct formtransf//5������ ��������������(���� ����)
    {
      string nf;
      string type;
      string num;//����� ����
    }; formtransf ft;


    string NA;//6��������� ���������(���� ����)
    string coment;//7����������


    string data;//������
    string str_data;//������ ���� (��� ��� ������)
public:
    ELEMENT(){}

    string gettype(){return type;}//������ ����
    string getorder(){return order;}//������ ������
    string getname(){return name;}//������ �����
    string getfstype(){return fs.type;}//������ ������� ��������
    string getfsbyte(){return fs.num;}//������ ����� ������� ��������
    string getdata(){return data;}//������ ������
    string getstrdata(){return str_data;}//������ ������ ���� ����� � ������


    //������������� ������������� ��������
    void create(vector<string>  tp)
    {
        for(int i=0;i<tp.size();i++)
        {
            if(i==0) type=tp[i];
            if(i==1) name=tp[i];
            if(i==(tp.size()-1)) { coment=tp[i];break;}
            if(i==2) fs.nf=tp[i];
            if(i==3) fp.nf=tp[i];
            if(i==4)
            {
                if(tp[i]=="NA") NA=tp[i];
                else ft.nf=tp[i];
            }
            if(i==5) NA=tp[i];
        }

        edit_elem();
    }


    //(�������� �������) ��������� ����,���������������� �������� ��������, ������������, �������������
    void edit_elem()
    {
        char str[500];
        strcpy(str, type.c_str());
        Tokens T;
        vector<string> tp=T.edit_token(str);
        for(int j=0;j<tp.size();j++)
        {
            if(j==0) type=tp[j];
            if(j==1) order=tp[j];
        }

        strcpy(str, fs.nf.c_str());
        tp=T.edit_token(str);
        for(int j=0;j<tp.size();j++)
        {
            if(j==0) fs.type=tp[j];
            if(j==1) fs.num=tp[j];
        }

        strcpy(str, fp.nf.c_str());
        tp=T.edit_token(str);
        for(int j=0;j<tp.size();j++)
        {
            if(j==0) fp.type=tp[j];
            if(j==1) fp.num=tp[j];
        }

        strcpy(str, ft.nf.c_str());
        tp=T.edit_token(str);
        for(int j=0;j<tp.size();j++)
        {
            if(j==0) ft.type=tp[j];
            if(j==1) ft.num=tp[j];
        }
    }



    //����������� ����� ������
    virtual void print()
    {
        cout<<type<<" ";
        cout<<order<<" ";
        cout<<name<<" ";
        cout<<fs.type<<" ";
        cout<<fs.num<<" ";
        cout<<fp.type<<" ";
        cout<<fp.num<<" ";
        cout<<ft.type<<" ";
        cout<<ft.num<<" ";
        cout<<NA<<" ";
        cout<<coment<<" ";
    }


    //�������� ������
    virtual int datael(int pos,char *Data)
        {
            int byte;
            byte=atoi(fs.num.c_str());
            if((fs.type=="B")||(fs.type=="BI"))
            {
                    pos=hex_dec(pos,byte,Data);
                    str_data=type+" "+name+" "+data;
                    //cout<<str_data<<endl;
            }
            if((fs.type=="FA")||(fs.type=="AA")||(fs.type=="FC")||(fs.type=="AS"))
            {
                    pos=hex_asci(pos,byte,Data);
                    str_data=type+" "+name+" "+data;
                    //cout<<str_data<<endl;
            }
            if((fs.type=="A")||(fs.type=="F"))
            {
                    pos=hex_dcoi(pos,byte,Data);
                    str_data=type+" "+name+" "+data;
                    //cout<<str_data<<endl;
            }
            return pos;
        }


    //16 � 10 �������
        int hex_dec(int pos,int byte,char *Data)
        {
            string buf;
            char* istr = new char[byte];
            char* str = new char[byte];
            for(int i=0;i<byte;i++)
            {
                istr[i]=Data[pos];
                pos++;
            }
            for(int j = 0;j < byte;j++)
            {
                sprintf(str,"%X",(int)(unsigned char)istr[j]);
                if(strlen(str)==1){buf=buf+"0"+str;}
                else {buf=buf+str;}
            }

            if(((strcmp(buf.c_str(),"7FFFFFFF")>0)&&(byte==4))||((strcmp(buf.c_str(),"800000")==0)&&(byte==3))||((strcmp(buf.c_str(),"8000")==0)&&(byte==2))||((strcmp(buf.c_str(),"80")==0)&&(byte==1)))
            {
                data="Null";
                return pos;
            }
            long datalong= stol(buf,nullptr,16);
            data=to_string(datalong);
            return pos;
        }

        //16 � ASCII
        int hex_asci(int pos,int byte,char *Data)
        {
            string buf;
            char* istr = new char[byte];
            char* str = new char[byte];
            for(int i=0;i<byte;i++)
            {
                istr[i]=Data[pos];
                pos++;
            }
            for(int j = 0;j < byte;j++)
            {
                sprintf(str,"%X",(int)(unsigned char)istr[j]);
                if(strlen(str)==1)
                {
                    char ch;
                    int low = hex_to_int(str[0]);
                    if(low>=128){ch=translate(table,low);}
                    else ch=(char)low;
                    buf=buf+ch;
                }
                else
                {
                    char ch;
                    int high = hex_to_int(str[0]) * 16;
                    int low = hex_to_int(str[1]);
                    int hl=high+low;
                    if(hl>=128){ch=translate(table,hl);}
                    else ch=(char)hl;
                    buf=buf+ch;
                }
            }
            data=buf;
            return pos;
        }

        //16 � ����� �����
        int hex_to_int(char c)
        {
            int first = c / 16 - 3;
            int second = c % 16;
            int result = first*10 + second;
            if(result > 9)
                result--;
            return result;
        }

        //16 � ����
        int hex_dcoi(int pos,int byte,char *Data)
        {
            string buf;
            char* istr = new char[byte];
            char* str = new char[byte];
            for(int i=0;i<byte;i++)
            {
                istr[i]=Data[pos];
                pos++;
            }
            string buffer;
            for(int j = 0;j < byte;j++)
            {
                sprintf(str,"%X",(int)(unsigned char)istr[j]);
                if(strlen(str)==1){buf="0"+str[0];}
                else {buf=str;}

                if (buf == "C1") { buffer+='�'; }
                else if (buf == "BA") { buffer+='�'; }
                else if (buf == "C2") { buffer+='�'; }
        else if (buf == "BF") { buffer+='�'; }
        else if (buf == "BC") { buffer+='�'; }
        else if (buf == "C5") { buffer+='�'; }
        else if (buf == "EC") { buffer+='�'; }
        else if (buf == "FA") { buffer+='�'; }
        else if (buf  == "CB") { buffer+='�'; }
        else if (buf == "CC") { buffer+='�'; }
        else if (buf  == "D2") { buffer+='�'; }
        else if (buf  == "CE") { buffer+='�'; }
        else if (buf == "D4") { buffer+='�'; }
        else if (buf  == "C8") { buffer+='�'; }
        else if (buf  == "D6") { buffer+='�'; }
        else if (buf  == "DC") { buffer+='�'; }
        else if (buf == "D7") { buffer+='�'; }
        else if (buf == "C3") { buffer+='�'; }
        else if (buf  == "E3") { buffer+='�'; }
        else if (buf  == "EB") { buffer+='�'; }
        else if (buf  == "BE") { buffer+='�'; }
        else if (buf == "E7") { buffer+='�'; }
        else if (buf  == "BB") { buffer+='�'; }
        else if (buf  == "FE") { buffer+='�'; }
        else if (buf  == "FB") { buffer+='�'; }
        else if (buf == "FD") { buffer+='�'; }
        else if (buf  == "EF") { buffer+='�'; }
        else if (buf  == "EE") { buffer+='�'; }
        else if (buf == "FC") { buffer+='�'; }
        else if (buf  == "B8") { buffer+='�'; }
        else if (buf == "DD") { buffer+='�'; }
        else if (buf  == "81") { buffer+='�'; }
        else if (buf  == "78") { buffer+='�'; }
        else if (buf  == "AF") { buffer+='�'; }
        else if (buf == "8D") { buffer+='�'; }
        else if (buf  == "8A") { buffer+='�'; }
        else if (buf== "85") { buffer+='�'; }
        else if (buf== "AE") { buffer+='�'; }
        else if (buf== "B2") { buffer+='�'; }
        else if (buf== "8F") { buffer+='�'; }
        else if (buf== "90") { buffer+='�'; }
        else if (buf== "9A") { buffer+='�'; }
        else if (buf== "9B") { buffer+='�'; }
        else if (buf== "9C") { buffer+='�'; }
        else if (buf== "9D") { buffer+='�'; }
        else if (buf== "96") { buffer+='�'; }
        else if (buf== "9F") { buffer+='�'; }
        else if (buf== "97") { buffer+='�'; }
        else if (buf== "83") { buffer+='�'; }
        else if (buf== "AC") { buffer+='�'; }
        else if (buf== "A8") { buffer+='�'; }
        else if (buf== "8C") { buffer+='�'; }
        else if (buf== "A7") { buffer+='�'; }
        else if (buf== "80") { buffer+='�'; }
        else if (buf== "B6") { buffer+='�'; }
        else if (buf== "B3") { buffer+='�'; }
        else if (buf== "B5") { buffer+='�'; }
        else if (buf== "B7") { buffer+='�'; }
        else if (buf== "B1") { buffer+='�'; }
        else if (buf== "B0") { buffer+='�'; }
        else if (buf== "B4") { buffer+='�'; }
        else if (buf== "76") { buffer+='�'; }
        else if (buf== "A0") { buffer+='�'; }
        else if (buf== "30") { buffer+='0'; }
        else if (buf== "31") { buffer+='1'; }
        else if (buf== "4B") { buffer+='K'; }
        else if (buf== "4F") { buffer+='O'; }
        else if (buf== "52") { buffer+='R'; }
        else if (buf== "60") { buffer+='\''; }
        else if (buf== "2C") { buffer+=','; }
        else if (buf== "32") { buffer+='2'; }
        else if (buf== "36") { buffer+='6'; }
        else if (buf== "3B") { buffer+=';'; }
        else if (buf== "16") { buffer+=32; }
        else if (buf== "7F") { buffer+=32; }
        else if (buf== "DF") { buffer+='�';}
        else if (buf== "DB") { buffer+='�'; }
        else if (buf== "B9") { buffer+='�';}
        else if (buf== "DA") { buffer+='�';}
        else if (buf== "ED") { buffer+='�';}
        else if (buf== "BD") { buffer+='�';}
        else if (buf== "EA") { buffer+='�';}
        else if (buf== "DE") { buffer+='�';}
        else if (buf== "3A") { buffer+=':';}
        else if (buf== "38") { buffer+='8';}
        else if (buf== "33") { buffer+='3';}
            }
            data=buffer;
            return pos;
        }

        char *table="������������������������������������������������---�+�������---�L+T+-+��L�T�=+��TTLL-�++----��-���������������������������v���	";
        char translate(char* table, int d) {
          return table[d-128];
        }








};


typedef vector<ELEMENT>elements;













//����� ������(������)(������������ ��� �������� �����,RBODY,RECORDS)
class sect: public ELEMENT
{
    elements mass_el;//������ ���������
    int marks=0;//����� ��������
    int index=1;//������ �����
    vector<int> nomera;//������ ��������, ��� ���� ������
    vector<sect> grpes;//������
    vector<string> stroka_data;//������ � �������
public:
    sect(){}

    elements getmass_el(){return mass_el;}//��������� ���������
    vector<string> getsd(){return stroka_data;}//��������� ����� � �������

    //���������� ��������
    void push_elem(vector<string> tp)
    {
        ELEMENT el;
        el.create(tp);
        mass_el.push_back(el);
    }


    //������ �������
    void print(int probels=0)
    {
        int i=0;
        cout<<endl;
        cout<<type<<" "<<order<<" "<<name<<" "<<coment<<" "<<index<<endl;
        while(i<mass_el.size())
        {
            for(int k=0;k<probels;k++) cout<<" |";
            string str=mass_el[i].gettype();
            if((str.find("GRP")!=-1)||(str.find("GRV")!=-1)||(str.find("GRK")!=-1))
            {
                for(int j=0;j<nomera.size();j++)
                {
                    if(nomera[j]-1==i)
                    {
                        mass_el[i].ELEMENT::print();
                        grpes[j].print(probels+1);
                    }
                }
            }
            else
            {
                mass_el[i].ELEMENT::print();
                cout<<endl;
            }
            i++;
        }
        for(int k=0;k<probels;k++) cout<<" |";
        cout<<"END "<<name<<endl;
    }





    //�������� �������(����� ���� �����������)
    int create(int i,vector<string> notF_Str)
    {
        //�������� ���� ������
        char str[500];
        strcpy(str, notF_Str[i].c_str());
        Tokens T;
        vector<string> tp=T.create_token(str);
        for(int j=0;j<tp.size();j++)
        {
            if(j==0) type=tp[j];
            edit_elem();
            if(j==1) name=tp[j];
            if(j==(tp.size()-1)){ coment=tp[j];break;}
        }
        i++;
        if(notF_Str[i].find("IND")!=-1)
        {
            strcpy(str, notF_Str[i].c_str());
            tp=T.create_token(str);
            ELEMENT ind;
            ind.create(tp);
            index= atoi(ind.getorder().c_str());
            if(notF_Str[i+1].find("IND")!=-1)
            {
                strcpy(str, notF_Str[i+1].c_str());
                tp=T.create_token(str);
                ind.create(tp);
                int in;
                in= atoi(ind.getorder().c_str());
                index=index*in;
            }
        }

        string s="END";
        while(notF_Str[i].find(s)==-1)
        {
            if((notF_Str[i].find("GRP")!=-1)||(notF_Str[i].find("GRV")!=-1)||(notF_Str[i].find("GRK")!=-1))
            {
                marks++;
                strcpy(str, notF_Str[i].c_str());
                tp=T.create_token(str);
                push_elem(tp);

                sect Newsect;
                i=Newsect.create(i,notF_Str);
                grpes.push_back(Newsect);
                nomera.push_back(marks);
                i++;
            }
            else
            {
                marks++;
                strcpy(str, notF_Str[i].c_str());
                tp=T.create_token(str);
                push_elem(tp);
                i++;
            }
        }
        return i;
    }


    //�������� ������ ���������
    int datael(int pos,char *data,int indeks=0)
    {
        //cout<<type<<endl;
        if(type=="GRV") indeks=indeks;
        else {
            indeks=index;
        }
        //cout<<indeks;
        for(int k=0;k<indeks;k++)
        {
            for(int i=0;i<mass_el.size();i++)
            {
                if(mass_el[i].gettype()=="IND"){i++;};
                if(mass_el[i].gettype()=="GRP")
                {
                    for(int j=0;j<nomera.size();j++)
                    {
                        if(nomera[j]-1==i)
                        {
                            pos=grpes[j].datael(pos,data);
                            vector<string>v=grpes[j].getsd();
                            grpes[j].cleardata();
                            stroka_data.insert(stroka_data.end(),  v.begin(),  v.end());
                        }
                    }
                }


                if((mass_el[i].gettype()=="GRV")||(mass_el[i].gettype()=="GRK"))
                {
                    int chislo;
                    int l;
                    for(l=0;l<mass_el.size();l++)
                        if(mass_el[i].getorder()==mass_el[l].getname())
                            chislo=stoi(mass_el[l].getdata());
                    for(int j=0;j<nomera.size();j++)
                    {
                        if(nomera[j]-1==i)
                        {
                            pos=grpes[j].datael(pos,data,chislo);
                            vector<string>v=grpes[j].getsd();
                            grpes[j].cleardata();
                            stroka_data.insert(stroka_data.end(),  v.begin(),  v.end());
                        }
                    }
                }
                else{pos=mass_el[i].datael(pos,data);if(mass_el[i].getstrdata()!="") stroka_data.push_back(mass_el[i].getstrdata());}
            }

            //cout<<endl;
        }
        return pos;
    }

    //������ ������ � �������
    void cleardata()
    {
        stroka_data.clear();
    }









};






















#endif // STRUCT_H
