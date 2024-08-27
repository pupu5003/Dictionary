#include "KeywordTrie.hpp"
using namespace std;

const int limitPredict = 10;



KeywordNode::KeywordNode()
{
    IdofWord = -1;
    for (int i = 0; i < limitLetter; i++)
    {
        children[i] = nullptr;
    }
}

 KeywordNode::~KeywordNode() 
 {
    for (int i = 0; i < limitLetter; i++)
    {
        if (children[i] != nullptr)
        {
            delete children[i];
        }
    }
}


KeywordTrie::KeywordTrie() 
{
    root = new KeywordNode();
}

KeywordTrie::~KeywordTrie() 
{
    delete root;
}

void KeywordTrie::insert(string& keyword, int Id) 
{
    KeywordNode *temp = root;
    for (int i = 0; i < keyword.size(); ++i)
    {
        int index = CodeHelper::getInstance().mapChar(keyword, i);
        // cout << codepoint << " " << index << endl;
        if (temp->children[index] == nullptr)
        {
            temp->children[index] = new KeywordNode();
        }
        temp = temp->children[index];
    }
    temp->IdofWord = Id;
}

int KeywordTrie::search(string& keyword) 
{
    KeywordNode *temp = root;
    for (int i = 0; i < keyword.size(); i++)
    {
        int index = CodeHelper::getInstance().mapChar(keyword, i);
        if (temp->children[index] == nullptr)
        {
            return -1;
        }
        temp = temp->children[index];
    }
    return temp->IdofWord;
}

void KeywordTrie::remove(string& keyword) 
{
    KeywordNode *temp = root;
    for (int i = 0; i < keyword.size(); ++i)
    {
        int index = CodeHelper::getInstance().mapChar(keyword, i);
        // cout << codepoint << " " << index << endl;
        if (temp->children[index] == nullptr)
        {
            return;
        }
        temp = temp->children[index];
    }
    temp->IdofWord = -1;
}

vector<int> KeywordTrie::predict(vector<int>& codePoints) 
{
    KeywordNode *temp = root;
    vector<int> result;
    for (int i = 0; i < codePoints.size(); i++)
    {
        int index = CodeHelper::getInstance().mapCodepoint(codePoints[i]);
        if (temp->children[index] == nullptr)
        {
            return result;
        }
        temp = temp->children[index];
    }
    stack<KeywordNode*> st;
    st.push(temp);
    while (!st.empty())
    {
        KeywordNode *current = st.top();
        st.pop();
        if (current->IdofWord != -1)
        {
            result.push_back(current->IdofWord);
        }
        if (result.size() == limitPredict)
        {
            break;
        }
        for (int i = 0; i < limitLetter; i++)
        {
            if (current->children[i] != nullptr)
            {
                st.push(current->children[i]);
            }
        }
    }
    return result;
}

void KeywordTrie::clear() 
{
    delete root;
    root = new KeywordNode();
}