#include "KeywordTrie.hpp"
using namespace std;

int mapChar[10000] = {0};

int utf8ToCodepoint(const std::string& utf8Str, int& index) {
    int codepoint = 0;
    unsigned char lead = utf8Str[index];
    
    if (lead < 0x80) {
        codepoint = lead;
    } else if ((lead >> 5) == 0x6) {
        codepoint = ((lead & 0x1F) << 6) | (utf8Str[index + 1] & 0x3F);
        index++;
    } else if ((lead >> 4) == 0xE) {
        codepoint = ((lead & 0x0F) << 12) | ((utf8Str[index + 1] & 0x3F) << 6) | (utf8Str[index + 2] & 0x3F);
        index += 2;
    } else if ((lead >> 3) == 0x1E) {
        codepoint = ((lead & 0x07) << 18) | ((utf8Str[index + 1] & 0x3F) << 12) | ((utf8Str[index + 2] & 0x3F) << 6) | (utf8Str[index + 3] & 0x3F);
        index += 3;
    }
    
    return codepoint;
}

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

void initMapChar()
{
    for (int i = 0; i < sizeof(VNCodePoints) / sizeof(int); i++)
    {
        mapChar[VNCodePoints[i]] = i;
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

        int codepoint = utf8ToCodepoint(keyword, i);
        // cout << getCode << endl;
        // if (mapChar[getCode] > limitLetter)
        // {
        //     cout << "Error:" <<i << " " << keyword <<  " " << getCode<< " " <<mapChar[getCode]  << endl;
        //     exit(0);
        // }
        int index = mapChar[codepoint];
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
        int index = mapChar[(int)keyword[i]];
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
    internalRemove(root, keyword, 0); 
}

void KeywordTrie::internalRemove(KeywordNode* &node, string& keyword, int index) 
{
    if (index == keyword.size())
    {
        delete node;
        node = nullptr;
        return;
    }
    int i = mapChar[(int)keyword[index]];
    if (node->children[i] == nullptr)
    {
        return;
    }
    internalRemove(node->children[i], keyword, index + 1);
    if (index == 0) return;
    for (int i = 0; i < limitLetter; i++)
    if (node->children[i] != nullptr)
    {
        return;
    }
    delete node;
    node = nullptr;
    return;
}

vector<int> KeywordTrie::predict(string& keyword) 
{
    KeywordNode *temp = root;
    vector<int> result;
    for (int i = 0; i < keyword.size(); i++)
    {
        int index = mapChar[(int)keyword[i]];
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