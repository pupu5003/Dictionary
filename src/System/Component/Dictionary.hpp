#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

struct Word
{
    int id;
    bool isFavorite;
    string word;
    vector<string> type;
    vector<string> definition;
    Word();
    // Word(int id) : id(id);
    ~Word();
};

class Dictionary
{
private:
    enum dataSet
    {
        engEng = 0,
        engVie = 1,
        vieEng = 2,
        emoji = 3,
        slang = 4
    };

    vector<Word> words[5];
public:
    Dictionary();
    ~Dictionary();
   void lodadData();
};