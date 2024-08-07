// #include "KeyWordTrie.hpp"
// using namespace std;

// KeywordNode::KeywordNode() : IdofWord(-1);
// {
//     for (int i = 0; i < 26; i++)
//     {
//         children[i] = nullptr;
//     }
// }

//  KeywordNode::~KeywordNode() 
//  {
//     for (int i = 0; i < 26; i++)
//     {
//         if (children[i] != nullptr)
//         {
//             delete children[i];
//         }
//     }
// }

// KeywordTrie::KeywordTrie() 
// {
//     root = new KeywordNode();
// }

// KeywordTrie::~KeywordTrie() 
// {
//     delete root;
// }

// void KeywordTrie::insert(string keyword, int Id) 
// {
//     KeywordNode *temp = root;
//     for (int i = 0; i < keyword.size(); i++)
//     {
//         int index = keyword[i] - 'a';
//         if (temp->children[index] == nullptr)
//         {
//             temp->children[index] = new KeywordNode();
//         }
//         temp = temp->children[index];
//     }
//     temp->isEndOfWord = true;
//     temp->IdofWord = Id;
// }

// int KeywordTrie::search(string keyword) 
// {
//     KeywordNode *temp = root;
//     for (int i = 0; i < keyword.size(); i++)
//     {
//         int index = keyword[i] - 'a';
//         if (temp->children[index] == nullptr)
//         {
//             return -1;
//         }
//         temp = temp->children[index];
//     }
//     return temp->IdofWord;
// }

// void KeywordTrie::remove(string keyword) 
// {
//     KeywordNode *temp = root;
//     for (int i = 0; i < keyword.size(); i++)
//     {
//         int index = keyword[i] - 'a';
//         if (temp->children[index] == nullptr)
//         {
//             return;
//         }
//         temp = temp->children[index];
//     }
//     temp->isEndOfWord = false;
//     temp->IdofWord = -1;
// }