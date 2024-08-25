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

    for (int i = 0; i < 5; i++)
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
            int fi = wordTrie[i].search(keyWord);
            if (fi != -1)
            {
                words[i][fi].type.push_back(type);
                words[i][fi].definition.push_back(definition);
                defTable[i].insert(definition, fi);
                continue;
            }
            Word word;
            word.id = words[i].size();
            word.word = keyWord;
            word.data = (dataSet)i;
            if (type == "") type = "()";
            word.type.push_back(type);
            word.definition.push_back(definition);
            words[i].push_back(word);
            wordTrie[i].insert(keyWord, word.id);
            defTable[i].insert(definition, word.id);
        }
        file.close();
        defTable[i].setCountSize(words[i].size());
    }
}

Word& Dictionary::getRandomWord()
{
    int data = random((int)0, (int)4);
    return words[data][random(0, words[data].size() - 1)];
}

Word& Dictionary::getRandomWord(dataSet data)
{
    return words[data][random(0, words[data].size() - 1)];
}

Word& Dictionary::getWord(dataSet data, int id)
{
    // cout <<  data << endl;
    return words[data][id];
}

void Dictionary::addWord(dataSet data, Word word)
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

void Dictionary::removeWord(dataSet data, int id)
{
    vaildId[data].push_back(id);
    wordTrie[data].remove(words[data][id].word);
    for (int i = 0; i < (int)words[data][id].definition.size(); i++)
    {
        defTable[data].remove(words[data][id].definition[i], id);
    }
    words[data][id].id = -1;
    words[data][id].word = "";
    words[data][id].type.clear();
    words[data][id].definition.clear();
    if (words[data][id].isFavorite) removeFavorite(data, id);
    removeHistory(data, id);
}

void Dictionary::editWord(dataSet data, int id, int curDef, string& def)
{
    words[data][id].definition[curDef] = def;
}

void Dictionary::addFavorite(dataSet data, int id){
    words[data][id].isFavorite = true;
    favorite.push_back({data, id});
}

void Dictionary::removeFavorite(dataSet data, int id){
    words[data][id].isFavorite = false;
    auto it = find(favorite.begin(), favorite.end(), make_pair(data, id));
    if (it != favorite.end())
    favorite.erase(it);
}

void Dictionary::removeAllFavorite(){
    for (auto v : favorite)
    {
        words[v.first][v.second].isFavorite = false;
    }
    favorite.clear();
}

vector<pair<dataSet,int>>& Dictionary::getFavorite(){
    return favorite;
}

void Dictionary::addHistory(dataSet data, int id){
    removeHistory(data, id);
    history.push_back({data, id});
}

void Dictionary::removeHistory(dataSet data, int id){
    auto it = find(history.begin(), history.end(), make_pair(data, id));
    if (it != history.end())
    history.erase(it);
}

void Dictionary::removeAllHistory(){
    history.clear();
}
vector<pair<dataSet, int>>& Dictionary::getHistory()
{
    return history;
}

vector<int> Dictionary::predictKeyword(dataSet data, vector<int> &codePoints)
{
    return wordTrie[data].predict(codePoints);
}

vector<int> Dictionary::predictDefinition(dataSet data, vector<int> &codePoints)
{
    return defTable[data].predict(codePoints);
};