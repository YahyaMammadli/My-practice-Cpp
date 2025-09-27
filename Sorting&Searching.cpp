#include <iostream>
using namespace std;



void bubbleSort(int arr[], int size, bool descending = false)
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





void selectionSortHalf(int arr[], int size) 
{
    int middle = size / 2;

    for (int i = 0; i < middle - 1; i++) 
    {
        int maxIndex = i;
        for (int j = i + 1; j < middle; j++) 
        {
            if (arr[j] > arr[maxIndex]) 
            {
                maxIndex = j;
            }
        }
        if (maxIndex != i) 
        {
            int temp = arr[i];
            arr[i] = arr[maxIndex];
            arr[maxIndex] = temp;
        }
    }

    for (int i = middle; i < size - 1; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j < size; j++) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }
        if (minIndex != i) 
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}





















void sortBubleNegativeElements(int arr[], int size)
{
    int leftNegativeIndex = -1;
    int rightNegativeIndex = -1;

    for (int i = 0; i < size; i++)
    {
        if (arr[i] < 0) 
        {
            leftNegativeIndex = i;
            break;
        }
    }

    for (int i = size - 1; i >= 0; i--) 
    {
        if (arr[i] < 0) 
        {
            rightNegativeIndex = i;
            break;
        }
    }

    

    cout << "Left negative index => " << leftNegativeIndex << arr[leftNegativeIndex] << endl;
    cout << "Right negative index => " << rightNegativeIndex <<  arr[rightNegativeIndex] << endl;

    int start = leftNegativeIndex + 1;
    int end = rightNegativeIndex - 1;
    int count = end - start + 1;

  


    for (int i = 0; i < count - 1; i++) 
    {
        for (int j = start; j <= end - i - 1; j++) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}




void sortBetweenNegativeElementsSelection(int arr[], int size) 
{
    int leftNegativeIndex = -1;
    int rightNegativeIndex = -1;

    for (int i = 0; i < size; i++) 
    {
        if (arr[i] < 0) 
        {
            if (leftNegativeIndex == -1) 
            {
                leftNegativeIndex = i;
            }
            rightNegativeIndex = i;
        }
    }

   

    cout << "Left negative index => " << leftNegativeIndex << endl;
    cout << "Right negative index => " << rightNegativeIndex << endl;

    int start = leftNegativeIndex + 1;
    int end = rightNegativeIndex - 1;

   

    for (int i = start; i <= end; i++) 
    {
        int minIndex = i;
        for (int j = i + 1; j <= end; j++) 
        {
            if (arr[j] < arr[minIndex]) 
            {
                minIndex = j;
            }
        }
        if (minIndex != i) 
        {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}















void printArray(int arr[], int size) 
{
    for (int i = 0; i < size; i++) 
    {
        cout << arr[i] << "\t";
    }
    
}


















int main()
{

    const int size = 10;

    int arr[size] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };


    cout << "Array => ";
    printArray(arr, size);

    bubbleSort(arr, size);
    cout << "Ascending => ";
    printArray(arr, size);

    bubbleSort(arr, size, true);
    cout << "Descending => ";
    printArray(arr, size);
    


    int arr[size] = { 64, 34, 25, 12, 22, 11, 90, 88, 76, 50 };
    

    cout << "Array => ";
    
    printArray(arr, size);
    
    selectionSortHalf(arr, size);
    
    cout << "Sorted aray => ";
    
    printArray(arr, size);

    


    

    int arr[size] = { 5, 10, -3, 8, 15, -7, 20, 12, -1, 9 };


    int arr[size] = { 15, 8, -5, 12, -10, 7, 20, -3, 9, -1 };

    cout << "Array => ";
    printArray(arr, size);
    
    cout << endl;

    sortBubleNegativeElements(arr, size);

    sortBetweenNegativeElementsSelection(arr, size);

    cout << "Sorted aray => ";
    printArray(arr, size);






	return 0;
}