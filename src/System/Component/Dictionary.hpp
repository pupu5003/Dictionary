#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "KeywordTrie.hpp"
#include "FontHelper.hpp"
#include "OtherFunc.hpp"
#include <wchar.h>
using namespace std;


enum dataSet
    {
        engEng = 0,
        engVie = 1,
        vieEng = 2,
        emoji = 3,
        slang = 4
    };
const string dataSetName[5] = {"engEng", "engVie", "vieEng", "emoji", "slang"};
struct Word
{
    int id;
    bool isFavorite;
    dataSet data;
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

    vector<Word> words[5];
    KeywordTrie wordTrie[5];
    vector<int> vaildId[5];
public:
    Dictionary();
    ~Dictionary();
    vector<pair<dataSet, int>> favorite;
   void lodadData();
   Word& getRandomWord();
   Word& getRandomWord(dataSet data);
   void addWord(Word word, dataSet data);
   void removeWord(int id, dataSet data);
   void editWord(int id, dataSet data, int curDef, string& def);
   void addFavorite(dataSet data, int id);
   void removeFavorite(dataSet data, int id);
};
