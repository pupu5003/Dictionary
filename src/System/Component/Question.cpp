#include "Question.hpp"
#include <ctime>

PracticeQuestion::PracticeQuestion(bool type, std::string question, std::string a, std::string b, std::string c, std::string d, int correct) {
    this->type_askByWord = type;
    this->question = question;
    this->answer.push_back(a);
    this->answer.push_back(b);
    this->answer.push_back(c);
    this->answer.push_back(d);
    this->correctAnswer = correct;
}

PracticeQuestion generateQuestion(Dictionary& dictionary, dataSet data) {
    // srand(time(0));
    // int i = rand() % 2;
    // if (i) return PracticeQuestion(1, "Hello", "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    // "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    // "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    // "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    // 3);
    // else return PracticeQuestion(0, "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    // "hello", "hello", "hello", "hello", 
    // 2);
    
    srand(time(0));
    int type_askByWord = rand() % 2;
    vector<Word> words(4);
    for (int i = 0; i < 4; ++i)
        words[i] = dictionary.getRandomWord(data);
    int correctAnswer = rand() % 4;
    if (type_askByWord) return PracticeQuestion(1, words[correctAnswer].word, 
        words[0].definition[rand() % words[0].definition.size()], 
        words[1].definition[rand() % words[1].definition.size()],
        words[2].definition[rand() % words[2].definition.size()],
        words[3].definition[rand() % words[3].definition.size()],
        correctAnswer);
    else return PracticeQuestion(0, words[correctAnswer].definition[rand() % words[correctAnswer].definition.size()],
        words[0].word, words[1].word, words[2].word, words[3].word, correctAnswer);
}