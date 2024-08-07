#include "Dictionary.hpp"
using namespace std;

Word::Word()
{
    id = -1;
    word = "";
    type.clear();
    definition.clear();
    bool isFavorite = false;
}

Word::~Word()
{
    type.clear();
    definition.clear();
}

Dictionary::Dictionary()
{
    lodadData();
}

Dictionary::~Dictionary()
{
    for (int i = 0; i < 5; i++)
    {
        words[i].clear();
    }
}

void Dictionary::lodadData()
{
    const char *fileName[5] = {"data/DictionaryData/engEng.txt", "data/DictionaryData/engVie.txt", "data/DictionaryData/vieEng.txt", "data/DictionaryData/emoji.txt", "data/DictionaryData/slang.txt"};

    for (int i = 0; i < 1; i++)
    {
        ifstream file(fileName[i]);
        if (!file.is_open())
        {
            cout << "Can't open file " << fileName[i] << endl;
            return;
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string keyWord, type, definition;
            getline(ss, keyWord, ',');
            getline(ss, type, ',');
            getline(ss, definition);
            Word word;
            word.id = words[i].size();
            word.word = keyWord;
            word.type.push_back(type);
            word.definition.push_back(definition);
            words[i].push_back(word);
        }
    }
}