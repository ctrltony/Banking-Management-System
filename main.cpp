#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

class BankAccount {
    int accountNumber;
    char accountHolder[50];
    float balance;
public:
    void openAccount() {
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cin.ignore();
        cout << "Enter Account Holder Name: ";
        cin.getline(accountHolder, 50);
        cout << "Enter Initial Deposit: ";
        cin >> balance;
    }
    void showAccount() {
        cout << "Account Number: " << accountNumber << "\n";
        cout << "Account Holder: " << accountHolder << "\n";
        cout << "Current Balance: " << balance << "\n";
    }
    void deposit(float amount) {
        balance += amount;
    }
    void withdraw(float amount) {
        if (amount <= balance) {
            balance -= amount;
            cout << "Withdrawal successful.\n";
        } else {
            cout << "Insufficient balance.\n";
        }
    }
    int getAccountNumber() {
        return accountNumber;
    }
};

void writeAccount() {
    BankAccount ac;
    ofstream outFile("bank_data.dat", ios::binary | ios::app);
    ac.openAccount();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
    outFile.close();
    cout << "Account created.\n";
}

void displayAccount(int n) {
    BankAccount ac;
    bool flag = false;
    ifstream inFile("bank_data.dat", ios::binary);
    if (!inFile) {
        cout << "File could not be opened.\n";
        return;
    }
    while (inFile.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount))) {
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            flag = true;
        }
    }
    inFile.close();
    if (!flag) {
        cout << "Account not found.\n";
    }
}

void modifyBalance(int n, int option) {
    bool found = false;
    BankAccount ac;
    fstream File("bank_data.dat", ios::binary | ios::in | ios::out);
    if (!File) {
        cout << "File could not be opened.\n";
        return;
    }
    while (!File.eof() && found == false) {
        File.read(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
        if (ac.getAccountNumber() == n) {
            ac.showAccount();
            float amt;
            if (option == 1) {
                cout << "Enter amount to deposit: ";
                cin >> amt;
                ac.deposit(amt);
            }
            if (option == 2) {
                cout << "Enter amount to withdraw: ";
                cin >> amt;
                ac.withdraw(amt);
            }
            int pos = (-1) * static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char*>(&ac), sizeof(BankAccount));
            found = true;
        }
    }
    File.close();
    if (!found) {
        cout << "Record not found.\n";
    }
}

int main() {
    char ch;
    int num;
    do {
        cout << "\n\n=== BANKING SYSTEM ===\n";
        cout << "1. Open New Account\n";
        cout << "2. Balance Enquiry\n";
        cout << "3. Deposit Amount\n";
        cout << "4. Withdraw Amount\n";
        cout << "5. Exit\n";
        cout << "Select Your Option (1-5): ";
        cin >> ch;
        switch (ch) {
            case '1':
                writeAccount();
                break;
            case '2':
                cout << "Enter Account Number: ";
                cin >> num;
                displayAccount(num);
                break;
            case '3':
                cout << "Enter Account Number: ";
                cin >> num;
                modifyBalance(num, 1);
                break;
            case '4':
                cout << "Enter Account Number: ";
                cin >> num;
                modifyBalance(num, 2);
                break;
            case '5':
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid Input.\n";
        }
    } while (ch != '5');
    return 0;
}
