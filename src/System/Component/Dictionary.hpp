#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
    DefHashTable defTable[5];
    vector<int> validId[5];
    vector<pair<dataSet, int>> favorite, history;
    bool isChanged[5];
public:
    Dictionary();
    ~Dictionary();

    void loadRawData();
    void loadData(const char *fileName[5], bool isOrigin = false);
    void saveData();
    void resetData();
    void setChangedDataSet(dataSet data);

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
    void addHistory(dataSet data, int id);
    void removeHistory(dataSet data, int id);
    void removeAllHistory();
    vector<pair<dataSet,int>>& getHistory();
    vector<int> predictKeyword(dataSet data, vector<int> &codePoints);
    vector<int> predictDefinition(dataSet data, vector<int> &codePoints);
};