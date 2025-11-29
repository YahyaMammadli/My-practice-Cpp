#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

istream& operator>>(istream& is, int& value)
{
    ios_base::iostate state = ios_base::goodbit;

    char ch;

    while (is.get(ch) && isspace(ch))
    {

    }

    if (!is.good())
    {
        if (is.eof())
        {
            state |= ios_base::eofbit;
        }
        state |= ios_base::failbit;
        is.setstate(state);
        return is;
    }

    bool negative = false;

    if (ch == '-')
    {
        negative = true;
        if (!is.get(ch))
        {
            state |= ios_base::failbit;
            is.setstate(state);
            return is;
        }
    }

    else if (ch == '+')
    {
        if (!is.get(ch))
        {
            state |= ios_base::failbit;
            is.setstate(state);
            return is;
        }
    }

    if (!isdigit(static_cast<unsigned char>(ch)))
    {
        is.putback(ch);
        if (negative)
        {
            is.putback('-');
        }
        state |= ios_base::failbit;
        is.setstate(state);
        return is;
    }

    long long result = 0;
    int digits_count = 0;

    do
    {
        int digit = ch - '0';

        if (result > (numeric_limits<int>::max() - digit) / 10)
        {
            state |= ios_base::failbit;
            is.setstate(state);
            return is;
        }

        result = result * 10 + digit;
        digits_count++;

    } while (is.get(ch) && isdigit(static_cast<unsigned char>(ch)));

    if (digits_count > 0)
    {
        if (is.good())
        {
            is.putback(ch);
        }

        if (negative)
        {
            result = -result;
        }

        if (result < numeric_limits<int>::min() || result > numeric_limits<int>::max())
        {
            state |= ios_base::failbit;
            is.setstate(state);
            return is;
        }

        value = static_cast<int>(result);
    }
    else
    {
        state |= ios_base::failbit;
        is.setstate(state);
    }

    return is;
}



class MyCin 
{

private:
    istream& input_stream;

public:

    MyCin(istream& is = cin) : input_stream(is) {}

    operator bool() const 
    {
        return static_cast<bool>(input_stream);
    }

    bool good() const { return input_stream.good(); }
    bool eof() const { return input_stream.eof(); }
    bool fail() const { return input_stream.fail(); }
    bool bad() const { return input_stream.bad(); }

    void clear(ios_base::iostate state = ios_base::goodbit) 
    {
        input_stream.clear(state);
    }

    MyCin& operator>>(int& value) 
    {
        ::operator>>(input_stream, value);
        return *this;
    }

    template<typename T>
    MyCin& operator>>(T& value) 
    {
        input_stream >> value;
        return *this;
    }
};

namespace my
{

    MyCin cin;
}

int main()
{
    int number;
    double d;
    string text;

    cout << "Enter any integer => ";
    if (my::cin >> number)
    {
        cout << "You typed integer => " << number << endl;
    }
    else
    {
        cout << "Error reading integer!" << endl;
        my::cin.clear();
        std:: cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    cout << "Enter a double => ";
    if (my::cin >> d)
    {
        cout << "You typed double => " << d << endl;
    }
    
    else
    {
        cout << "Error reading double!" << endl;
        my::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    
    cout << "Enter a string => ";
    
    if (my::cin >> text)
    {
        cout << "You typed string => " << text << endl;
    }
    
    else
    {
        cout << "Error reading string!" << endl;
        my::cin.clear();
    }

    int a, b;
    
    cout << "Enter two integers => ";

    
    my::cin.clear();
    
    if (my::cin >> a >> b)
    {
        cout << "You typed => " << a << " and " << b << endl;
    }
    else
    {
        cout << "Error reading integers!" << endl;
        my::cin.clear();
        std::cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}




