#include <iostream>
using namespace std;

class Fraction 
{



private:
   
    int numerator;
    int denominator;

    int gcd(int a, int b)
    {
        while (b > 0) 
        {
            a %= b;
            swap(a, b);
        }
        return a;
    }





    void normalize() 
    {
        if (denominator == 0) 
        {
            denominator = 1;
        }

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }

        Simplify();
    }

public:
   
    
    
    Fraction() 
    {
        numerator = 0;
        denominator = 1;
    }

    Fraction(int num, int denom)
    {
        numerator = num;
        denominator = denom;
        normalize();
    }

    void Simplify() 
    {
        if (numerator == 0)
        {
            denominator = 1;
            return;
        }

        int commonDivisor = gcd(numerator, denominator);
        numerator /= commonDivisor;
        denominator /= commonDivisor;
    }

    Fraction Add(const Fraction& other) 
    {
        int newNumerator = numerator * other.denominator + other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction Subtract(const Fraction& other)
    {
        int newNumerator = numerator * other.denominator - other.numerator * denominator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }

    Fraction Multiply(const Fraction& other)
    {
        int newNumerator = numerator * other.numerator;
        int newDenominator = denominator * other.denominator;
        return Fraction(newNumerator, newDenominator);
    }



    Fraction Divide(const Fraction& other) 
    {

        int newNumerator = numerator * other.denominator;
        int newDenominator = denominator * other.numerator;
    
        
        
        return Fraction(newNumerator, newDenominator);
    }


    void Print() const 
    {
        cout << numerator << "/" << denominator << endl;
    }
};

int main() 
{




    
    Fraction a(1, 2);   
    
    Fraction b(3, 4);   

    
    Fraction c = a.Add(b);      
    
    Fraction d = a.Multiply(b); 
    
    Fraction e = a.Subtract(b); 
    
    Fraction f = a.Divide(b);   

    
    


    
    cout << "a = ";
    a.Print();
 


    cout << endl;
    cout << endl;


    cout << "b = "; 
    b.Print();
    





    cout << endl;
    cout << endl;




    cout << "a + b = "; 
    c.Print();
    


    cout << endl;
    cout << endl;




    cout << "a * b = "; 
    d.Print();
    



    cout << endl;
    cout << endl;



    cout << "a - b = "; 
    e.Print();
    


    cout << endl;
    cout << endl;







    cout << "a / b = "; 
    f.Print();


    cout << endl;
    cout << endl;



    Fraction g(6, 8);     
    cout << "6/8 simplified = "; 
    g.Print();


    cout << endl;
    cout << endl;



    Fraction h(3, -4);    
    cout << "3/-4 normalized = ";
    cout << "3/-4 normalized = ";
    h.Print();


    cout << endl;
    cout << endl;





    Fraction i(-2, -4);    
    cout << "-2/-4 normalized = "; 
    i.Print();





    cout << endl;
    cout << endl;



    Fraction j(4, 0);      
    cout << "4/0 corrected = "; 
    j.Print();



    return 0;
}