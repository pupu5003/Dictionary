#pragma once
#include <iostream>
#include <vector>
#include <raylib.h>
#include "../src/DataStructure/Trie.hpp"
#include <stack>
#include "FontHelper.hpp"
#include "../src/System/State/TextHandle.hpp"
// #include "Dictionary.hpp"
using namespace std;

const int limitPredict = 10;
const int limitLetter = 262;

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
public:
    KeywordTrie();
    ~KeywordTrie();
    void insert(string& keyword, int Id);
    int search(string& keyword);
    void remove(string& keyword);
    vector<int> predict(vector<int>& codePoints);
};