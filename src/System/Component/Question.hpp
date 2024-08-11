#include <string>
#include <vector>
using namespace std;


struct PracticeQuestion {
    bool type_askByWord;        //1 for question by word, 0 for question by definition
    std::string question;
    std::vector<std::string> answer;
    int correctAnswer;

    PracticeQuestion() {
        type_askByWord = 1;
        correctAnswer = 0;
    }

    PracticeQuestion(bool type, std::string question, std::string a, std::string b, std::string c, std::string d, int correct);
};

PracticeQuestion generateQuestion();