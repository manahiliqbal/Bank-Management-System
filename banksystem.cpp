#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

class Account
{
private:
    string username;
    string password;
    int accountNumber;
    int amount;

public:
    static int count;
    Account()
    {
        this->username = "";
        this->password = "";
        this->accountNumber = 0;
        this->amount = 0;
    }
    Account(string un, string pw, int acN, int amt)
    {
        this->username = un;
        this->password = pw;
        this->accountNumber = acN;
        this->amount = amt;
    }
    ~Account() {}
    void setUsername(string un)
    {
        this->username = un;
    }
    void setPassword(string pw)
    {
        this->password = pw;
    }
    void setAccountNumber(int acN)
    {
        this->accountNumber = acN;
    }
    void setAmount(int amt)
    {
        this->amount = amt;
    }
    string getUsername()
    {
        return username;
    }
    string getPassword()
    {
        return password;
    }
    int getAccountNumber()
    {
        return accountNumber;
    }
    int getAmount()
    {
        return amount;
    }
    static void writeAccounts(Account array[], int SIZE)
    {
        ofstream outf;
        outf.open("accounts.dat", ios::ate);
        outf.write(reinterpret_cast<char *>(array), (sizeof(Account) * SIZE));
        outf.close();
    }
    static void readAccounts(Account array[], int SIZE)
    {
        ifstream inf;
        inf.open("accounts.dat", ios::in);
        if (!inf)
        {
            ofstream outf;
            outf.open("accounts.dat", ios::app);
            outf.close();
            inf.open("accounts.dat", ios::in);
        }
        inf.read(reinterpret_cast<char *>(array), (sizeof(Account) * SIZE));
        inf.close();
    }
};
int Account ::count = 0;
const int SIZE = 10;
bool check1 = 0, check2 = 0, check3 = 0;
int temp, temp2;
string check;

void CreateAccount(Account array[])
{
    Account::readAccounts(array, SIZE);
    int acn;
    string un, pw;
    cout << "To create an account give the following info: \n";
    cout << "Enter username: ";
    cin >> un;
    for (int i = 0; i < SIZE; i++)
    {
        if (array[i].getAccountNumber() == 0)
        {
            Account::count = i;
            break;
        }
    }
    array[Account::count].setUsername(un);
    cout << "Enter password: ";
    cin >> pw;
    array[Account::count].setPassword(pw);
    array[Account::count].setAccountNumber(Account::count + 100);
    cout << "Account Number for your account is: ";
    cout << array[Account::count].getAccountNumber();
    cout << "\n";
    Account::count++;
    Account::writeAccounts(array, SIZE);
}

void DepositMoney(Account array[])
{
    Account::readAccounts(array, SIZE);
    cout << "To deposit money, give the following info: \n";
    cout << "Enter Account Number: ";
    cin >> temp;
    for (int j = 0; j < SIZE; j++)
    {
        if (temp == array[j].getAccountNumber())
        {
            cout << "Enter amount you want to store in your account: ";
            cin >> temp2;
            array[j].setAmount(array[j].getAmount() + temp2);
            check1 = 1;
            break;
        }
    }
    if (check1 == 0)
    {
        cout << "Account does not exist\n\n";
    }
    else
    {
        cout << "Success\n";
    }
    cout << "\n";
    Account::writeAccounts(array, SIZE);
}

void WithdrawMoney(Account array[])
{
    Account::readAccounts(array, SIZE);
    cout << "To withdraw money, give the following info: \n";
    cout << "Enter Account Number: ";
    cin >> temp;
    for (int k = 0; k < SIZE; k++)
    {
        if (temp == array[k].getAccountNumber())
        {
            cout << "Enter amount you want to withdraw from your account: ";
            cin >> temp2;
            while (array[k].getAccountNumber() < temp2)
            {
                cout << "Insufficient Amount";
                cout << "Enter amount again: ";
                cin >> temp2;
            }
            array[k].setAmount(array[k].getAmount() - temp2);
            check2 = 1;
            break;
        }
        cout << "\n";
    }
    if (check2 == 0)
    {
        cout << "Account does not exist\n\n";
    }
    else
    {
        cout << "Success\n";
    }
    Account::writeAccounts(array, SIZE);
}

