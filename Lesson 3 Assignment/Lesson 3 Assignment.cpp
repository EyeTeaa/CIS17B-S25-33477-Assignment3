// Lesson 3 Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std; 


#include <memory>
#include <stdexcept>
#include <string>

// TODO: Define custom exception classes here
// - NegativeDepositException (for negative deposit attempts)
class NegativeDepositException : public std::exception
{
private:
    std::string message = "Negative Deposit Exception: ";
public: 
    NegativeDepositException(const std::string &msg = "")
    {
        this->message += msg; 
    }
    const char* what() const override
    {
        return (this->message).c_str(); 
    }
};
// - OverdrawException (for withdrawing more than the balance)
class OverdrawException : public std::exception
{
private: 
    std::string message = "Overdraw Exception: "; 
public: 
    OverdrawException(const std::string& msg = "")
    {
        this->message += msg; 
    }
    const char* what() const override 
    {
        return (this->message).c_str(); 
    }
};
// - InvalidAccountOperationException (for transactions on a closed account)
class InvalidAccountOperationException : public std::exception
{
private:
    std::string message = "Invalid Account Operation Exception: "; 
public: 
    InvalidAccountOperationException(const std::string& msg = "")
    {
        this->message += msg; 
    }
    const char* what() const override
    {
        return (this->message).c_str(); 
    }
};

class BankAccount {
private:
    std::string accountNumber;
    double balance;
    bool isActive;

public:
    // Constructor to initialize account number, balance, and active status
    BankAccount(std::string accNum, double initialBalance) : accountNumber(accNum), balance(initialBalance), isActive(true) {}

    // Deposit method
    void deposit(double amount) {
        // TODO: Implement exception handling for negative deposits
        if (amount < 0)
        {
            throw NegativeDepositException("cannot deposit: "  + std::to_string(amount));
        }
        else if (!isActive)
        {
            throw InvalidAccountOperationException("cannot deposit from a closed account");
        }
        else
        {
            balance += amount;
        }
    }

    // Withdraw method
    void withdraw(double amount) {
        // TODO: Implement exception handling for overdrawing and closed accounts
        if (!isActive)
        {
            throw InvalidAccountOperationException("cannnot withdraw from closed account");
        }
        else if (balance < amount || amount < 0 )
        {
            throw OverdrawException("cannot withdraw: " + std::to_string(amount) + 
                " because balance is " + std::to_string(balance));
        }
        else
        {
            balance -= amount;
        }
    }

    //Method to get account number
    string getAccountNumber()
    {
        return accountNumber; 
    }

    // Method to get current balance
    double getBalance() {
        return balance;
    }

    // Method to close the account
    void closeAccount() {
        // TODO: Prevent further transactions when the account is closed
        isActive = false;
    }

    void validInput()
    {
        if (std::cin.fail()) 
        {
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            throw std::runtime_error("Invalid input: Please enter a number.");
        }
    }

   
};




int main() {
    try {
        // TODO: Ask the user to enter an initial balance and create a BankAccount object using smart pointers
        // Example: std::cout << "Enter initial balance: ";
        //          std::cin >> initialBalance;
        //          auto account = std::make_unique<BankAccount>("123456", initialBalance);

        double initialBalance = 0; 
        double depositAmt = 0;
        double withdrawAmount = 0; 


        // TODO: Test edge cases - try withdrawing more than available balance
        cout << "This section will automate testing exceptions" << std::endl;

        auto account = std::make_unique<BankAccount>("54321", 100);
        std::cout << "Bank Account Created: #" << account->getAccountNumber() << std::endl;
        std::cout << "Current Balance: $" << account->getBalance() << std::endl;
        cout << std::endl;

        try
        {
            cout << "Testing NegativeDepositException" << std::endl;
            cout << "Depositing -10 " << std::endl;
            account->deposit(-10);
        }
        catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

        cout << std::endl;

        try
        {
            cout << "Testing OverdrawException" << std::endl;
            std::cout << "Current Balance: $" << account->getBalance() << std::endl;
            std::cout << "Attempting to withdraw $600..." << std::endl;
            account->withdraw(600); // This should trigger an exception once implemented
        }
        catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

        cout << std::endl;

        try
        {
            cout << "Testing InvalidAccountOperationException" << std::endl;
            std::cout << "Current Balance: $" << account->getBalance() << std::endl;
            std::cout << "Closing the account..." << std::endl;
            account->closeAccount();
            cout << "Account Closed" << std::endl;
            cout << "Attempting to deposit $90..." << std::endl;
            account->deposit(90);
        }
        catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

        cout << std::endl << std::endl;



        cout << "This section will automate testing edge cases on a different account" << std::endl;

        account = std::make_unique<BankAccount>("10101", 500);
        std::cout << "Bank Account Created: #" << account->getAccountNumber() << std::endl;
        std::cout << "Current Balance: $" << account->getBalance() << std::endl;
        cout << std::endl;

        try
        {
            cout << "Testing depositing 0" << std::endl;
            account->deposit(0);
            cout << "And it worked, balance is " << account->getBalance() << std::endl;
        }
        catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

        cout << std::endl;

        try
        {
            cout << "Testing withdrawing 0" << std::endl;
            account->withdraw(0);
            cout << "And it worked, balance is " << account->getBalance() << std::endl;
        }
        catch (const std::exception& e) { std::cerr << "Error: " << e.what() << std::endl; }

        cout << std::endl;

        try
        {
            cout << "Testing withdrawing -5 (a negative number)" << std::endl;
            account->withdraw(-5);
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
            cout << "A valid exception has been raised" << std::endl;
        }

        cout << std::endl << std::endl << std::endl;

        // --------- USER RAN TESTS ------------- 


        cout << "This section will be user ran tests" << std::endl;
        cout << "\t User will enter input based on the prompts" << std::endl; 
        cout << "\t If errors are caught, the program will print exception and terminate" << std::endl << std::endl;

        cout << "A new account will be created" << std::endl; 
        std::cout << "Enter initial balance: ";
        std::cin >> initialBalance; 
        if (std::cin.fail() || initialBalance < 0 ) 
        {
            std::cin.clear(); // clear the error state
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard bad input
            throw std::runtime_error("Invalid input: Please enter a number at least 0.");
        }

        account = std::make_unique<BankAccount>("123456", initialBalance); // Example initialization

        std::cout << "Bank Account Created: #" << account->getAccountNumber() << std::endl;
        std::cout << "Current Balance: $" << account->getBalance() << std::endl;

        // TODO: Allow the user to enter deposit amounts and call deposit() method - done 
        std::cout << "How much would you like to deposit?" << std::endl;
        cin >> depositAmt; 
        account->validInput(); 
        
        std::cout << "Depositing " << depositAmt << "..." << std::endl;
        account->deposit(depositAmt);
        std::cout << "Current Balance: $" << account->getBalance() << std::endl;


        // TODO: Allow the user to enter withdrawal amounts and call withdraw() method - done 
        std::cout << "How much wouold you like to withdraw?" << std::endl; 
        cin >> withdrawAmount; 
        std::cout << "Withdrawing "<< withdrawAmount << "..." << std::endl;
        account->withdraw(withdrawAmount);

        std::cout << "Current Balance: $" << account->getBalance() << std::endl;

        cout << "This is the end of the user input cases" << std::endl << std::endl;








    }//large try
    catch (const std::exception& e) {
        // TODO: Catch and handle exceptions properly
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}

