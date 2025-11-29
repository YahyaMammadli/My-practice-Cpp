#include <iostream>
#include <limits>
#include <cctype>

using namespace std;

namespace my
{
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
}

int main()
{
    int number;

    cout << "Type anything => ";

    if (my::operator>>(std::cin, number))
    {
        cout << "\nYou typed => " << number << endl;
    }
    else
    {
        cout << "Error!!!" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}