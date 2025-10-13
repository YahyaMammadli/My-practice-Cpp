#include <iostream>

using namespace std;

class Complex 
{


private:
    double real;
    double imag;

public:

    Complex() : real(0), imag(0) {}


    Complex(double r, double i) : real(r), imag(i) {}


    double getReal() const { return real; }
    double getImag() const { return imag; }


    void setReal(double r) { real = r; }
    void setImag(double i) { imag = i; }


    Complex operator+(const Complex& other) const 
    {
        return Complex(real + other.real, imag + other.imag);
    }


    Complex operator-(const Complex& other) const 
    {
        return Complex(real - other.real, imag - other.imag);
    }


    Complex operator*(const Complex& other) const 
    {

        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }


    void print() const 
    {
        cout << real;
        
        if (imag >= 0) 
        {
            std::cout << " + " << imag << "i";
        }
        
        else 
        {
            std::cout << " - " << -imag << "i";
        }
    }
};


ostream& operator<<(std::ostream& os, const Complex& c) 
{
    os << c.getReal();
    
    double imag = c.getImag();
    
    if (imag >= 0) 
    {
        os << " + " << imag << "i";
    }

    else 
    {
        os << " - " << -imag << "i";
    }
    return os;
}

int main() 
{


    Complex a(2, 3);   
    Complex b(1, 4);   

    Complex c = a + b; 
    Complex d = a * b; 
    Complex e = a - b;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "a + b = " << c << endl;
    cout << "a * b = " << d << endl;
    cout << "a - b = " << e << endl;

    return 0;
}