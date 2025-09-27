#include <iostream>
#include <ctime>
using namespace std;




template <typename T>
void FillArray(T* arr, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		arr[i] = 1 + rand() % 101;


	}
}


template <typename T>
void BubbleSortArray(T*& arr, const int size, bool descending = false)
{

	for (int i = 0; i < size - 1; i++)
	{
		for (int j = 0; j < size - i - 1; j++)
		{
			if (!descending)
			{
				if (arr[j] > arr[j + 1])
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
			else
			{
				if (arr[j] < arr[j + 1])
				{
					int temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
			}
		}
	}

}




template <typename T>
void ReverseArray(T* arr, const int size)
{

	

	for (size_t i = 0; i < size / 2; i++)
	{
		T temp = arr[i];
		arr[i] = arr[size - 1 - i];
		arr[size - 1 - i] = temp;
	}




}







template <typename T>
bool ValidIndex(int index, const T* arr, const int size)
{
    return index >= 0 && index < size;
}






template <typename T>
void InsertElement(T*& arr, int& size, int index, T value)
{
    if (index < 0 || index > size)
    {
		cout << "Error!!!";
		return -1;
    }

    T* newArr = new T[size + 1];

    for (int i = 0; i < index; i++)
    {
        newArr[i] = arr[i];
    }

    newArr[index] = value;

    for (int i = index; i < size; i++)
    {
        newArr[i + 1] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    size++;

}



















template <typename T>
void RemoveElement(T*& arr, int& size, int index)
{
    if (!ValidIndex(index, arr, size))
    {
		cout << "Error!!!";
        return -1;
    }

    T* newArr = new T[size - 1];

    for (int i = 0; i < index; i++)
    {
        newArr[i] = arr[i];
    }

    for (int i = index + 1; i < size; i++)
    {
        newArr[i - 1] = arr[i];
    }

    delete[] arr;
    arr = newArr;
    size--;

}













template <typename T>
void RemoveElementsByConditions(T*& arr, int& size, T K)
{

	int countToRemove = 0;


    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0 ||          
            (arr[i] % 2 == 0) ||   
            (arr[i] < K))          
        {
            countToRemove++;
        }
    }

    if (countToRemove == 0)
    {
        cout << "Error!!!";
        return -1;
    }

    T* newArr = new T[size - countToRemove];
    int newIndex = 0;

    for (int i = 0; i < size; i++)
    {
        
        if (!(arr[i] < 0 ||     
            (arr[i] % 2 == 0) ||
            (arr[i] < K)))      
        {
            newArr[newIndex] = arr[i];
            newIndex++;
        
		}
    
	
	}

    delete[] arr;
    arr = newArr;
    size = newIndex;

}














template <typename T>
void PrintArray(const T* arr, const int size)
{
	for (size_t i = 0; i < size; i++)
	{
		cout << arr[i] << " ";
	}
}





int main()
{



	srand(time(0));
	
	
	
	int size;

	cout << "Type array size => ";
	cin >> size;

	int* arr = new int[size] {};




	int K;
	cout << "Type target => ";
	cin >> K;








	FillArray(arr, size);

	PrintArray(arr, size);

	cout << endl;
	cout << endl;

	BubbleSortArray(arr, size);

	PrintArray(arr, size);

	cout << endl;
	cout << endl;



	ReverseArray(arr, size);

	PrintArray(arr, size);

	InsertElement(arr, size, 2, 999);

	PrintArray(arr, size);


	cout << endl;
	cout << endl;


	RemoveElement(arr, size, 3);
	PrintArray(arr, size);








	cout << endl;
	cout << endl;




	RemoveElementsByConditions(arr, size, K);

	PrintArray(arr, size);












	delete[] arr;

	arr = nullptr;

	return 0;
}