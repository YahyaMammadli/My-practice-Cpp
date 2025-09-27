#include <iostream>
#include <string>

using namespace std;





class RandomUtils
{

public:

	RandomUtils()
	{

	}



#pragma region Random Value

	static int GetRandomInt(int min, int max)
	{
		int range = max - min + 1;
		return min + (rand() % range);
	}



	


	static double GetRandomDouble(double min, double max)
	{

		double randomValue = (double)rand() / RAND_MAX;					

		return min + randomValue * (max - min);


	}




#pragma endregion






	static void RollDice()
	{

		int diceValue = GetRandomInt(1, 6);
		cout << "\n\nDice \t" << diceValue << "=> \n\n";



		switch (diceValue)
		{

		case 1:
			cout << "+-------+" << endl;
			cout << "|       |" << endl;
			cout << "|   o   |" << endl;
			cout << "|       |" << endl;
			cout << "+-------+" << endl;
			break;

		case 2:
			cout << "+-------+" << endl;
			cout << "| o     |" << endl;
			cout << "|       |" << endl;
			cout << "|     o |" << endl;
			cout << "+-------+" << endl;
			break;

		case 3:
			cout << "+-------+" << endl;
			cout << "| o     |" << endl;
			cout << "|   o   |" << endl;
			cout << "|     o |" << endl;
			cout << "+-------+" << endl;
			break;

		case 4:
			cout << "+-------+" << endl;
			cout << "| o   o |" << endl;
			cout << "|       |" << endl;
			cout << "| o   o |" << endl;
			cout << "+-------+" << endl;
			break;

		case 5:
			cout << "+-------+" << endl;
			cout << "| o   o |" << endl;
			cout << "|   o   |" << endl;
			cout << "| o   o |" << endl;
			cout << "+-------+" << endl;
			break;

		case 6:
			cout << "+-------+" << endl;
			cout << "| o   o |" << endl;
			cout << "| o   o |" << endl;
			cout << "| o   o |" << endl;
			cout << "+-------+" << endl;
			break;
		}



	}




	static string FlipCoin()
	{

		int result = GetRandomInt(0, 1);


		if (result == 0)
		{

			return "Heads";

		}


		else
		{
			return "Tails";


		}


	}








};



int main()
{
	cout << RandomUtils::GetRandomInt(1, 100) << endl;

	RandomUtils::RollDice();

	cout << RandomUtils::GetRandomDouble(0, 10) << endl;
	
	cout << RandomUtils::FlipCoin() << endl;




	return 0;
}