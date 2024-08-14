#include "Dictionary.hpp"
#include <chrono>
using namespace std;


Word::Word()
{
    id = -1;
    word = "";
    data = engEng;
    type.clear();
    definition.clear();
    isFavorite = false;
}

Word::~Word()
{
    type.clear();
    definition.clear();
}

Dictionary::Dictionary()
{
    for (int i = 0; i < sizeof(VNCodePoints) / sizeof(int); i++)
    {
        mapChar[VNCodePoints[i]] = i;
    }
    // cout << sizeof(VNCodePoints) / sizeof(int);
    // exit(0);
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

    for (int i = 0; i < 3; i++)
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
            getline(ss, keyWord, '\\');
            getline(ss, type, '\\');
            getline(ss, definition);
            if (words[i].size() > 0 && words[i].back().word == keyWord)
            {
                words[i].back().type.push_back(type);
                words[i].back().definition.push_back(definition);
                continue;
            }
            Word word;
            word.id = words[i].size();
            word.word = keyWord;
            word.data = (dataSet)i;
            word.type.push_back(type);
            word.definition.push_back(definition);
            words[i].push_back(word);
            wordTrie[i].insert(keyWord, word.id);
            // cout << definition << endl;
        }
    }

    for (int i = 3; i < 5; i++)
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
            string keyWord, definition;
            getline(ss, keyWord, '\\');
            getline(ss, definition);
            Word word;
            word.id = words[i].size();
            word.word = keyWord;
            word.data = (dataSet)i;
            word.definition.push_back(definition);
            words[i].push_back(word);
            // wordTrie[i].insert(keyWord, word.id);
            // cout << definition << endl;
        }
    }
}

Word& Dictionary::getRandomWord(dataSet data)
{
    data = (dataSet)random(0, 4);
    return words[data][random(0, words[data].size() - 1)];
}

void Dictionary::addWord(Word word, dataSet data)
{
    if ((int)vaildId[data].size() > 0)
    {
        word.id= vaildId[data].back();
        vaildId[data].pop_back();
        words[data][word.id] = word;
        wordTrie[data].insert(word.word, word.id);
    }
    else
    {
        word.id = words[data].size();
        words[data].push_back(word);
        wordTrie[data].insert(word.word, word.id);
    }

}

void Dictionary::removeWord(int id, dataSet data)
{
    vaildId[data].push_back(id);
    wordTrie[data].remove(words[data][id].word);
    words[data][id] = Word();
}

void Dictionary::editWord(int id, dataSet data, int curDef, string& def)
{
    words[data][id].definition[curDef] = def;
}

void Dictionary::addFavorite(dataSet data, int id){
    words[data][id].isFavorite = true;
    favorite.push_back({data, id});
}

void Dictionary::removeFavorite(dataSet data, int id){
    words[data][id].isFavorite = false;
    for (int i = 0; i < favorite.size(); i++)
    {
        if (favorite[i].first == data && favorite[i].second == id)
        {
            swap(favorite[i], favorite.back());
            favorite.pop_back();
            break;
        }
    }
}

