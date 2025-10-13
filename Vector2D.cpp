#include <iostream>

using namespace std;

class Vector2D 
{


private:
    double x;
    double y;



public:


    Vector2D() : x(0), y(0) {}
    Vector2D(double x_val, double y_val) : x(x_val), y(y_val) {}



    double getX() const { return x; }
    double getY() const { return y; }


    void setX(double x_val) { x = x_val; }
    void setY(double y_val) { y = y_val; }




    Vector2D operator+(const Vector2D& other) const 
    {
        return Vector2D(x + other.x, y + other.y);
    }



    Vector2D operator-(const Vector2D& other) const 
    {
        return Vector2D(x - other.x, y - other.y);
    }





    double operator*(const Vector2D& other) const 
    {
        return x * other.x + y * other.y;
    }




    Vector2D operator*(double scalar) const 
    {
        return Vector2D(x * scalar, y * scalar);
    }



    Vector2D operator/(double scalar) const 
    {
        if (scalar == 0)
        {
            throw invalid_argument("Division by zero");
        }

        return Vector2D(x / scalar, y / scalar);
    }



    bool operator==(const Vector2D& other) const
    {
        return x == other.x && y == other.y;
    }



    bool operator!=(const Vector2D& other) const 
    {
        return !(*this == other);
    }



    double length() const 
    {
        return sqrt(x * x + y * y);
    }



    Vector2D normalize() const
    {
        double len = length();
        
        if (len == 0) 
        {
            throw invalid_argument("Cannot normalize zero vector");
        }

        return Vector2D(x / len, y / len);
    }



    double lengthSquared() const
    {
        return x * x + y * y;
    }

    


    void print() const 
    {
        cout << "(" << x << ", " << y << ")";
    }



};




ostream& operator<<(ostream& os, const Vector2D& v) 
{
    os << "(" << v.getX() << ", " << v.getY() << ")";
    return os;
}





Vector2D operator*(double scalar, const Vector2D& v) 
{
    return v * scalar;
}





int main() 
{



    Vector2D v1(2, 3);
    Vector2D v2(1, -1);

    Vector2D v3 = v1 + v2;   
    Vector2D v4 = v1 - v2;   
    double dot = v1 * v2;    

    cout << "v1 = " << v1 << endl;
    cout << "v2 = " << v2 << endl;
    cout << "v1 + v2 = " << v3 << endl;
    cout << "v1 - v2 = " << v4 << endl;
    cout << "v1 * v2 = " << dot << endl;

   
 
    Vector2D v5 = v1 * 2.5;
    cout << "v1 * 2.5 = " << v5 << endl;

    
    Vector2D v6 = 3.0 * v1;
    cout << "3.0 * v1 = " << v6 << endl;

    
    Vector2D v7 = v1 / 2.0;
    cout << "v1 / 2.0 = " << v7 << endl;

    
    Vector2D v8(2, 3);
    cout << "v1 == v8: " << (v1 == v8) << endl;
    cout << "v1 == v2: " << (v1 == v2) << endl;
    cout << "v1 != v2: " << (v1 != v2) << endl;

   
    Vector2D v9(3, 4);
    Vector2D v10 = v9.normalize();
    cout << "v9 = " << v9 << endl;
    cout << v10 << endl;
    cout << v10.length() << endl;

    
    cout << v9.lengthSquared() << endl;



     
   

    return 0;
}