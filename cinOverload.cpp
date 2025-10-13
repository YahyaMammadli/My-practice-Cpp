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
            state |= std::ios_base::failbit;
        
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
        
        state |= std::ios_base::failbit;
        
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




// I was curious about how the cin function works, but it turned out that cin is just an object of the istream class, which has 16 overloads of the ">>" operator 
// I wrote my own overload of "operator>>", but the compiler does not allow me to implement it due to a priority conflict and the error 'operator >>' is ambiguous 
// But the experience was interesting

int main()
{
    int number;


    if (std::cin >> number)
    {
        cout << "You type => " << number << endl;
    }



    else 
    {
        cout << "Erorr!!!" << endl;

        
        cin.clear();
    
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    
    }


    

    return 0;
}