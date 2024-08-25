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
        if (table[e.first] == nullptr)
        {
            return;
        }
        else
        {
            Slot *temp = table[e.first];
            if (temp->value == e.second)
            {
                for (int i = 0; i < (int)temp->Ids.size(); i++)
                if (temp->Ids[i] == Id)
                {
                    swap(temp->Ids[i], temp->Ids.back());
                    temp->Ids.pop_back();
                    break;
                }
                if (temp->Ids.size() == 0)
                {
                    table[e.first] = temp->next;
                    temp->next = nullptr;
                    delete temp;
                }
            }
            else
            {
                while (temp->next != nullptr)
                {
                    if (temp->next->value == e.second)
                    {
                        for (int i = 0; i < (int)temp->next->Ids.size(); i++)
                        if (temp->next->Ids[i] == Id)
                        {
                            swap(temp->next->Ids[i], temp->next->Ids.back());
                            temp->next->Ids.pop_back();
                            break;
                        }
                        if (temp->next->Ids.size() == 0)
                        {
                            Slot *del = temp->next;
                            temp->next = temp->next->next;
                            del->next = nullptr;
                            delete del;
                        }
                        break;
                    }
                }
            }
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

    for (auto e : filter)
    for (auto id : e->Ids)
    {
        count[id]++;
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