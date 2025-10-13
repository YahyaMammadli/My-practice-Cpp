#include <iostream>
#include <utility> 

using namespace std;

class Fraction
{


private:
    int numerator;
    int denominator;

    
    int gcd(int a, int b) const
    {
        a = abs(a);
        b = abs(b);
        while (b > 0)
        {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    void reduce()
    {
        int Gcd = gcd(numerator, denominator); 
        numerator /= Gcd;
        denominator /= Gcd;

        if (denominator < 0)
        {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:

    Fraction() : numerator(0), denominator(1) {}


    Fraction(int num, int den) : numerator(num), denominator(den)
    {
        if (denominator == 0)
        {
            throw invalid_argument("Denominator cannot be zero");
        }
        reduce();
    }



    int getNumerator() const { return numerator; }
    int getDenominator() const { return denominator; }

    
    
    Fraction operator+(const Fraction& other) const
    {
        int new_num = numerator * other.denominator + other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }

   
    
    Fraction operator-(const Fraction& other) const
    {
        int new_num = numerator * other.denominator - other.numerator * denominator;
        int new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }

    
    
    
    Fraction operator*(const Fraction& other) const
    {
        int new_num = numerator * other.numerator;
        int new_den = denominator * other.denominator;
        return Fraction(new_num, new_den);
    }

    
    
    
    Fraction operator/(const Fraction& other) const
    {
        if (other.numerator == 0)
        {
            throw invalid_argument("Division by zero");
        }

        int new_num = numerator * other.denominator;
        int new_den = denominator * other.numerator;
        return Fraction(new_num, new_den);
    }

    
    
    void print() const
    {
        cout << numerator;
        if (denominator != 1)
        {
            cout << "/" << denominator;
        }
    }



};

ostream& operator<<(ostream& os, const Fraction& f)
{
    os << f.getNumerator();
    if (f.getDenominator() != 1)
    {
        os << "/" << f.getDenominator();
    }
    return os;
}

int main()
{

    Fraction f1(1, 2);   
    Fraction f2(3, 4);   

    Fraction f3 = f1 + f2;
    Fraction f4 = f1 - f2;
    Fraction f5 = f1 * f2;
    Fraction f6 = f1 / f2;

    cout << "f1 = " << f1 << endl;
    cout << "f2 = " << f2 << endl;
    cout << "f1 + f2 = " << f3 << endl;
    cout << "f1 - f2 = " << f4 << endl;
    cout << "f1 * f2 = " << f5 << endl;
    cout << "f1 / f2 = " << f6 << endl;

    

    return 0;
}