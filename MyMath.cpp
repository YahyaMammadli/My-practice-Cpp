#include <iostream>
#include <vector>
#include <string>

using namespace std;


class MyMath
{


public:
	
	 static const double PI;
	
	 static const double E;




	 MyMath()
	 {
		 cout << "I workd" << endl;


	 }
	
		
	
	#pragma region Basic Operations


	static double Square(double x)
	{
		return x * x;
	}


	static double Cube(double x)
	{
		return x * x * x;
	}








	static double Power(double num, int exp)
	{
		if (exp == 0) 
		{
			return 1;
		}




		double result = 1;
		bool negativeExponent = exp < 0;
		int absoluteExp = exp;
	
		
		
		if (exp < 0)
		{
			absoluteExp = -exp;

		}

		for (int i = 0; i < absoluteExp; i++)
		{
			result *= num;
		
		}

		if (negativeExponent)
		{

			return 1 / result;
		}
		
		else
		{
			return result;

		}


	}













	static unsigned long long Factorial(int n) 
	{
		if (n < 0)
		{
			return -1;
		}


		if (n == 0 || n == 1)
		{
			return 1;
		}


		unsigned long long result = 1;
		
		for (int i = 2; i <= n; i++)
		{
			result *= i;
		}


		return result;
	}



#pragma endregion
	
	
	
	
	
	
	
	
	
	
	
	
	
	#pragma region Geometry of a circle

	static double getArea(double radius)
	{
		if (radius < 0)
		{
			return -1;

		}


		return PI * radius * radius;
	}








	static double CircleLength(double radius)
	{
		if (radius < 0)
		{
			return -1;

		}


		return 2 * PI * radius;
	}




#pragma endregion
	
	
	
	
	
	#pragma region Algorithmic methods


	static bool IsPrime(int n)
	{
		if (n <= 1)
		{
			return false;

		}
		
		if (n == 2)
		{

			return true;

		}
		
		
		if (n % 2 == 0)
		{
			return false;

		}



		for (int i = 3; i * i <= n; i += 2)
		{
			
			if (n % i == 0)
			{
				
				return false;			


			}
		
		}
		
		
		return true;

	}




	
	static int gcd(int a, int b)
	{
		int tempA = a;
		int tempB = b;


		if (tempA < 0)
		{

			tempA = -tempA;

		}
		
		
		if (tempB < 0)
		{
			
			tempB = -tempB;


		}

		
		
		
		while (tempB != 0) 
		{
		
			int temp = tempB;
			tempB = tempA % tempB;
			tempA = temp;
		
		}


		return tempA;
	
	
	}


#pragma endregion

};
const double MyMath::PI = 3.14;
const double MyMath::E = 2.71828;










int main()
{


	cout << "Pi => " << MyMath::PI << endl;

	cout << "E => " << MyMath::E << endl;
	
	cout << "5**2 = " << MyMath::Square(5) << endl;
	
	cout << "3**3 => " << MyMath::Cube(3) << endl;
	
	cout << "2**8 => " << MyMath::Power(2, 8) << endl;
	
	cout << "5! ==> " << MyMath::Factorial(5) << endl;
	
	cout << "Circle Length (r=3) => " << MyMath::CircleLength(3) << endl;
	
	cout << "Circle Area (r=3) => " << MyMath::getArea(3) << endl;
	
	cout << "17 Is Prime => " << (MyMath::IsPrime(17) ? "YES!" : "NOPE!") << endl;
	
	cout << "GCD(56, 98) => " << MyMath::gcd(56, 98);




	return 0;

}