#include "DefHashTable.hpp"
using namespace std;

const int limitPredict = 10;


Slot::Slot()
{
    next = nullptr;
}
Slot::~Slot()
{
    if (next != nullptr)
    {
        delete next;
    }
}

DefHashTable::DefHashTable()
{
    for (int i = 0; i < Size; i++)
    {
        table[i] = nullptr;
    }
}

DefHashTable::~DefHashTable()
{
    for (int i = 0; i < Size; i++)
    {
        if (table[i] != nullptr)
        {
            delete table[i];
        }
    }
}

pair<int, int> DefHashTable::hashFunction(string &def)
{
    int hash = 0;
    int value = 0;
    for (int i = 0; i < def.size(); i++)
    {
        int codepoint = utf8ToCodepoint(def, i);
        if (isSpecialSymbol(codepoint)) continue;
        int index = CodeHelper::getInstance().mapCodepoint(codepoint) + 1;
        hash = (hash * Base + index) % Size;
        value = (1ll * Base * value % MOD + index) % MOD;
    }
    
    return make_pair(hash, value);
}

vector<pair<int,int>> DefHashTable::splitnHash(string &def)
{
    vector<pair<int,int>> hashList;
    stringstream ss(def);
    while(ss.good())
    {
        string substr;
        getline(ss, substr, ' ');
        hashList.push_back(hashFunction(substr));
    }
    sort(hashList.begin(), hashList.end());
    hashList.resize(unique(hashList.begin(), hashList.end()) - hashList.begin());
    return hashList;
}

void DefHashTable::insert(string &def, int Id)
{
    vector<pair<int,int>> hashList = splitnHash(def);
    for (auto e : hashList)
    if (e.first != 0)
    {
        if (table[e.first] == nullptr)
        {
            table[e.first] = new Slot();
            table[e.first]->value = e.second;
            table[e.first]->Ids.push_back(Id);
        }
        else
        {
            bool flag = false;
            Slot *temp = table[e.first];
            while (temp->next != nullptr)
            {
                if (temp->value == e.second)
                {
                    temp->Ids.push_back(Id);
                    flag = true;
                    break;
                }
                temp = temp->next;
            }
            if (!flag)
            {
                temp->next = new Slot();
                temp->next->value = e.second;
                temp->next->Ids.push_back(Id);
            }
        }
    }
}

void DefHashTable::remove(string &def, int Id)
{
    vector<pair<int,int>> hashList = splitnHash(def);
    for (auto e : hashList)
    if (e.first != 0)
    {
        Slot *temp = table[e.first], *pre = nullptr;
        while(temp != nullptr)
        {
            if (temp->value == e.second)
            {
                auto it = find(temp->Ids.begin(), temp->Ids.end(), Id);
                if (it != temp->Ids.end())
                {
                    temp->Ids.erase(it);
                    if (temp->Ids.size() == 0)
                    {
                        if (pre != nullptr)
                        {
                            pre->next = temp->next;
                            delete temp;
                        }
                        else
                        {
                            delete temp;
                            table[e.first] = nullptr;
                        }
                    }
                }
                break;
            }
            temp = temp->next;
        }
    }
}
void DefHashTable::setCountSize(int size)
{
    count.assign(size, 0); 
}
vector<int> DefHashTable::predict(vector<int> &codePoints)
{
    int hash = 0;
    int value = 0;
    vector<pair<int, int>> codeList;
    for (int i = 0 ; i < codePoints.size(); i++)
    if (codePoints[i] == 32)
    {
        codeList.push_back(make_pair(hash, value));
        hash = 0;
        value = 0;
    }
    else if (!isSpecialSymbol(codePoints[i]))
    {
        int index = CodeHelper::getInstance().mapCodepoint(codePoints[i]) + 1;
        hash = (hash * Base + index) % Size;
        value = (1ll * Base * value % MOD + index) % MOD;
    }
    codeList.push_back(make_pair(hash, value));

    vector<int> res;
    vector<Slot*> filter;
    for (auto e : codeList)
    if (e.first != 0)
    {
        Slot *temp = table[e.first];
        bool flag = false;
        while (temp != nullptr)
        {
            if (temp->value == e.second)
            {
                filter.push_back(temp);
                flag = true;
                break;
            }
            temp = temp->next;
        }
        if (!flag)
        {
            return res;
        }
    }

    for (int i = 0; i < (int)filter.size(); i++)
    for (auto id : filter[i]->Ids)
    {
        if (count[id] < i + 1)
        {
            count[id]++;
        }
    }
    if (filter.size() == 0)
    {
        return res;
    }
    for (auto id : filter[0]->Ids)
    if (count[id] == (int)filter.size())
    {
        res.push_back(id);
        if (res.size() == limitPredict)
        {
            break;
        }
    }

    for (auto e : filter)
    for (auto id : e->Ids)
    {
        count[id] = 0;
    }
    
    return res;
}