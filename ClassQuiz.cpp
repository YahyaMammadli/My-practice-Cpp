#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;




enum difficultyLevel
{
	Easy = 1,
	Normal,
	Hard
};



class Question
{

public:

	string text;
	vector<string> answers;
	int correctAnswerIndex;
	double score;
	difficultyLevel diflvl;

	Question() {}


	Question(string t, vector<string> a, int c, double s, difficultyLevel d)
	{

		text = t;
		answers = a;
		correctAnswerIndex = c;
		score = s;
		diflvl = d;
	}





	void display() const
	{
	
		cout << text << endl;

		for (size_t i = 0; i < answers.size(); i++)
		{

			cout << answers[i];
		
		}

		cout << "Type answer (1- 4) => " << endl;
	
	}

	
	bool checkAnswer(int userAnswer) const
	{
		return userAnswer - 1 == correctAnswerIndex;
	}











};



class Quiz
{

private:
	vector<Question> questions;
	int correctAnswers;
	vector<int> wrongAnswers;
	double totalScore;

	double getMaxScore() const 
	{

		double maxScore = 0;

		for (const auto& q : questions)
		{

			maxScore += q.score;

		}

		return maxScore;

	}


public:

	Quiz() {}

	Quiz(vector<Question> q)
	{

		questions = q;

	}





	void AddQuestion(const Question& q)
	{

		questions.push_back(q);

	}



	void shuffleQuestions() 
	{
		random_device rd;
		mt19937 g(rd());
		shuffle(questions.begin(), questions.end(), g);
	}








	void run()
	{
		correctAnswers = 0;
		totalScore = 0;
		wrongAnswers.clear();

		cout << "\n\n===== Welcome to the hitory test =====\n\n";

		for (size_t i = 0; i < questions.size(); i++)
		{

			questions[i].display();

			int userAnswer;

			cin >> userAnswer;


			if (userAnswer < 1 || userAnswer > static_cast<int>(questions[i].answers.size()))
			{
				cout << "Wrong answer number! Try again! \n" << endl;
				i--;
				continue;

			}


			if (questions[i].checkAnswer(userAnswer))
			{
				correctAnswers++;
				totalScore += questions[i].score;
				cout << "Correct! + " << questions[i].score << "score" << endl;

			}


			else
			{

				wrongAnswers.push_back(i);
				cout << "Incorrec!" << endl;
			}


		}

		
		showStatistic();

	}


	void showStatistic()
	{

		cout << "\n\n======== Test Results ======" << endl;
		cout << "\nAll quetions => " << questions.size() << endl;
		cout << "\nCorrect answers => " << correctAnswers << endl;
		cout << "\nWrong answers => " << wrongAnswers.size() << endl;
		cout << "\nTotal score => " << totalScore << " from " << getMaxScore() << endl;



		if (!wrongAnswers.empty())
		{

			cout << "\n\n======= Correct answers ======\n" << endl;

			for (auto& questionIndex : wrongAnswers)
			{

				const Question& q = questions[questionIndex];
				cout << "\nQuestion => " << q.text;
				cout << "Correct answer => " << (q.correctAnswerIndex + 1);




				string difficulty;

				switch (q.diflvl)
				{
					case Easy: difficulty = "Easy"; break;
					case Normal: difficulty = "Normal"; break;
					case Hard: difficulty = "Hard"; break;


				}

				cout << "Difficulty => " << difficulty << ", score => " << q.score << endl;
				
			
			}



		}


		double percentage = (static_cast<double>(correctAnswers) / questions.size()) * 100;

		cout << "\nPercentage correct answers => " << percentage << "%" << endl;

		if (percentage >= 80)
		{
			cout << "Excelent result" << endl;
		}

		else if (percentage >= 60)
		{
			cout << "Good result" << endl;

		}

		else if (percentage >= 40)
		{
		
			cout << "Satisfactorily" << endl;

		}

		else
		{
			cout << "Need to repeat the material " << endl;

		}





	}



















};





int main()
{

	Question q1 = Question("1. Who was the first President of the United States?\n",
						  { "A. George Washington\n", "B. Abraham Lincoln\n", "C. Thomas Jefferson\n", "D. John Adams\n" }, 
						  0, 0.5, difficultyLevel::Easy);

	
	Question q2 = Question("\n\n2. In which year did World War II end?\n", 
						  { "A. 1943\n", "B. 1945\n", "C. 1946\n", "D. 1950\n" },
						  1, 1, difficultyLevel::Normal);

	
	Question q3 = Question("\n\n3. Which ancient civilization built the pyramids in Egypt?\n", 
						  { "A. Greeks\n","B. Romans\n","C. Ancient Egyptians\n","D. Mayans\n" }, 
						  2, 1.5, difficultyLevel::Hard);


	Question q4 = Question("\n\n4. Who was known as the \"Maid of Orléans\" during the Hundred Years War?\n",
						  {"A. Catherine de Medici\n", "B. Joan of Arc\n", "C. Marie Antoinette\n", "D. Eleanor of Aquitaine\n"},
						  1, 1, difficultyLevel::Normal);


	Question q5 = Question("\n\n5. What was the main cause of the French Revolution in 1789?\n",
						  { "A. Religious conflicts\n","B. Colonial expansion\n","C. Social inequality and financial crisis\n","D. Foreign invasion\n" },
						  2, 1.5, difficultyLevel::Hard);



	
	vector<Question> q = { q1,q2,q3,q4,q5 };

	
	
	
	

	Quiz quiz = Quiz(q);

	/*quiz.AddQuestion(q1);			//Both work
	quiz.AddQuestion(q2);
	quiz.AddQuestion(q3);
	quiz.AddQuestion(q4);
	quiz.AddQuestion(q5);*/



	quiz.shuffleQuestions();

	quiz.run();









	return 0;
}