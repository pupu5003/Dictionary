#include "Dictionary.hpp"
#include <chrono>
using namespace std;

int random(int min, int max)
{
    srand(chrono::system_clock::now().time_since_epoch().count());
    return rand() % (max - min + 1) + min;
}

Word::Word()
{
    id = -1;
    word = "";
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
            wordTrie[i].insert(keyWord, word.id);
        }
    }
}

Word& Dictionary::getRandomWord(dataSet data)
{
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

void Dictionary::addFavorite(int id, dataSet data){
    words[data][id].isFavorite = true;
    favorite[data].push_back(words[data][id]);
}

void Dictionary::removeFavorite(int id, dataSet data){
    words[data][id].isFavorite = false;
    for (int i = 0; i < favorite[data].size(); i++)
    {
        if (favorite[data][i].id == id)
        {
            favorite[data].erase(favorite[data].begin() + i);
            break;
        }
    }
}

