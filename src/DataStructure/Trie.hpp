#include <iostream>

struct trieNode
{
    trieNode *children[26];
    bool isEndOfWord;
    trieNode()
    {
        isEndOfWord = false;
        for (int i = 0; i < 26; i++)
        {
            children[i] = nullptr;
        }
    }
};
