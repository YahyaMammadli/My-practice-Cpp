#include <iostream>
using namespace std;





class MyString
{


private:
    char* str;
    int size;



public:
    MyString() : str(nullptr), size(0)
    {
        cout << "Default constructor => ''" << endl;
    }

    MyString(const char* text)
    {
        if (text)
        {
            size = 0;
            while (text[size] != '\0') size++;

            str = new char[size + 1];
            for (int i = 0; i <= size; i++)
            {
                str[i] = text[i];
            }
        }
        else
        {
            str = nullptr;
            size = 0;
        }
        cout << "Constructor => '" << (str ? str : "") << "'" << endl;
    }

    ~MyString()
    {
        cout << "Destructor => '" << (str ? str : "") << "'" << endl;
        delete[] str;
    }

    MyString(const MyString& other)
    {
        if (other.str)
        {
            size = other.size + 1;
            str = new char[size];
            for (int i = 0; i <= size; i++)
            {
                str[i] = other.str[i];
            }
        }
        else
        {
            str = nullptr;
            size = 0;
        }
        cout << "Copy constructor => '" << (str ? str : "") << "'" << endl;
    }

    void concat(const char* text)
    {
        cout << "concat(\"" << text << "\") called on => '" << (str ? str : "") << "'" << endl;

        if (!text) return;

        int textLen = 0;
        while (text[textLen] != '\0') textLen++;

        int newSize = size + textLen;
        char* newStr = new char[newSize + 1];

        if (str)
        {
            for (int i = 0; i < size; i++)
            {
                newStr[i] = str[i];
            }
        }

        for (int i = 0; i < textLen; i++)
        {
            newStr[size + i] = text[i];
        }

        newStr[newSize] = '\0';

        delete[] str;
        str = newStr;
        size = newSize;

        cout << "After concat => '" << str << "'" << endl;
    }

    void concat(MyString text)
    {
        cout << "concat(MyString) called on => '" << (str ? str : "") << "' with => '" << text.getString() << "'" << endl;
        concat(text.str);
    }

    void replace(const char* text)
    {
        cout << "replace(\"" << text << "\") called on => '" << (str ? str : "") << "'" << endl;

        if (!text) return;

        delete[] str;

        int textLen = 0;
        while (text[textLen] != '\0') textLen++;

        size = textLen;
        str = new char[size + 1];

        for (int i = 0; i <= size; i++)
        {
            str[i] = text[i];
        }

        cout << "After replace => '" << str << "'" << endl;
    }

    void replace(MyString text)
    {
        cout << "replace(MyString) called on => '" << (str ? str : "") << "' with => '" << text.getString() << "'" << endl;
        replace(text.str);
    }

    int compare(const char* text)
    {
        cout << "compare(\"" << text << "\") called on => '" << (str ? str : "") << "'" << endl;

        if (!str && !text) return 0;
        if (!str) return -1;
        if (!text) return 1;

        int i = 0;
        while (str[i] != '\0' && text[i] != '\0')
        {
            if (str[i] < text[i]) return -1;
            if (str[i] > text[i]) return 1;
            i++;
        }

        if (str[i] == '\0' && text[i] == '\0') return 0;
        if (str[i] == '\0') return -1;
        return 1;
    }

    int compare(MyString text)
    {
        cout << "compare(MyString) called on => '" << (str ? str : "") << "' with => '" << text.getString() << "'" << endl;
        return compare(text.str);
    }

    int getSize()
    {
        return size;
    }

    const char* getString()
    {
        return str ? str : "";
    }
};









int main() 
{

    cout << "======== Testing MyString class =========" << endl;

    cout << endl;
    cout << endl;


    cout << "\n1. Testing concat with const char*" << endl;
    MyString s1("Hello");
    s1.concat(" World");

    cout << endl;
    cout << endl;



    cout << "\n2. Testing concat with MyString" << endl;
    MyString s2("Hello");
    MyString s3(" MyString");
    s2.concat(s3);

    cout << endl;
    cout << endl;



    cout << "\n3. Testing replace with const char*" << endl;
    MyString s4("Hello");
    s4.replace("Salam");

    cout << endl;
    cout << endl;


    cout << "\n4. Testing replace with MyString" << endl;
    MyString s5("OldString");
    MyString s6("NewString");
    s5.replace(s6);


    cout << endl;
    cout << endl;


    cout << "\n5. Testing compare with const char*" << endl;
    MyString s7("A");
    MyString s8("B");


    cout << endl;
    cout << endl;


    cout << "Result: " << s7.compare("B") << endl;
    cout << endl;

    
    cout << "Result: " << s8.compare("A") << endl;

    cout << endl;



    cout << "Result: " << s7.compare("A") << endl;

    cout << endl;


    cout << "\n6. Testing compare with MyString" << endl;
    MyString s9("Apple");
    MyString s10("Banana");
    
    cout << endl;

    cout << "Result: " << s9.compare(s10) << endl;
    cout << endl;

    
    cout << "Result: " << s10.compare(s9) << endl;

    cout << endl;

    cout << "Result: " << s9.compare(s9) << endl;

    cout << "\n7. Complex example" << endl;
    MyString complex("Start");
    complex.concat(" Middle");
    
    cout << endl;

    
    complex.replace("Replaced");
    
    cout << endl;

    complex.concat(" End");





    return 0;



}