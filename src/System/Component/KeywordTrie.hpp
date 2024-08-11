#pragma once
#include <iostream>
#include <vector>
#include "../src/DataStructure/Trie.hpp"
#include <stack>
using namespace std;

const int limitPredict = 10;
const int limitLetter = 126;

struct KeywordNode
{
    int IdofWord;
    KeywordNode *children[limitLetter];
    KeywordNode();
    ~KeywordNode();
};

class KeywordTrie 
{
private:
    KeywordNode *root;
    void internalRemove(KeywordNode* &node, string& keyword, int index);
public:
    KeywordTrie();
    ~KeywordTrie();
    void insert(string& keyword, int Id);
    int search(string& keyword);
    void remove(string& keyword);
    vector<int> predict(string& keyword);
};