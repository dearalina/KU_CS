#include "wordfrequency.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;

/** 
  * Assignment 3 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 5. 9
  *
  */

WordFrequency::WordFrequency()
{
    map = new WordFreqMap();
}

WordFrequency::~WordFrequency()
{
    delete map;
}

void WordFrequency::ReadText(const char* filename)
{
    // 逐行读取，将行读入字符串, 行之间用回车换行区分
    ifstream input(filename);
    if(!input.is_open()){
        cout << "Input file cannot be opened! Terminated";
        return;
    }
    string str;
    // in >> str替代getline(in, str)
    while(getline(input, str)) {
        std::replace_if(str.begin(), str.end(), ::isdigit, ' ');
        std::replace_if(str.begin(), str.end(), ::ispunct, ' ');
        //replace_if(str.begin(), str.end(), [](auto ch) {
            //return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
            //return ::isdigit(ch) || ::ispunct(ch);
        //}, ' ');

        // iss对象绑定一行字符串string s;
        istringstream iss(str);
        do {
            string data;
            iss >> data;
            string new_data;
            transform(data.begin(), data.end(), data.begin(), ::tolower);
            for (int i = 0; i < data.size(); i++) {
                if (data[i] >= 'a' && data[i] <= 'z') {
                    new_data += data[i];
                }
            }
            data = new_data;
            //cout << data << "\n";
            if (data.empty()) continue;
            IncreaseFrequency(data);
        } while (iss);
    }
}

int WordFrequency::GetFrequency(const std::string word)
{
    WordFreqElem* temp = (*map).find(word);
    if(temp) return temp->val;
	else return 0;
}

void WordFrequency::IncreaseFrequency(const std::string word)
{
    WordFreqElem* temp = (*map).find(word);
    if(temp){
        int v = temp->val + 1;
        (*map).insert(word, v);
    }else{
        (*map).insert(word, 1);
    }
}
