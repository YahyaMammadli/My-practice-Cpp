#include <iostream>
#include <string>
#include <iomanip>
using namespace std;





struct Book
{

    string title;
    string author;
    float price;
    int year;



};




bool IsValidEnglishText(const string& text)
{

    for (char c : text)
    {

        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || c == '\'' || c == '-'))
        {

            return false;
        }
    }

    return !text.empty();


}



bool IsValidYear(int year)
{
    return year >= 0 && year <= 2025;


}





bool IsValidPrice(float price)
{
    return price > 0 && price < 2147483647;


}




string GetValidEnglishText(const string& prompt)
{
    string input;


    while (true)
    {
        cout << prompt;
        getline(cin, input);

        if (IsValidEnglishText(input))
        {
            return input;

        }


        else
        {
            cout << "Invalid syntax! Use only English letters, spaces, apostrophes and hyphens\n";

        }



    }



}














int GetValidYear()
{
    int year;
    while (true)
    {
        cout << "Enter publication year => ";




        if (!(cin >> year))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid year\n";
        }

        else if (IsValidYear(year))
        {
            cin.ignore(10000, '\n');
            return year;
        }

        else
        {
            cout << "Invalid year! Please enter a year between 0 and 2025\n";


        }


    }



}














float GetValidPrice()
{
    float price;
    while (true)
    {
        cout << "Enter book price => ";

        if (!(cin >> price))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a valid price\n";
        }

        else if (IsValidPrice(price))
        {
            cin.ignore(10000, '\n');
            return price;
        }


        else
        {
            cout << "Invalid price! Please enter a positive price\n";
        }
    }
}















void AddBook(Book*& arr, int& size, const Book& newBook)
{


    Book* newArr = new Book[size + 1];



    for (int i = 0; i < size; i++)
    {

        newArr[i] = arr[i];

    }



    newArr[size] = newBook;



    if (size > 0)
    {

        delete[] arr;

    }




    arr = newArr;
    size++;



}









void PrintBooks(const Book arr[], const int size)
{


    if (size == 0)
    {
        cout << "No books in the store!\n";
        return;
    }


    cout << "\n============================================= ALL BOOKS LIST ===============================\n";
    for (int i = 0; i < size; i++)
    {
        cout << "\n\n--------------------\n\n";

        cout << "# " << i + 1 << endl;
        cout
            << "Title => \t" << arr[i].title << endl
            << "Author => \t" << arr[i].author << endl
            << "Year => \t" << arr[i].year << endl
            << "Price => \t" << fixed << setprecision(2) << arr[i].price << " dollar";

        cout << "\n\n--------------------\n\n";
    }


    cout << endl;
    cout << endl;

    cout << "===================================================================\n\n";


}



















void FindBooksByAuthor(const Book arr[], const int size, const string& author)
{
    bool found = false;
    cout << "\n=========================== SEARCH RESULTS FOR AUTHOR " << author << " =============\n";

    for (int i = 0; i < size; i++)
    {
        if (arr[i].author.find(author) != string::npos)
        {
            cout << "\nTitle => \t" << arr[i].title
                << "\nAuthor => \t" << arr[i].author
                << "\nYear => \t" << arr[i].year
                << "\nPrice => \t" << fixed << setprecision(2) << arr[i].price << " dollar \n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "Books by author " << author << " not found\n";
    }

    cout << endl;
    cout << endl;
    cout << "=================================================================================\n\n";
}













void SortBooksByYear(Book arr[], int size, bool ascending = true)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            bool needSwap = ascending ?
                (arr[j].year > arr[j + 1].year) :
                (arr[j].year < arr[j + 1].year);

            if (needSwap)
            {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }




        }






    }

    cout << endl;
    cout << endl;


    cout << "Books sorted by year (" << (ascending ? "ascending" : "descending") << ")\n";


}











void SortBooksByPrice(Book arr[], int size, bool ascending = true)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            bool needSwap = ascending ?
                (arr[j].price > arr[j + 1].price) :
                (arr[j].price < arr[j + 1].price);

            if (needSwap)
            {
                Book temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;

            }

        }


    }


    cout << endl;
    cout << endl;

    cout << "Books sorted by price (" << (ascending ? "ascending" : "descending") << ")\n";



}





















