#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "KeywordTrie.hpp"
using namespace std;


enum dataSet
    {
        engEng = 0,
        engVie = 1,
        vieEng = 2,
        emoji = 3,
        slang = 4
    };

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

    vector<Word> words[5];
    KeywordTrie wordTrie[5];
    vector<int> vaildId[5];
public:
    Dictionary();
    ~Dictionary();
    vector<Word> favorite[5];
   void lodadData();
   Word& getRandomWord(dataSet data = engEng);
   void addWord(Word word, dataSet data);
   void removeWord(int id, dataSet data);
   void editWord(int id, dataSet data, int curDef, string& def);
   void addFavorite(int id, dataSet data);
   void removeFavorite(int id, dataSet data);
};
