#include <iostream>
#include <string>

using namespace std;



class Device 
{

protected:
    string brand;
    double price;

public:
    
    Device() = default; //Мне это сам VS посоветовал
    
    Device(const string& b, double p) : brand(b), price(p)
    {
        cout << "Device constructor called for " << brand << endl << endl;
    }

    
    ~Device()
    {
        cout << "\nevice deleted => " << brand << " (price => $" << price << ")\n" << endl;
    }

    
    void showInfo() 
    {
        cout << "Brand => " << brand << "\nprice => " << price << endl;
    }


};






class Smartphone : public Device
{

private:
    string cameraResolution;

public:
    
    Smartphone(const string& b, double p, const string& res) : Device(b, p), cameraResolution(res)
    {
        cout << "/nSmartphone constructor called for " << brand << endl << endl;
    }



    
    ~Smartphone() 
    {
        cout << "\nSmartphone deleted => " << brand << endl;
    }

    
    void showInfo() 
    {
        Device::showInfo(); 
        cout << "\nCamera = > " << cameraResolution << endl;
    }


};







class Tablet : public Device 
{

private:
    
    double screenSize;

public:
    
    Tablet(const string& b, double p, double size) : Device(b, p), screenSize(size) 
    {
        cout << "/nTablet constructor called for " << brand << endl;
    }


    ~Tablet() 
    {
        cout << "\nTablet deleted => " << brand << endl;
    }


    void showInfo()
    {
        Device::showInfo();
       
        cout << "\nScreen Size => " << screenSize << " inches" << endl;
    
    }

};



class Laptop : public Device
{

private:
  
    string processor;

public:
    
    Laptop(const string& b, double p, const string& proc) : Device(b, p), processor(proc)
    {
        cout << "\nLaptop constructor called for " << brand << endl;
    }



    ~Laptop() 
    {
        cout << "\nLaptop deleted => " << brand << endl;
    }

    
    void showInfo() 
    {
        Device::showInfo();
    
        cout << "\nProcessor => " << processor << endl;
    
    }


};



class TV : public Device
{

private:
    
    int screenSize;

public:
    
    TV(const string& b, double p, int size) : Device(b, p), screenSize(size) 
    {
        cout << "\nTV constructor called for " << brand << endl;
    }

    
    ~TV()
    {
        cout << "\nTV deleted => " << brand << endl;
    }

    
    void showInfo() 
    {
        Device::showInfo();
        cout << "\nScreen Size => " << screenSize << " inches" << endl;
    }

};




class IPhone : public Smartphone 
{

private:
    
    string iosVersion;
    
    bool faceID;

public:

    IPhone(const string& model, double p, const string& camera, const string& ios, bool faceId = true) : Smartphone("Apple", p, camera), iosVersion(ios), faceID(faceId)
    {
        
            cout << "\nIPhone constructor called for " << brand << " " << model << endl;
        
    }


    ~IPhone()
    {
        cout << "\nIPhone deleted" << endl;
    }


    void showInfo()
    {
        Smartphone::showInfo(); 
        cout << "\niOS Version => " << iosVersion << ", FaceID => " << (faceID ? "Yes" : "No") << endl;
    }

    
    void useFaceID()
    {

        if (faceID)
        {
            cout << "\nFace ID unlocked successfully!" << endl;
        }

        else 
        {
            cout << "\nFace ID not available on this model" << endl;
        }

    }

};




int main(void)
{

  
    
        
        Smartphone phone("Iphone 16", 699.99, "MP");

        phone.showInfo();

       
    

    
    
        
        Tablet tablet("iPad Air", 599.99, 10.9);
        tablet.showInfo();
        
    


    
       
        Laptop laptop("Dell XPS", 1299.99, "Intel Core i7");
        laptop.showInfo();
        
    

    
        cout << "--- Creating TV ---" << endl;
        TV tv("Sony Bravia", 899.99, 55);
        tv.showInfo();
        cout << endl;
    

    
        
        IPhone iphone("15 Pro", 999.99, "48MP", "iOS 17", true);
        iphone.showInfo();
        iphone.useFaceID();
        cout << endl;
    

   
    return 0;
}