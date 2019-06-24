#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

struct Record
{
    string word;
    int count;
};

class Dictionary
{
public:
    void read(const string & filename)
    {
        ifstream ifs(filename.c_str());//c++风格的字符串转换为c风格的，不然vimples会报错
        string str;
        if(!ifs.good())
        {
            cout << "ifstream file open failed" << endl;
            return;
        }
        while(getline(ifs,str))
        {
            stringstream ss;
            ss << str;
            string word;
            while(ss >> word)//每次读取一个单词
            {
               // cout << word << endl;
               // for(auto i=word.begin();i!=word.end();i++)
               // {
               //     cout << "*i = " << *i << endl;
               //     if(*i<'A' || (*i>'Z' && *i<'a') || *i>'z')
               //     {
               //         if(word.size()==1)
               //         {
               //             continue;
               //         }
               //         cout << "delete *i = " << *i << endl;
               //         word.erase(i);
               //     }
               // }
               // 想把符号都去掉，结果失败了
                vector<Record>::iterator it;
                for(it=vec.begin();it!=vec.end();it++)
                {
                    if(word==(*it).word)
                    {
                        (*it).count++;
                        break;
                    }
                }
                if(it==vec.end())
                {
                    Record newRe;
                    newRe.word=word;
                    newRe.count=1;
                    vec.push_back(newRe);
                }
            }
        }
        ifs.close();
    }

    void store(const string & filename)
    {
        vector<Record>::iterator it;
        ofstream ofs(filename.c_str());
        if(!ofs.good())
        {
            cout << "ofstream open file failed" << endl;
        }
        for(it=vec.begin();it!=vec.end();it++)
        {
            ofs << (*it).word << " " << (*it).count << endl;
        }
        ofs.close();
    }
private:
    vector<Record> vec;
};
int main()
{
    Dictionary dic;
    dic.read("The_Holy_Bible.txt");
    dic.store("record.txt");
    return 0;
}

