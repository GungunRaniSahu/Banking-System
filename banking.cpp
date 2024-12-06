#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Base Class: Account
class Account 
{
protected:
    int accountNumber;
    string holderName;
    double balance;

public:
    Account(int accNo, string name, double initialBalance)
        : accountNumber(accNo), holderName(name), balance(initialBalance) {}

    virtual void deposit(double amount) 
    {
        balance += amount;
        cout << "Deposit successful! New Balance: " << balance << endl;
    }

    virtual void withdraw(double amount) 
    {
        if (amount <= balance) 
        {
            balance -= amount;
            cout << "Withdrawal successful! New Balance: " << balance << endl;
        } 
        
        else 
        {
            cout << ".....Insufficient funds!....." << endl;
        }
    }

    virtual void displayBalance() const 
    {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Holder Name: " << holderName << endl;
        cout << "Current Balance: " << balance << endl;
    }

    virtual ~Account() {}
};

// Derived Class: SavingsAccount
class SavingsAccount : public Account 
{
private:
    double interestRate;

public:
    SavingsAccount(int accNo, string name, double initialBalance, double rate)
        : Account(accNo, name, initialBalance), interestRate(rate) {}

    void calculateInterest() 
    {
        double interest = balance * interestRate / 100;
        balance += interest;
        cout << "Interest added! New Balance: " << balance << endl;
    }
};

// Derived Class: CurrentAccount
class CurrentAccount : public Account 
{
private:
    double overdraftLimit;

public:
    CurrentAccount(int accNo, string name, double initialBalance, double overdraft)
        : Account(accNo, name, initialBalance), overdraftLimit(overdraft) {}

    void withdraw(double amount) override 
    {
        if (amount <= balance + overdraftLimit) 
        {
            balance -= amount;
            cout << "Withdrawal successful! New Balance: " << balance << endl;
        }
         else 
        {
            cout << "Overdraft limit exceeded!" << endl;
        }
    }
};


int main() 
{
    vector<Account*> accounts; 
    int choice, accNo;
    string name;
    double amount, rate, overdraft;

    while (true) 
    {
        cout << "\nBanking System Menu:\n"
             << "1. Open Savings Account\n"
             << "2. Open Current Account\n"
             << "3. Deposit\n"
             << "4. Withdraw\n"
             << "5. Display Account\n"
             << "6. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) 
        {
        case 1: 
        {
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> amount;
            cout << "Enter Interest Rate: ";
            cin >> rate;
            accounts.push_back(new SavingsAccount(accNo, name, amount, rate));
            cout << ".....Savings Account created successfully!....." << endl;
            break;
        }

        case 2: 
        {
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Holder Name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> amount;
            cout << "Enter Overdraft Limit: ";
            cin >> overdraft;
            accounts.push_back(new CurrentAccount(accNo, name, amount, overdraft));
            cout << ".....Current Account created successfully!....." << endl;
            break;
        }

        case 3: 
        {
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Deposit Amount: ";
            cin >> amount;
            for (auto& acc : accounts) {
                if (acc->displayBalance(), accNo) 
                { 
                    acc->deposit(amount);
                    break;
                }
            }
            break;
        }

        case 4:
        {
            cout << "Enter Account Number: ";
            cin >> accNo;
            cout << "Enter Withdrawal Amount: ";
            cin >> amount;
            for (auto& acc : accounts) 
            {
                if (acc->displayBalance(), accNo) 
                { 
                    acc->withdraw(amount);
                    break;
                }
            }
            break;
        }

        case 5:
            for (auto& acc : accounts) 
            {
                acc->displayBalance();
            }
            
            break;

        case 6:
            for (auto& acc : accounts) delete acc;
            cout << "Exiting the system. Goodbye!" << endl;
            return 0;

        default:
            cout << "Invalid choice! Try again." << endl;
        }
    }
}
