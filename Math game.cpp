#include <iostream>
#include <cstdlib>
#include <ctime>
#include<limits>
#include <string>
using namespace std;

enum enLevel { Easy = 1 , Med = 2 , Hard = 3 , Mix = 4  };

enum enOperationType { Add = 1 , Sub = 2 , Mult = 3 ,Div = 4 , MixOp = 5   };


struct stQuiz {
    short numberOfquestions=0;
    short rightAnswers=0;
    short wrongAnswers=0;
    enLevel level;
    enOperationType operationType;
    bool finalResult;

};


struct stQuestion {
    short orderOfQuestion = 0;
    enLevel level;
    int number1 = 0;
    int number2 = 0;
    int correctAnswer = 0;
    int userAnswer = 0;
    enOperationType operationType;
    bool result;



};


bool AnotherRound() {


    char again;

    cout << "\nDo you want to play again? (Y/N) : ";
    cin >> again;

    do {


        if (again == 'y' || again == 'Y')
        {
            system("cls");
            return true;
        }

        else if (again == 'n' || again == 'N')
        {
            cout << "\nSee you in the next game :) " << endl;
            exit(0);
        }

        else
        {
            do {
                cout << "\nWrong choice, please choose (Y/N) : ";
                cin >> again;

            } while (again != 'y' && again != 'Y' && again != 'n' && again != 'N');

        }

    } while (true);


}


int RandomNumber(int from, int to) {

    return (rand() % (to - from + 1) + from);

}


enLevel ReadLevel() {
    short level;

    do
    {
        cout << "Enter questions level [1]Easy  [2]Med  [3]Hard  [4]Mix ? ";
        cin >> level;
    } while (level < 1 || level>4);

    return (enLevel)level;

}


enOperationType ReadOperationType() {

    short operationType;

    do
    {
        cout << "Enter operation type [1]Add  [2]Sub  [3]Mult  [4]Div  [5]Mix ? ";
        cin >> operationType;
    } while (operationType < 1 || operationType>5);

    return (enOperationType)operationType;


}


short ReadNumberOfQuestions() {

    short numberOfQuestions;
    cout << "Enter number of questions do you want to answer: ";
    cin >> numberOfQuestions;
    return numberOfQuestions;


}


int ReadUserAnswer() {

    int answer;
    cin >> answer;
    return answer;

}


int GenerateNumber(enLevel level){

    switch (level)
    {
    case Easy:
        return RandomNumber(1, 10);
    case Med:
        return RandomNumber(11, 50);
    case Hard:
        return RandomNumber(51, 100);

    }




}


string GetOperationSymbol(enOperationType operationType) {

    switch (operationType)
    {
    case Add:
        return "+ ";
    case Sub:
        return "-";

    case Mult:
        return "x";

    case Div:
        return "/";
    case MixOp:
        return "Mix";
    
    }


}


string GetLevelAsText(enLevel level) {

    switch(level)
    {
    case Easy:
        return "Easy";
    case Med:
        return "Med";
    case Hard:
        return "Hard";
    case Mix:
        return "Mix";
    
   
    
    }



}


void TurnColorOfScreen(bool result) {

    if (result) 
        system("color 2F");
    else 
    {
        cout << '\a';
        system("color 4F");
    }

}


int SimpleCalculator(int number1 , int number2 , enOperationType operationType) {

    switch (operationType)
    {
    case Add:
        return (number1 + number2);

    case Sub:
        return (number1 - number2);

    case Mult:
        return (number1 * number2);

    case Div:
        return (number1 / number2);

    }

}


void PrintOrderOfQuestion(short orderOfQuestion, short numberOfQuestions) {


    cout << "Question [" << orderOfQuestion << '/' << numberOfQuestions << "]\n\n";


}


void PrintQuestion(stQuestion question){


    cout << question.number1 << '\n';
    cout << '\t' << GetOperationSymbol(question.operationType) << '\n';
    cout << question.number2 << "\n\n";
    cout << "_______________________\n";


}


void Question(stQuestion &question,stQuiz quiz) {

   
        
        PrintOrderOfQuestion(question.orderOfQuestion, quiz.numberOfquestions);

        
        if (quiz.level == Mix)
            question.level = (enLevel)(RandomNumber(1, 3));

        
        if (quiz.operationType == MixOp)
            question.operationType = (enOperationType)RandomNumber(1, 4);

        question.number1 = GenerateNumber(question.level);
        question.number2 = GenerateNumber(question.level);

        PrintQuestion(question);
     
       question.userAnswer = ReadUserAnswer();
       question.correctAnswer = SimpleCalculator(question.number1, question.number2, question.operationType);
       question.result = (question.correctAnswer == question.userAnswer);
    


}


void PrintQuestionResult(stQuestion question, stQuiz &quiz){

    if (question.result)
    {
        TurnColorOfScreen(question.result);
        cout << "Right answer :-)\n\n\n";
        quiz.rightAnswers++;
    }
    else
    {
        TurnColorOfScreen(question.result);
        cout << "Wrong answer :-(\n";
        cout << "The right answer is " << question.correctAnswer<<"\n\n\n";
        quiz.wrongAnswers++;

    }


}


void PrintPassORFail(stQuiz quiz) {

    cout << "___________________________________________\n\n";
    if (quiz.finalResult)
    {
        cout << "The final result is pass :-)\n\n";
        TurnColorOfScreen(quiz.finalResult);

    }
    else
    {
        cout << "The final result is fail :-(\n\n";
        TurnColorOfScreen(quiz.finalResult);
  
    }



}


void PrintFinalResults(stQuiz quiz){



    PrintPassORFail(quiz);
    cout << "___________________________________________\n\n";
    cout << "Number of questions : " << quiz.numberOfquestions<<'\n';
    cout << "Questions level : " << GetLevelAsText (quiz.level) << '\n';
    cout << "Operation type : " << GetOperationSymbol( quiz.operationType) << '\n';
    cout << "Number of right answers : " << quiz.rightAnswers << '\n';
    cout << "Number of wrong answers : " << quiz.wrongAnswers << "\n\n";
    cout << "___________________________________________\n\n";





}


void Game(stQuiz &quiz, stQuestion &question) {


    for (short orderOfQuestion = 1; orderOfQuestion <= quiz.numberOfquestions; orderOfQuestion++)
    {
        question.orderOfQuestion = orderOfQuestion;
        Question(question, quiz);
        PrintQuestionResult(question,quiz);

    }

}


void StartGame() {

    stQuestion question;
    stQuiz quiz;
    do 
    {
    system("color 07");

    quiz.numberOfquestions = ReadNumberOfQuestions();
    quiz.level = question.level = ReadLevel();
    quiz.operationType = question.operationType = ReadOperationType();

    
        
        Game(quiz, question);

        quiz.finalResult = (quiz.rightAnswers >= quiz.wrongAnswers);
        PrintFinalResults(quiz);

    } while (AnotherRound());
}


int main()
{
    srand(time(0));
    StartGame();
    return 0; 
}

