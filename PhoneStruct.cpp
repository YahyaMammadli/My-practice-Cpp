#include <iostream>
#include <string>

using namespace std;





struct phone
{
    string brand = "n/a";
    string model = "n/a";
    int price = 0;
    int yearofrelease = 0;
};

bool arephonesequal(const phone& p1, const phone& p2)
{
    return p1.brand == p2.brand && p1.model == p2.model &&
        p1.price == p2.price && p1.yearofrelease == p2.yearofrelease;
}

void showphoneinfo(const phone& ph)
{
    cout << "phone info:\n";
    cout << "brand: " << ph.brand << endl;
    cout << "model: " << ph.model << endl;
    cout << "price $: " << ph.price << endl;
    cout << "year of release: " << ph.yearofrelease << endl;
    cout << "-------------------\n";
}

phone findmostexpensive(const phone phones[], const int size)
{
    if (size == 0) {
        phone empty;
        return empty;
    }

    int maxIndex = 0;
    for (int i = 1; i < size; i++)
    {
        if (phones[i].price > phones[maxIndex].price)
        {
            maxIndex = i;
        }
    }
    return phones[maxIndex];
}



int main()
{


    cout << "\n === TEST 2: Phone comparison === \n";
    phone p1{ "apple", "iphone 4s", 1000, 2011 };
    phone p2 = p1;
    phone p3{ "sony", "ericsson t610", 200, 2003 };

    cout << "p1 == p2: " << arephonesequal(p1, p2) << endl;
    cout << "p1 == p3: " << arephonesequal(p1, p3) << endl;

    cout << "\n === TEST 3: Most expensive phone === \n";
    phone p4{ "apple", "iphone 4s", 1000, 2011 };
    phone p5{ "sony", "ericsson t610", 200, 2003 };
    phone p6{ "nokia", "3310", 180, 2000 };
    phone p7{ "apple", "iphone 17", 1029, 2025 };
    phone p8{ "samsung", "sh-100", 394, 1988 };

    const int phoneSize = 5;
    phone phones[phoneSize] = { p4, p5, p6, p7, p8 };

    phone expensive = findmostexpensive(phones, phoneSize);
    cout << "\n ===Most expensive phone=== \n";
    showphoneinfo(expensive);


    return 0;
}