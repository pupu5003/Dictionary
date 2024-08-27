#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "KeywordTrie.hpp"
#include "FontHelper.hpp"
#include "OtherFunc.hpp"
#include "DefHashTable.hpp"
#include <wchar.h>
using namespace std;


enum dataSet
{
    engEng = 0,
    engVie = 1,
    vieEng = 2,
    emoji = 3,
    slang = 4,
    null = -1
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
    DefHashTable defTable[5];
    vector<int> validId[5];
    vector<pair<dataSet, int>> favorite, history;

    //If the data set has been changed, so rewrite
    vector<bool> changed;

public:
    Dictionary();
    ~Dictionary();

    void loadData();
    void loadDataSets();
    void loadFavorite(const char* filePath);
    void loadHistory(const char* filePath);
    void loadOpenSlot(const char* filePath);

    Word& getRandomWord();
    Word& getRandomWord(dataSet data);
    Word& getWord(dataSet data, int id);
    void addWord(Word word);
    void removeWord(dataSet data, int id);
    void editDef(dataSet data, int id, int index, string ty, string def);
    void removeDef(dataSet data, int id, int index);
    void addFavorite(dataSet data, int id);
    void removeFavorite(dataSet data, int id);
    void removeAllFavorite();
    vector<pair<dataSet,int>>& getFavorite();
    void addHistory(dataSet data, int id);      //Word is added to history in SearchResPage constructor.
    void removeHistory(dataSet data, int id);
    void removeAllHistory();
    vector<pair<dataSet,int>>& getHistory();
    vector<int> predictKeyword(dataSet data, vector<int> &codePoints);
    vector<int> predictDefinition(dataSet data, vector<int> &codePoints);

    void saveData();
    void saveFavorite(const char* filePath);
    void saveHistory(const char* filePath);
    void saveDataSet(int set);
    void saveOpenSlot(const char* filePath);
};
