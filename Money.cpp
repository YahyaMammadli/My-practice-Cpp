#include <iostream>

using namespace std;

class Money
{

private:

    int banknotes = 0;
    int cents = 0;

    void setBanknotes(int b) 
    {
        if (b < 0) 
        {
            throw invalid_argument("Banknotes cannot be negative");
        }
        banknotes = b;
    }

    void setCents(int c) 
    {
        if (c < 0) 
        {
            throw invalid_argument("Cents cannot be negative");
        }
        if (c >= 100) 
        {
            throw invalid_argument("Cents cannot be 100 or more");
        }
        cents = c;
    }

public:

    Money() {}

    Money(int b, int c)
    {
        setBanknotes(b);
        setCents(c);
    }



    void showInfo()
    {
        cout << banknotes << "." << (cents < 10 ? "0" : "") << cents << " $" << endl;
    }
   
    
    void setBanknotesPublic(int b) 
    {
        setBanknotes(b);
    }


    
    void setCentsPublic(int c) 
    {
        setCents(c);
    }



    
    int getBanknotes() const 
    {
        return this->banknotes;
    }


    int getCents() const
    {
        return this->banknotes;
    }





    Money operator+(const Money& other) 
    {
        auto totalBanknotes = this->banknotes + other.banknotes;
        auto totalCents = this->cents + other.cents;

        if (totalCents >= 100)
        {
            totalBanknotes += totalCents / 100;
            totalCents = totalCents % 100;
        }

        return Money(totalBanknotes, totalCents);
    
    }

    Money operator+(int banknotes) 
    {
        auto totalBanknotes = this->banknotes + banknotes;
        return Money(totalBanknotes, this->cents);
    }

    Money operator-(const Money& other) 
    {
        int totalCents1 = this->banknotes * 100 + this->cents;
        int totalCents2 = other.banknotes * 100 + other.cents;

        int resultCents = totalCents1 - totalCents2;

        if (resultCents < 0) 
        {
            return Money(0, 0);
        }

        return Money(resultCents / 100, resultCents % 100);
    }

    Money operator-(int banknotes) 
    {
        int totalCents = this->banknotes * 100 + this->cents;
        int subtractCents = banknotes * 100;

        int resultCents = totalCents - subtractCents;

        if (resultCents < 0)
        {
            return Money(0, 0);
        }

        return Money(resultCents / 100, resultCents % 100);
    }



    bool operator==(const Money& other) 
    {
        
        int a = this->banknotes * 100 + this->cents;
        
        int b = other.banknotes * 100 + other.cents;

        return a == b;
    
    }

    bool operator!=(const Money& other) 
    {
        return !(*this == other);
    }


    
    
    bool operator<(const Money& other) 
    {
        int a = this->banknotes * 100 + this->cents;
        int b = other.banknotes * 100 + other.cents;
        return a < b;
    }



    
    bool operator>(const Money& other) 
    {
        int a = this->banknotes * 100 + this->cents;
        int b = other.banknotes * 100 + other.cents;
        return a > b;
    }




};







Money operator-(int banknotes, const Money& money)
{
    int totalCents1 = banknotes * 100;
    int totalCents2 = money.getBanknotes() * 100 + money.getCents();

    int resultCents = totalCents1 - totalCents2;

    if (resultCents < 0)
    {
        return Money(0, 0);
    }

    return Money(resultCents / 100, resultCents % 100);
}






int main()
{

        Money m1(10, 75); 
        Money m2(5, 50);  

        cout << "m1 = "; m1.showInfo();
        
        cout << endl;
        cout << endl;





        cout << "m2 = "; m2.showInfo();

        cout << endl;
        cout << endl;


        
        Money m3 = m1 + m2;
        cout << "m1 + m2 = "; m3.showInfo();

        cout << endl;
        cout << endl;




        Money m4 = m1 - m2;
        cout << "m1 - m2 = "; m4.showInfo();

        cout << endl;
        cout << endl;


      
        m1.setBanknotesPublic(20);
        
        m1.setCentsPublic(30);

        cout << endl;
        cout << endl;


        m1.showInfo();




    return 0;


}