void ApplyDiscount(Book& book, float discount)
{
    if (discount <= 0 || discount > book.price)
    {
        cout << "\nInvalid discount!!!\n";
        return;
    }



    book.price -= discount;
    cout << "\n\nDiscount " << fixed << setprecision(2) << discount << " applied. New price => " << fixed << setprecision(2) << book.price << " dollar\n";
}










void RemoveBook(Book*& arr, int& size, int index)
{





    if (index < 0 || index >= size)
    {

        cout << "Invalid book index!!!\n";


        return;
    }

    Book* newArr = new Book[size - 1];

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



    cout << "Book removed! \n";
}











Book InputBook()
{
    Book newBook;


    cout << "\n=============== ADD NEW BOOK ==============\n";

    newBook.title = GetValidEnglishText("Enter book title => ");
    newBook.author = GetValidEnglishText("Enter book author => ");
    newBook.year = GetValidYear();
    newBook.price = GetValidPrice();






    return newBook;


}










void ShowMenu()
{


    cout << "\n======================= BOOK STORE =======================================\n";

    cout << "1. Add book\n";

    cout << "2. Show all books\n";

    cout << "3. Find books by author\n";

    cout << "4. Sort books\n";

    cout << "5. Apply discount\n";

    cout << "6. Remove book\n";

    cout << "0. Exit\n";

    cout << "\nChoose action => ";

}












void ShowSortMenu()
{

    cout << "\n====================================== SORT BOOKS ===========================\n";

    cout << "1. By year (ascending) \n";

    cout << "2. By year (descending) \n";

    cout << "3. By price (ascending)\n";

    cout << "4. By price (descending)\n";

    cout << "0. Back\n";

    cout << "\nChoose sorting option => ";


}











int main()
{


    Book* books = nullptr;

    int size = 0;

    int choice;




    Book book1 = { "C for Dummies", "Dan Gookin", 100.5, 1994 };

    Book book2 = { "C++ for Dummies", "Stephen Randy Davis", 170, 1996 };

    Book book3 = { "Algorithms For Dummies", "John Mueller and Luca Massaron", 1009, 2017 };




    AddBook(books, size, book1);
    AddBook(books, size, book2);
    AddBook(books, size, book3);

    do
    {
        ShowMenu();
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input! Please enter a number\n";
            continue;
        }




        switch (choice)
        {

        case 1:
        {

            cin.ignore();
            Book newBook = InputBook();
            AddBook(books, size, newBook);
            cout << "\nNew Book was added!!! \n";
            break;

        }



        case 2:
        {
            PrintBooks(books, size);
            break;
        }

        case 3:
        {
            string author;
            cout << "Enter author name to search => ";
            cin.ignore();
            getline(cin, author);
            FindBooksByAuthor(books, size, author);
            break;
        }

        case 4:
        {
            int sortChoice;
            ShowSortMenu();
            if (!(cin >> sortChoice))
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input!\n";
                break;
            }

            switch (sortChoice)
            {


            case 1:
            {

                SortBooksByYear(books, size, true);

                break;

            }

            case 2:
            {
                SortBooksByYear(books, size, false);
                break;
            }

            case 3:
            {
                SortBooksByPrice(books, size, true);
                break;
            }

            case 4:
            {
                SortBooksByPrice(books, size, false);

                break;
            }

            case 0:
            {
                break;
            }



            default:
            {
                cout << "Invalid choice!!!\n";

            }


            }


            break;
        }

        case 5:
        {



            if (size == 0)
            {
                cout << "No books in the store\n";
                break;

            }

            PrintBooks(books, size);

            int index;


            float percent;

            cout << "Enter book number for discount => ";







            if (!(cin >> index) || index < 1 || index > size)
            {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid book number!\n";

                break;
            }


            cout << "Enter discount percentage => ";


            if (!(cin >> percent))
            {


                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid input!\n";

                break;


            }




            ApplyDiscount(books[index - 1], percent);

            break;



        }

        case 6:
        {


            if (size == 0)
            {
                cout << "No books in the store\n";
                break;
            }

            PrintBooks(books, size);

            int index;

            cout << "Enter book number to remove => ";

            if (!(cin >> index) || index < 1 || index > size)
            {


                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Invalid book number!!!\n";
                break;


            }

            RemoveBook(books, size, index - 1);


            break;


        }

        case 0:
        {
            cout << "Goodbye👋\n";
            break;
        }

        default:
        {
            cout << "Invalid choice! Try again => \n";
        }


        }




    } while (choice != 0);






    if (size > 0)
    {
        delete[] books;
    }










    return 0;

}