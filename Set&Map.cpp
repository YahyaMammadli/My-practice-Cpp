#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;





class Fine
{
public:
    string description = "N/A";
    double amount = 0;

	Fine() = default;

	Fine(const string& desc, double amt) : description(desc), amount(amt) 
	{

	}





};




class Owner
{
public:
    string licenseNumber = "N/A";
    string firstName = "N/A";
    string lastName = "N/A";
    string phone = "N/A";
    vector<Fine> fines;
	
	

    Owner() = default;
    
    Owner(const string& license, const string& fname, const string& lname, const string& ph) : licenseNumber(license), firstName(fname), lastName(lname), phone(ph)
    {


    }



    void addFine(const Fine& fine)
    {
        fines.push_back(fine);
    }






    void showInfo() const
    {
        cout << "Driver => " << firstName << " " << lastName << endl;
        cout << "License Number => " << licenseNumber << endl;
        cout << "Phone Number => " << phone << endl;
        cout << "Count of Fines => " << fines.size() << endl;

        if (!fines.empty())
        {
            cout << "Fines List => " << endl;
            
            double total = 0;

            for (size_t i = 0; i < fines.size(); ++i)
            {
                cout << "  " << (i + 1) << ". " << fines[i].description << " - $" << fines[i].amount << endl;

                total += fines[i].amount;
            }

            cout << "Total amount of fines => " << total << endl;
        }
        cout << "\n------------------------\n" << endl;
    }
	


};





class Car
{
public:
    string number = "N/A";
    string model = "N/A";
    string color = "N/A";
    Owner* owner = nullptr;
	

    Car() : owner(nullptr) {}

    Car(const string& num, const string& mod, const string& col, Owner* own) : number(num), model(mod), color(col), owner(own) 
    {

    }

    void showInfo() const
    {
        cout << "Car => " << model << endl;
        cout << "Number => " << number << endl;
        cout << "Color => " << color << endl;

        if (owner)
        {
            cout << "Oner => " << owner->firstName << " " << owner->lastName << " (" << owner->licenseNumber << ")" << endl;
        }

        else
        {
            cout << "Owner: not specified" << endl;
        }

        cout << "------------------------" << endl;


    }



};




class Application
{
private:
    map<string, Owner> owners;
    map<string, Car> cars;

public:
    void Run() 
    {
        int choice;
    
        do
        {
            showMenu();
            cout << "Select an item => ";
            cin >> choice;
            cin.ignore(); 

            switch (choice)
            {
                case 1: addOwner(); break;
                case 2: removeOwner(); break;
                case 3: findOwner(); break;
                case 4: addCar(); break;
                case 5: removeCar(); break;
                case 6: findCar(); break;
                case 7: issueFine(); break;
                case 0: cout << "Exit the program..." << endl; break;
                default: cout << "Wrong choice!" << endl;
            }
            
            cout << endl;

        } while (choice != 0);
    }

private:

    void showMenu() const 
    {
        cout << "\n====== Traffic Police BASE ======\n" << endl;
        cout << "1. Add Driver" << endl;
        cout << "2. Delete Driver" << endl;
        cout << "3. Search Driver" << endl;
        cout << "4. Add Car" << endl;
        cout << "5. Delete Car" << endl;
        cout << "6. Search Car" << endl;
        cout << "7. Issue a fine" << endl;
        cout << "0. Exit" << endl;
        cout << "\n------------------------\n" << endl;
    }

    
    void addOwner() 
    {
        string license, fname, lname, phone;

        cout << "Enter the license number => ";

        getline(cin, license);

        if (owners.find(license) != owners.end())
        {
            cout << "A driver with this license number already exists!" << endl;
            return;
        }

        cout << "Enter name => ";

        
        getline(cin, fname);
        
        cout << "Enter your last name => ";
        
        getline(cin, lname);
        
        cout << "Enter your phone number => ";
        
        getline(cin, phone);


        
        owners[license] = Owner(license, fname, lname, phone);
        
        cout << "Driver added successfully" << endl;
    
    }



    void removeOwner() 
    {
        string license;
    
        cout << "Enter your driver's license number to delete => ";

        getline(cin, license);

        auto it = owners.find(license);

        if (it != owners.end()) 
        {
            for (auto carIt = cars.begin(); carIt != cars.end();)
            {

                if (carIt->second.owner && carIt->second.owner->licenseNumber == license) 
                {
                    carIt = cars.erase(carIt);
                }

                else 
                {
                    ++carIt;
                }
            }
            

            owners.erase(it);

            cout << "The driver and his vehicles have been removed" << endl;
        
        }

        else
        {
            cout << "Driver not found!" << endl;
        }


    }

    void findOwner()
    {
        string license;

        
        cout << "Enter your license number to search => ";
        
        getline(cin, license);

        
        auto it = owners.find(license);
        
        if (it != owners.end())
        {
            it->second.showInfo();
        }
        
        else 
        {
            cout << "Driver not found!" << endl;
        }
    
    }




    void addCar() 
    {
        string number, model, color, ownerLicense;

        cout << "Enter car number => ";

        getline(cin, number);

        if (cars.find(number) != cars.end())
        {
            cout << "Car with this number already exists!" << endl;
            return;
        }

        cout << "Enter model => ";
        
        getline(cin, model);
        
        cout << "Enter color => ";
        
        getline(cin, color);
        
        cout << "Enter the owner's license number => ";
        
        getline(cin, ownerLicense);



        
        auto ownerIt = owners.find(ownerLicense);
        
        if (ownerIt != owners.end()) 
        {
            cars[number] = Car(number, model, color, &(ownerIt->second));

            cout << "Vehicle added successfully" << endl;
        }
        
        else 
        {
            cout << "Driver with this license number was not found!" << endl;
            cout << "Add a driver first!" << endl;
        }
    }




    void removeCar() 
    {
        string number;
        cout << "Enter the vehicle number to delete => ";
        
        getline(cin, number);

        auto it = cars.find(number);
        
        if (it != cars.end()) 
        {
            cars.erase(it);
            cout << "Car removed" << endl;
        }
        
        else 
        {
            cout << "Car not found!" << endl;
        }
    }

    void findCar() 
    {
        string number;

        cout << "Enter the vehicle number to search => ";
        
        getline(cin, number);

        auto it = cars.find(number);
        if (it != cars.end()) 
        {
            it->second.showInfo();
        }
        
        else 
        {
            cout << "Car not found!" << endl;
        }
    }

    void issueFine() 
    {
        string carNumber;
    
        cout << "Enter the vehicle number for the fine => ";
        
        getline(cin, carNumber);

        auto carIt = cars.find(carNumber);

        if (carIt == cars.end())
        {
            cout << "Car not found!" << endl;
            return;
        }

        if (!carIt->second.owner)
        {
            cout << "Car has no owner listed!" << endl;
            return;
        }

        string description;
        double amount;

        cout << "Enter the reason for the fine => ";
        getline(cin, description);
        cout << "Enter the fine amount => ";
        cin >> amount;
        cin.ignore();

        if (amount <= 0) 
        {
            cout << "The fine amount must be positive!" << endl;
            return;
        }

        carIt->second.owner->addFine(Fine(description, amount));
        cout << "The fine was successfully issued" << endl;
        cout << "Driver => " << carIt->second.owner->firstName << " " << carIt->second.owner->lastName << endl;
        cout << "Amount = >" << amount << endl;
    }


};





int main(void)
{

    Application app;
    
    app.Run();


    return 0;
}