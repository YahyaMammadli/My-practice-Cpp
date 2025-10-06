#include <iostream>

#include <string>

#include <iomanip>

#include <cstdio>

using namespace std;



template<class T>

class MyArray

{

private:

	T* arr = nullptr;

	int size = 0;

	bool isPositionValid(int posisiton) const

	{

		return (posisiton >= 0 && posisiton < size);

	}

public:

#pragma region Ctor and DCtor

	MyArray() {}

	~MyArray() { clear(); }

	MyArray(const MyArray& other)

	{

		size = other.size;

		if (size <= 0)

		{

			cout << "Source is empty\n\n";

			return;

		}

		if (arr != nullptr)

		{

			for (int i = 0; i < size; i++)

			{

				arr[i] = other.arr[i];

			}

		}

	}

#pragma endregion

	void pushBack(const T data)

	{

		T* newArray = new T[size + 1];

		for (int i = 0; i < size; i++)

		{

			newArray[i] = arr[i];

		}

		newArray[size] = data;

		delete[] arr;

		arr = newArray;

		size++;

		//Not neccessary

		newArray = nullptr;

	}

	void insert(const T data, const int position)

	{

		if (!isPositionValid(position))

		{

			cout << "Invalid position\n\n";

			return;

		}

		T* newArray = new T[size + 1];

		for (int i = 0; i < position; i++)

		{

			newArray[i] = arr[i];

		}

		newArray[position] = data;

		for (int i = position; i < size; i++)

		{

			newArray[i + 1] = arr[i];

		}

		delete[] arr;

		arr = newArray;

		size++;

		//Not neccessary

		newArray = nullptr;

	}

	void update(const T data, const int position)

	{

		if (!isPositionValid(position))

		{

			cout << "Invalid position\n\n";

			return;

		}

		arr[position] = data;

	}

	T get(const int position)  const

	{

		if (!isPositionValid(position))

		{

			cout << "Invalid position\n\n";

			return (-1); //❌ error here

		}

		return arr[position];

	}


	void removeAt(const int position)

	{

		if (!isPositionValid(position))

		{

			cout << "Invalid position\n\n";

			return;

		}

		T* newArray = new T[size - 1];

		for (int i = 0; i < position; i++)

		{

			newArray[i] = arr[i];

		}

		for (int i = position + 1; i < size; i++)

		{

			newArray[i - 1] = arr[i];

		}

		delete[] arr;

		arr = newArray;

		size--;

		

		newArray = nullptr;

	}

	void removeAll(T data)

	{

		int count = 0;

		for (int i = 0; i < size; i++)

		{

			if (arr[i] == data)

				count++;

		}

		T* newArray = new T[size - count];

		int j = 0;

		for (int i = 0; i < size; i++)

		{

			if (arr[i] != data)

			{

				newArray[j] = arr[i];

				j++;

			}

		}

		delete[] arr;

		arr = newArray;

		size -= count;

		

		newArray = nullptr;

	}

	int getSize()

	{

		return size;

	}

	int indexOf(const T data, int ofsset = 0)

	{

		for (int i = ofsset; i < size; i++)

		{

			if (arr[i] == data)

				return i;

		}

		return -1;

	}

	void clear()

	{

		delete[] arr;

		

		arr = nullptr;

		size = 0;

	}


};



class Student

{

private:

	string name = "N/A";

	MyArray<double> grades = MyArray<double>();


public:


	Student()

	{

		name = "N/A";

		grades = MyArray<double>();

	}


	void AddGrade(int grade)

	{

		grades.pushBack(grade);


	}


	int ArithmeticAverage()

	{

		int sum = 0;

		for (size_t i = 0; i < grades.getSize(); i++)

		{

			sum += grades.get(i);


		}

		return sum / grades.getSize();


	}


	void ShowInfo()

	{


	}



};



int main()
{



	return 0;

}