void ShowDetail(Account array[])
{
    Account::readAccounts(array, SIZE);
    cout << "To display the information of an account give the following info: \n";
    cout << "Enter Account Number: ";
    cin >> temp;
    cout << "Enter password: ";
    cin >> check;
    cout << "\n";
    for (int i = 0; i < SIZE; i++)
    {
        if (temp == array[i].getAccountNumber() && check == array[i].getPassword())
        {
            cout << "Username of customer is " << array[i].getUsername() << "\n";
            cout << "Password of customer is " << array[i].getPassword() << "\n";
            cout << "Account Number of customer is " << array[i].getAccountNumber() << "\n";
            cout << "Amount of customer is " << array[i].getAmount() << "\n";
            cout << "\n";
            check3 = 1;
            break;
        }
    }
    if (check3 == 0)
    {
        cout << "Account does not exist\n\n";
    }
    Account::writeAccounts(array, SIZE);
}
int main()
{
    Account array[SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        array[i].setAmount(0);
        array[i].setAccountNumber(0);
    }
    int choice;
    cout << "Welcome to Bank\n";
    cout << "What do you want to do?\n";
    cout << "Enter 1 to create account\n";
    cout << "Enter 2 to deposit money\n";
    cout << "Enter 3 to withdraw money\n";
    cout << "Enter 4 to show detail of an account\n";
    cout << "Enter 0 to terminate\n";
    cout << "Your choice: ";
    cin >> choice;

    while (choice != 0)
    {
        switch (choice)
        {
        case 1:
        {
            CreateAccount(array);
            cout << "\nWhat do you want to do?\n";
            cout << "Enter 1 to create account\n";
            cout << "Enter 2 to deposit money\n";
            cout << "Enter 3 to withdraw money\n";
            cout << "Enter 4 to show detail of an account\n";
            cout << "Your choice: ";
            cin >> choice;
            break;
        }
        case 2:
        {
            DepositMoney(array);
            cout << "\nWhat do you want to do?\n";
            cout << "Enter 1 to create account\n";
            cout << "Enter 2 to deposit money\n";
            cout << "Enter 3 to withdraw money\n";
            cout << "Enter 4 to show detail of an account\n";
            cout << "Enter 0 to terminate\n";
            cout << "Your choice: ";
            cin >> choice;
            break;
        }
        case 3:
        {
            WithdrawMoney(array);
            cout << "\nWhat do you want to do?\n";
            cout << "Enter 1 to create account\n";
            cout << "Enter 2 to deposit money\n";
            cout << "Enter 3 to withdraw money\n";
            cout << "Enter 4 to show detail of an account\n";
            cout << "Enter 0 to terminate\n";
            cout << "Your choice: ";
            cin >> choice;
            break;
        }
        case 4:
        {
            ShowDetail(array);
            cout << "\nWhat do you want to do?\n";
            cout << "Enter 1 to create account\n";
            cout << "Enter 2 to deposit money\n";
            cout << "Enter 3 to withdraw money\n";
            cout << "Enter 4 to show detail of an account\n";
            cout << "Enter 0 to terminate\n";
            cout << "Your choice: ";
            cin >> choice;
            break;
        }
        default:
        {
            cout << "Wrong Choice\n\n";
            cout << "\nWhat do you want to do?\n";
            cout << "Enter 1 to create account\n";
            cout << "Enter 2 to deposit money\n";
            cout << "Enter 3 to withdraw money\n";
            cout << "Enter 4 to show detail of an account\n";
            cout << "Enter 0 to terminate\n";
            cout << "Your choice: ";
            cin >> choice;
            break;
        }
        }
    }
    return 0;
}