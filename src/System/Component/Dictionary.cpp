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
    // loadRawData();
    const char *fileName[5] = {"data/Current/engEng.bin", "data/Current/engVie.bin", "data/Current/vieEng.bin", "data/Current/emoji.bin", "data/Current/slang.bin"};

    loadData(fileName);
}

Dictionary::~Dictionary()
{
    for (int i = 0; i < 5; i++)
    {
        words[i].clear();
    }
}

void Dictionary::loadRawData()
{
    const char *fileName[5] = {"data/RawData/engEng.txt", "data/RawData/engVie.txt", "data/RawData/vieEng.txt", "data/RawData/emoji.txt", "data/RawData/slang.txt"};

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

void Dictionary::loadData(const char *fileName[5], bool isOrigin)
{
    // const char *fileName[5] = {"data/Current/engEng.bin", "data/Current/engVie.bin", "data/Current/vieEng.bin", "data/Current/emoji.bin", "data/Current/slang.bin"};
    
    for (int i = 0; i < 5; i++)
    {
        ifstream file(fileName[i], ios::binary);
        if (!file.is_open())
        {
            cout << "Can't open file " << fileName[i] << endl;
            return;
        }
        int size;
        file.read((char *)&size, sizeof(int));
        for (int j = 0; j < size; j++)
        {
            Word word;
            int len;
            file.read((char *)&len, sizeof(int));
            char *buffer = new char[len + 1];
            file.read(buffer, len);
            buffer[len] = '\0';
            word.word = buffer;
            delete[] buffer;

            if (len == 0) validId[i].push_back(j);
            else 
            {
                word.data = (dataSet)i;
                word.id = j;
                wordTrie[i].insert(word.word, word.id);
            }

            int vecSize;
            file.read((char *)&vecSize, sizeof(int));
            for (int k = 0; k < vecSize; k++)
            {
                file.read((char *)&len, sizeof(int));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                word.type.push_back(buffer);
                delete[] buffer;
            }

            file.read((char *)&vecSize, sizeof(int));
            for (int k = 0; k < vecSize; k++)
            {
                file.read((char *)&len, sizeof(int));
                buffer = new char[len + 1];
                file.read(buffer, len);
                buffer[len] = '\0';
                word.definition.push_back(buffer);
                delete[] buffer;
            }
            words[i].push_back(word);
            for (int k = 0; k < (int)word.definition.size(); k++)
            {
                defTable[i].insert(word.definition[k], word.id);
            }
        }
        defTable[i].setCountSize(words[i].size());
        file.close();
    }

    if (isOrigin) return;
    
    ifstream file("data/Current/favorite.bin", ios::binary);
    int size = (int)favorite.size();
    file.read((char *)&size, sizeof(int));
    favorite.resize(size);
    file.read((char*)(favorite.data()), size*2*sizeof(int));
    // for (int i = 0; i < size; i++)
    // {
    //     pair<dataSet, int> p;
    //     file.read((char *)&p.first, sizeof(int));
    //     file.read((char *)&p.second, sizeof(int));
    //     addFavorite(p.first, p.second);
    // }
    file.close();
    for (int i = 0; i < size; ++i)
        words[favorite[i].first][favorite[i].second].isFavorite = true;

    
    file.open("data/Current/history.bin", ios::binary);
    size = (int)history.size();
    file.read((char *)&size, sizeof(int));
    history.resize(size);
    file.read((char*)(history.data()), size*2*sizeof(int));
    // for (int i = 0; i < size; i++)
    // {
    //     pair<dataSet, int> p;
    //     file.read((char *)&p.first, sizeof(int));
    //     file.read((char *)&p.second, sizeof(int));
    //     addHistory(p.first, p.second);
    // }
    file.close();
}

void Dictionary::saveData()
{
    const char *fileName[5] = {"data/Current/engEng.bin", "data/Current/engVie.bin", "data/Current/vieEng.bin", "data/Current/emoji.bin", "data/Current/slang.bin"};

    for (int i = 0; i < 5; i++)
    {
        ofstream file(fileName[i], ios::binary);
        if (!file.is_open())
        {
            cout << "Can't open file " << fileName[i] << endl;
            return;
        }
        int size = words[i].size();
        file.write((char *)&size, sizeof(int));
        for (const Word& word: words[i])
        {            
            int len = word.word.size();
            file.write((char *)&len, sizeof(int));
            file.write(word.word.c_str(), len);

            int vecSize = word.type.size();
            file.write((char *)&vecSize, sizeof(int));
            for (const string& s: word.type)
            {
                len = s.size();
                file.write((char *)&len, sizeof(int));
                file.write(s.c_str(), len);
            }

            vecSize = word.definition.size();
            file.write((char *)&vecSize, sizeof(int));
            for (const string& s: word.definition)
            {
                len = s.size();
                file.write((char *)&len, sizeof(int));
                file.write(s.c_str(), len);
            }
        }
        file.close();
    }


    ofstream file("data/Current/favorite.bin", ios::binary);
    int size = (int)favorite.size();
    file.write((char *)&size, sizeof(int));
    file.write((char*)(favorite.data()), size*2*sizeof(int));
    // for (const pair<dataSet, int>& p: favorite)
    // {
    //     file.write((char *)&p.first, sizeof(int));
    //     file.write((char *)&p.second, sizeof(int));
    // }
    file.close();
    file.open("data/Current/history.bin", ios::binary);
    size = (int)history.size();
    file.write((char *)&size, sizeof(int));
    file.write((char*)(history.data()), size*2*sizeof(int));
    // for (const pair<dataSet, int>& p: history)
    // {
    //     file.write((char *)&p.first, sizeof(int));
    //     file.write((char *)&p.second, sizeof(int));
    // }
    file.close();
}

Vector2 GetCenterPos(Font font, string text, float fontSize, float spacing, float x, float y, float width, float height) {
	Vector2 centerPos;
	centerPos.x = x + (width - MeasureTextEx(font, text.c_str(), fontSize, spacing).x) / 2;
	centerPos.y = y + (height - MeasureTextEx(font, text.c_str(), fontSize, spacing).y) / 2;
	return centerPos;
}

void Dictionary::DrawReset(string content) {
    float windowWidth = 1243;
    float windowHeight = 725;
    Texture reset_icon = LoadTexture("../External/source/Image/reset-icon.png");
	SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	DrawRectangle(268, 151, 700, 420, WHITE);
	DrawRectangle(268, 151, 700, 50, RAYWHITE);
	DrawRectangleLines(268, 151, 700, 420, Fade(BLACK, 0.7));
	DrawTextureEx(reset_icon, { (float)275, (float)160 }, 0, 0.07, WHITE);
	DrawTextEx(FontHelper::getInstance().getFont(RussoOne), (content + "LOADING...").c_str(), GetCenterPos(FontHelper::getInstance().getFont(RussoOne), content + "LOADING..", 40, 0.5, 268, 151, 700, 420), 40, 0.5, BLACK);
	DrawTextEx(FontHelper::getInstance().getFont(RussoOne), "Reset", GetCenterPos(FontHelper::getInstance().getFont(RussoOne), "Reset", 30, 0.5, 268, 151, 700, 50), 30, 0.5, BLACK);
	EndDrawing();
}


void Dictionary::resetData()
{
    removeAllFavorite();
    removeAllHistory();
    int percent = 0;
    for (int i = 0; i < 5; i++)
    {
        words[i].clear();
        validId[i].clear();
        wordTrie[i].clear();
        defTable[i].clear();
        percent += 15;
        ostringstream percentStream;
        percentStream << percent;
        string percentString = percentStream.str();
        string message = percentString + "% ";
        DrawReset(message.c_str());
    }
    const char *fileName[5] = {"data/Origin/engEng.bin", "data/Origin/engVie.bin", "data/Origin/vieEng.bin", "data/Origin/emoji.bin", "data/Origin/slang.bin"};

    loadData(fileName, true);
}

Word& Dictionary::getRandomWord()
{
    int data = random((int)0, (int)4);
    int id = random(0, (int)words[data].size() - 1);
    while(words[data][id].id == -1)
    {
        id = random(0, (int)words[data].size() - 1);
    }
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
    if ((int)validId[data].size() > 0)
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
        defTable[data].setCountSize(words[data].size());
    }
    for (int i = 0; i < (int)word.definition.size(); i++)
    {
        defTable[data].insert(word.definition[i], word.id);
    }
    if (word.isFavorite) addFavorite(data, word.id);

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
}

void Dictionary::removeDef(dataSet data, int id, int index)
{
    defTable[data].remove(words[data][id].definition[index], id);
    words[data][id].type.erase(words[data][id].type.begin() + index);
    words[data][id].definition.erase(words[data][id].definition.begin() + index);
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