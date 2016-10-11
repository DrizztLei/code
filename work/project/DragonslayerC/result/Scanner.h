#ifndef SCANNER_H_

#include <iostream>
#include <cstring>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>

using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::ifstream;
using std::ofstream;
std :: string& trim(std::string &s)
{
    if (s.empty())
    {
        return s;
    }
    s.erase(0,s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
    return s;
}
class Scanner
{
protected:
    string target , path , token;
    int position;
    ifstream fin;
    bool is_commented , is_identifier , is_brace , is_quotation , back , is_single_quotation;
public:
    Scanner(string path);
    virtual ~Scanner();
    void close();
    vector<string> next(string beef);
    string nextLine();
    string isCommented(string beef);
};
string Scanner :: isCommented(string beef)
{
    string result = "";
    int length = beef.length();
    char ch ;
    for(int i = 0 ; i < length ; i++ )
    {
        ch = beef[i];
        if(is_commented)
        {
            if(ch == '*')
            {
                if(i+1 < length && beef[i+1] == '/')
                {
                    is_commented = false;
                    i++;
                }
            }
        }
        else
        {
            if(is_quotation)
            {
                if(ch == '"')
                {
                    if(!back)
                    {
                        is_quotation = false;
                    }
                    back = false;
                }
                else if(ch == '\\')
                {
                    back = !back;
                }
                else
                {
                    back = false;
                }
                result += ch;
            }
            else if(is_single_quotation)
            {
                if(ch == '\'')
                {
                    if(!back)
                    {
                        is_single_quotation = false;
                    }
                    back = false;
                }
                else if(ch == '\\')
                {
                    back = !back;
                }
                else
                {
                    back = false;
                }
                result += ch;
            }
            else if(ch == '/')
            {
                if(i+1 < length)
                {
                    if(back) back = false;

                    if(beef[i+1] == '/')
                    {
                        return result;
                    }
                    else if(beef[i+1] == '*')
                    {
                        is_commented = true;
                        i++;
                    }
                    else
                    {
                        result += ch;
                    }
                }
                else
                {
                    result += ch;
                }
            }
            else if(ch == '"')
            {
                if(back)
                {
                    back = false;
                }
                else
                {
                    is_quotation = true;
                }
                result += ch;
            }
            else if(ch == '\'')
            {
                if(back)
                {
                    back = false;
                }
                else
                {
                    is_single_quotation = true;
                }
                result += ch;
            }
            else
            {
                if(back)
                {
                    back = false;
                }
                result += ch;
            }
        }
    }
    return result;
}
vector<string> Scanner :: next(string beef)
{
    int length = beef.length();
    string temp = "";
    vector<string> result = vector<string>();
    if(beef[0] == '#')
    {
        result.push_back("#");
        bool flag = true;
        string temp = "";
        for (int position = 1; position < length; ++position)
        {
            if(beef[position] == ' ' || beef[position] == '\t')
            {
                if(trim(temp).length())
                {
                    if(flag)
                    {
                        result[0] = "#" + temp;
                        flag = false;
                        temp = "";
                        continue;
                    }
                    result.push_back(temp);
                    temp = "";
                }
                continue;
            }
            temp += beef[position];
        }
        if(temp.length())
        {
            result.push_back(temp);
        }
    }
    else
    {
        string temp = "";
        for (int i = 0; i < length; ++i)
        {
            if(beef[i] == ' ' || beef[i] == '\t')
            {
                if(trim(temp).length())
                {
                    result.push_back(temp);
                    temp = "";
                }
                continue;
            }
            temp += beef[i];
        }
        if(temp.length())
        {
            result.push_back(temp);
        }
    }
    return result;
}
Scanner :: Scanner(string path)
{
    is_commented = is_identifier = is_brace = is_quotation = back = is_single_quotation = false;
    const char ch[path.length()];
    strcpy(ch , path.c_str());
    fin.open(ch , std::ios::in);
}
string Scanner :: nextLine()
{
    while(getline(fin , target))
    {
        if(target.length() && trim((target=isCommented(target))).length())
        {
            return target;
        }
    }
    return "";
}
Scanner :: ~Scanner()
{
    fin.close();
}
#endif
