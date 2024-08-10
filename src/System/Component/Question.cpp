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

PracticeQuestion generateQuestion() {
    srand(time(0));
    int i = rand() % 2;
    if (i) return PracticeQuestion(1, "Hello", "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    3);
    else return PracticeQuestion(0, "said to someone who has just said or done something stupid, especially something that shows they are not noticing what is happening", 
    "hello", "hello", "hello", "hello", 
    2);
}