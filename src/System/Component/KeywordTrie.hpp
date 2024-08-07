// #pragma once
// #include <iostream>
// #include <vector>
// #include "../src/DataStructure/Trie.hpp"
// using namespace std;

// struct KeywordNode
// {
//     int IdofWord;
//     KeywordNode *children[26];
//     KeywordNode() : IdofWord(-1);
//     ~KeywordNode();
// };

// class KeywordTrie 
// {
// private:
//     KeywordNode *root;
// public:
//     KeywordTrie();
//     ~KeywordTrie();
//     void insert(string keyword, int Id);
//     bool search(string keyword);
//     void remove(string keyword);
// };