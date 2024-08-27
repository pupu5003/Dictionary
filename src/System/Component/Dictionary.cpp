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
    loadData();
}

Dictionary::~Dictionary()
{
    saveData();
    for (int i = 0; i < 5; i++)
    {
        words[i].clear();
    }
}

void Dictionary::loadData() {
    loadDataSets();
    loadFavorite("data/Favorite/Favorite.txt");
    loadHistory("data/History/History.txt");
    loadOpenSlot("data/OpenSlot/OpenSlot.txt");
}

void Dictionary::saveData() {
    saveFavorite("data/Favorite/Favorite.txt");
    saveHistory("data/History/History.txt");
    saveOpenSlot("data/OpenSlot/OpenSlot.txt");
    for (int i = 0; i < 5; ++i) {
        if (changed[i]) saveDataSet(i);
    }
}

void Dictionary::loadDataSets()
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

        
        cout << "Load data set " << fileName[i] << " successfully.\n";
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

void Dictionary::addWord(Word word)
{
    dataSet data = word.data;
    if ((int)vaildId[data].size() > 0)
    {
        word.id= validId[data].back();
        validId[data].pop_back();
        words[data][word.id] = word;
        wordTrie[data].insert(word.word, word.id);
    }
    else
    {
        word.id = words[data].size();
        words[data].push_back(word);
        wordTrie[data].insert(word.word, word.id);
    }
    for (int i = 0; i < (int)word.definition.size(); i++)
    {
        defTable[data].insert(word.definition[i], word.id);
    }
    if (word.isFavorite) addFavorite(data, word.id);

    //Set data set as changed
    changed[(int)data] = true;
}

void Dictionary::removeWord(dataSet data, int id)
{
    validId[data].push_back(id);
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
  
    //Set data set as changed
    changed[(int)data] = true;
}

void Dictionary::editDef(dataSet data, int id, int index, string ty, string def)
{
    ty = "(" + ty + ")";
    if (index == (int)words[data][id].definition.size())
    {
        words[data][id].type.push_back(ty);
        words[data][id].definition.push_back(def);
        defTable[data].insert(def, id);
    }
    else
    {
        words[data][id].type[index] = ty;
        if (def != words[data][id].definition[index])
        {
            defTable[data].remove(words[data][id].definition[index], id);
            words[data][id].definition[index] = def;
            defTable[data].insert(def, id);
        }
    }
 
    //Set data set as changed
    changed[(int)data] = true;
}

void Dictionary::removeDef(dataSet data, int id, int index)
{
    defTable[data].remove(words[data][id].definition[index], id);
    words[data][id].type.erase(words[data][id].type.begin() + index);
    words[data][id].definition.erase(words[data][id].definition.begin() + index);
  
    //Set data set as changed
    changed[(int)data] = true;
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

void Dictionary::loadFavorite(const char* filePath) 
{
    fstream favFile(filePath, ios::in);
    if (!favFile.is_open()) {
        cout << "Error opening favorite file.\n";
        return;
    }
    while (!favFile.eof()) {
        int inputLanguage = -1; int wordID = -1;
        favFile >> inputLanguage >> wordID;
        dataSet language = (dataSet)inputLanguage;
        if (wordID != -1) favorite.push_back({language, wordID});
    }
    cout << "Successfully loaded favorite.\n";
}

void Dictionary::loadHistory(const char* filePath) 
{
    fstream hisFile(filePath, ios::in);
    if (!hisFile.is_open()) {
        cout << "Error opening history file.\n";
        return;
    }
    while (!hisFile.eof()) {
        int inputLanguage = -1; int wordID = -1;
        hisFile >> inputLanguage >> wordID;
        dataSet language = (dataSet)inputLanguage;
        if (wordID != -1) history.push_back({language, wordID});
    }
    cout << "Successfully loaded history.\n";
}

void Dictionary::saveFavorite(const char* filePath)
{
    fstream favFile(filePath, ios::out);
    if (!favFile.is_open()) {
        cout << "Error opening favorite file.\n";
        return;
    }
    for (auto word : favorite) {
        favFile << (int)word.first << " " << word.second << '\n';
    }
    cout << "Successfully saved favorite.\n";
}

void Dictionary::saveHistory(const char* filePath)
{
    fstream hisFile(filePath, ios::out);
    if (!hisFile.is_open()) {
        cout << "Error opening favorite file.\n";
        return;
    }
    for (auto word : history) {
        hisFile << (int)word.first << " " << word.second << '\n';
    }
    cout << "Successfully saved history.\n";
}

void Dictionary::saveDataSet(int i)
{
    const char *fileName[5] = {"data/DictionaryData/engEng.txt", "data/DictionaryData/engVie.txt", "data/DictionaryData/vieEng.txt", "data/DictionaryData/emoji.txt", "data/DictionaryData/slang.txt"};

    fstream file(fileName[i], ios::out);
    if (!file.is_open())
    {
        cout << "Can't open file " << fileName[i] << endl;
        return;
    }
    for (auto word : words[i]) {
        for (int j = 0; j < word.type.size(); ++j) {
            file << word.word << '\\'
            << word.type[j] << '\\'
            << word.definition[j] << '\n';
            }
    }
}

void Dictionary::loadOpenSlot(const char* filePath) {
    fstream openSlotFile(filePath, ios::in);
    if (!openSlotFile.is_open()) {
        cout << "Error opening open slot file.\n";
        return;
    }
    while (!openSlotFile.eof()) {
        int set, slot;
        openSlotFile >> set >> slot;
        validId[set].push_back(slot);
    }
    cout << "Successfully loaded open slot.\n";
}

void Dictionary::saveOpenSlot(const char* filePath) {
    fstream openSlotFile(filePath, ios::out);
    if (!openSlotFile.is_open()) {
        cout << "Error opening open slot file.\n";
        return;
    }
    for (int i = 0; i < 5; ++i)
        for (auto slot : validId[i])
            openSlotFile << i << " " << slot << '\n';
    cout << "Successfully loaded open slot.\n";
}