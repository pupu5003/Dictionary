#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "KeywordTrie.hpp"
#include <wchar.h>
#include "../src/System/State/UILibFunc.hpp"
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
    vector<pair<dataSet, int>> favorite, history;
public:
    Dictionary();
    ~Dictionary();
    void lodadData();
    Word& getRandomWord(dataSet data = engVie);
    Word& getWord(dataSet data, int id);
    void addWord(Word word, dataSet data);
    void removeWord(int id, dataSet data);
    void editWord(int id, dataSet data, int curDef, string& def);
    void addFavorite(dataSet data, int id);
    void removeFavorite(dataSet data, int id);
    void removeFavorite(int index);
    vector<pair<dataSet,int>>& getFavorite();
};
