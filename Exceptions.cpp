#include <iostream>
#include <string>
#include <vector>

using namespace std;





class BankAccount
{

private:
    
    int id;
    string owner;
    double balance;



public:
    
    
    BankAccount(int id, string owner, double initialBalance)
    {
        if (owner.empty())
        {
            throw invalid_argument("Owner name cannot be empty");
        }

        if (initialBalance < 0)
        {
            throw invalid_argument("The opening balance cannot be negative");
        }

        this->id = id;

        
        this->owner = owner;
        
        this->balance = initialBalance;
    }

    void deposit(double amount)
    {
        if (amount <= 0)
        {
            throw invalid_argument("The deposit amount must be positive");
        }

        balance += amount;
        cout << "Successfully submitted " << amount << " to the account #" << id << endl;
    }

    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            throw invalid_argument("The withdrawal amount must be positive");
        }

        if (balance < amount)
        {
            throw runtime_error("Insufficient funds in the account");
        }

        balance -= amount;
        cout << "Successfully filmed " << amount << " from the account #" << id << endl;
    }

    void transfer(BankAccount& to, double amount)
    {
        cout << "Translation " << amount << " from the account #" << id << " to the account #" << to.id << endl;
        withdraw(amount);
        to.deposit(amount);
        cout << "Translation completed successfully" << endl;
    }

    double getBalance() const
    {
        return balance;
    }

    string getOwner() const
    {
        return owner;
    }

    int getId() const
    {
        return id;
    }

    void printInfo() const
    {
        cout << "Check #" << id << " | Owner => " << owner << " | Balance => " << balance << endl;
    }

};





class Bank
{
private:
    vector<BankAccount> accounts;
    int nextId;

public:
    Bank() : nextId(1) {}

    void createAccount(string owner, double initialBalance = 0)
    {
        if (owner.empty())
        {
            throw invalid_argument("Owner name cannot be empty");
        }

        if (initialBalance < 0)
        {
            throw invalid_argument("The opening balance cannot be negative");
        }

        BankAccount newAccount(nextId, owner, initialBalance);
        accounts.push_back(newAccount);
        cout << "New account created #" << nextId << " for " << owner << " with initial balance " << initialBalance << endl;
        nextId++;
    }

    BankAccount& findAccount(int id)
    {
        for (auto& account : accounts)
        {
            if (account.getId() == id)
            {
                return account;
            }
        }
        throw out_of_range("Account with ID " + to_string(id) + " not found");
    }

    void printAllAccounts()
    {
        if (accounts.empty())
        {
            cout << "There are no accounts in the bank" << endl;
            return;
        }

        cout << "\n=== ALL BANK ACCOUNTS ===" << endl;
        double totalBalance = 0;
        for (const auto& account : accounts)
        {
            account.printInfo();
            totalBalance += account.getBalance();
        }
        cout << "GENERAL BALANCE OF THE BANK => " << totalBalance << endl;
        cout << "==========================\n" << endl;
    }

    bool hasAccounts() const
    {
        return !accounts.empty();
    }
};


void displayMenu()
{
    cout << "\n=== BANK ACCOUNT MANAGEMENT SYSTEM ===" << endl;
    cout << "1. Create a new account" << endl;
    cout << "2. Deposit funds" << endl;
    cout << "3. Withdraw funds" << endl;
    cout << "4. Transfer funds" << endl;
    cout << "5. View account balance" << endl;
    cout << "6. Show all accounts" << endl;
    cout << "0. Exit" << endl;
    cout << "Select action => ";
}


double getAmountFromUser()
{
    double amount;
    cout << "Enter amount => ";
    cin >> amount;
    return amount;
}


int getAccountIdFromUser()
{
    int id;
    cout << "Enter account ID => ";
    cin >> id;
    return id;
}


string getOwnerNameFromUser()
{
    string owner;
    cout << "Enter owner's name => ";
    cin.ignore();
    getline(cin, owner);
    return owner;
}


int main()
{
    Bank bank;

    int choice;

    cout << "Welcome to the bank account management system!" << endl;

    do
    {
        try
        {
            displayMenu();
            cin >> choice;

            switch (choice)
            {
            case 1:
            {
                string owner = getOwnerNameFromUser();
                double initialBalance;
                cout << "Enter starting balance => ";
                cin >> initialBalance;
                bank.createAccount(owner, initialBalance);
                break;
            }

            case 2:
            {
                if (!bank.hasAccounts())
                {
                    cout << "There are no accounts in the bank. First create an account." << endl;
                    break;
                }
                int id = getAccountIdFromUser();
                double amount = getAmountFromUser();
                BankAccount& account = bank.findAccount(id);
                account.deposit(amount);
                break;
            }

            case 3:
            {
                if (!bank.hasAccounts())
                {
                    cout << "There are no accounts at the bank. Please create one first." << endl;
                    break;
                }
                int id = getAccountIdFromUser();
                double amount = getAmountFromUser();
                BankAccount& account = bank.findAccount(id);
                account.withdraw(amount);
                break;
            }

            case 4:
            {
                if (!bank.hasAccounts())
                {
                    cout << "There are no accounts at the bank. Please create one first." << endl;
                    break;
                }
                cout << "Sender's account => " << endl;
                
                int fromId = getAccountIdFromUser();
                
                cout << "Recipient's account => " << endl;
                
                int toId = getAccountIdFromUser();
                
                double amount = getAmountFromUser();
                
                BankAccount& fromAccount = bank.findAccount(fromId);
                
                BankAccount& toAccount = bank.findAccount(toId);
                
                fromAccount.transfer(toAccount, amount);
                
                break;
            
            }



            case 5:
            {
                if (!bank.hasAccounts())
                {
                    cout << "There are no accounts at the bank. Please create one first" << endl;
                    break;
                }
                int id = getAccountIdFromUser();
                BankAccount& account = bank.findAccount(id);
                cout << "Account balance #" << id << " (" << account.getOwner() << ") => " << account.getBalance() << endl;
                break;
            }

            case 6:
            {
                bank.printAllAccounts();
                break;
            }

            case 0:
            {
                cout << "Logging out. Goodbye!" << endl;
                break;
            }

            default:
            {
                cout << "Incorrect selection. Try again" << endl;
                break;
            }
            }
        }
        catch (const invalid_argument& e)
        {
            cout << "Error => " << e.what() << endl;
        }
        catch (const runtime_error& e)
        {
            cout << "Error => " << e.what() << endl;
        }
        catch (const out_of_range& e)
        {
            cout << "Error => " << e.what() << endl;
        }
        catch (const exception& e)
        {
            cout << "Unknown error: " << e.what() << endl;
        }

        if (cin.fail())
        {
            cin.clear();

            cin.ignore(10000, '\n');
            
            cout << "Input error! Please enter correct data" << endl;
        }

    } while (choice != 0);

    return 0;
}