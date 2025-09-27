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
void ReverseArray(T* arr, int size)
{
    int* start = arr;               
    int* end = arr + size - 1;      


    while (start < end) 
    {


        
        int temp = *start;
        *start = *end;    
        *end = temp;      

        
        start++;          
        end--;       


    }
}







template <typename T>
void CopyArray(T* arr1, T* arr2, int size) 
{

    int* parr1 = arr1;
    int* parr2 = arr2;


    for (size_t i = 0; i < size; i++) 
    {
        *parr2 = *parr1; 


        parr1++;
        parr2++;
    }
}





template <typename T>
void CopyArrayReverse(T* source, T* destination, int size)
{

    for (int i = 0; i < size; i++) 
    {

        *(destination + size - 1 - i) = *(source + i);

    }
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

    int* arr = new int[size];
    



    int* arr1 = new int[size];
    int* arr2 = new int[size];


    FillArray(arr1, size);
    

    FillArray(arr2, size);


    PrintArray(arr1, size);

    cout << endl;
    cout << endl;

    PrintArray(arr2, size);




    PrintArray(arr, size);


    cout << endl;
    cout << endl;



    ReverseArray(arr, size);
    PrintArray(arr, size);


    CopyArray(arr2, arr1, size);



    CopyArrayReverse(arr2, arr1, size);


    PrintArray(arr1, size);







    delete[] arr;
    arr = nullptr;
    delete[] arr2;
    delete[] arr1;
    arr1 = nullptr;
    arr2 = nullptr;







    return 0;
}