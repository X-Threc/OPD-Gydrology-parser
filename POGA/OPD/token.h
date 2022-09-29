#ifndef TOKEN_H
#define TOKEN_H

#include <string.h>
#include <iostream>
#include <vector>
using namespace std;



//токены-массив строк, которые позднее будут приписаны характеристикам элемента
//создание токена
class Tokens
{
public:

    vector<string> create_token(char* str)
    {
        vector<string> Token_mass;
        int j=0;
        string token;
        while(j < strlen(str))
        {
            if( (str[j]==' ') || (str[j]==';'))  {j++;if(str[j]==')')j++;}
            else if (str[j]=='/')
            {
                j=j+2;

                for(j;j<strlen(str);j++) token=token+str[j];
                //cout<<token<<" ";
                Token_mass.push_back(token);
                token="";
                break;
            }

            else
            {
                token=token+str[j];
                if( (str[j+1]==' ') || (str[j+1]==';'))
                {
                    if(str[j+2]==')') token=token+str[j+2];
                    //cout<<token<<" ";
                    Token_mass.push_back(token);
                    token="";
                }
                j++;
            }
        }
        //cout<<endl;
        return Token_mass;
    }


    //содание токенов из характеристик со скобачками
    vector<string>  edit_token(char* str)
    {
        vector<string> Token_mass;
        int j=0;
        string token;
        while(j < strlen(str))
        {
            if(str[j]=='(')
            {
                j++;
                for(j;j<strlen(str)-1;j++)if(str[j]!=' ') token=token+str[j];
                Token_mass.push_back(token);
                token="";
                break;
            }
            else
            {
                token=token+str[j];
                if(str[j+1]=='(')
                {
                    Token_mass.push_back(token);
                    token="";
                }
                j++;
            }
        }
        return Token_mass;
    }

};










#endif // TOKEN_H
