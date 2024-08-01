#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class BankAccount {
	private:
		int number;
		string name;
		int balance;
		int pin;

	public:
		void createAccount(int iniBalance, int pinCode, string accName) {
			number = rand() % 9000 + 1000;
			name = accName;
			balance = iniBalance;
			pin = pinCode;
		}
		void accountDetails() const {
			cout << "Account Number: " << number << endl;
			cout << "Account Name: " << name << endl;
			cout << "Balance : " << balance << endl;
		}
		void depositMoney(int newCash) {
			balance += newCash;
			cout << newCash << "Has been deposited your account!, Current Balance: " << balance;
		}
		void withdraw(int amount, int checkPin) {
			if (pin != checkPin) {
				cout << "Invalid PIN. Transaction failed." << endl;
			}
			else if (amount > balance) {
				cout << "Insufficient funds. Transaction failed." << endl;
			}
			else {
				balance -= amount;
				cout << "Withdrew " << amount << ". New balance: " << balance << endl;
			}
		}
		// Getters
		
		int getAccountNumber() const { return number; }
		string getAccountHolderName() const { return name; }
		int getBalance() const { return balance; }
		int getPin() const { return pin; }

};

void displayMainMenu() {
	cout << "\nMain Menu\n";
	cout << "1. Create Account\n";
	cout << "2. Sign In\n";
	cout << "3. Exit\n";
	cout << "Enter your choice: ";
}

void displayAccountMenu() {
    cout << "\nAccount Menu\n";
    cout << "1. Deposit Money\n";
    cout << "2. Withdraw Money\n";
    cout << "3. Account Details\n";
    cout << "4. Logout\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(time(0)); // Seed the random number generator
    vector<BankAccount> accounts;
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
        case 1: {
            string name;
            int balance, pin;
            cout << "Enter Account Holder Name: ";
            cin.ignore(); // Clear the newline character left in the buffer
            getline(cin, name);
            cout << "Enter Initial Balance: ";
            cin >> balance;
            cout << "Enter PIN: ";
            cin >> pin;

            BankAccount newAccount;
            newAccount.createAccount(balance, pin, name);
            accounts.push_back(newAccount);
            cout << "Account created successfully! Your account number is: " << newAccount.getAccountNumber() << endl;
            break;
        }
        case 2: {
            int accNumber, pin, accIndex = -1;
            cout << "Enter Account Number: ";
            cin >> accNumber;
            cout << "Enter PIN: ";
            cin >> pin;

            for (size_t i = 0; i < accounts.size(); ++i) {
                if (accounts[i].getAccountNumber() == accNumber && accounts[i].getPin() == pin) {
                    accIndex = i;
                    break;
                }
            }

            if (accIndex != -1) {
                int accountChoice;
                do {
                    displayAccountMenu();
                    cin >> accountChoice;

                    switch (accountChoice) {
                    case 1: {
                        int amount;
                        cout << "Enter amount to deposit: ";
                        cin >> amount;
                        accounts[accIndex].depositMoney(amount);
                        break;
                    }
                    case 2: {
                        int amount;
                        cout << "Enter amount to withdraw: ";
                        cin >> amount;
                        accounts[accIndex].withdraw(amount, pin);
                        break;
                    }
                    case 3:
                        accounts[accIndex].accountDetails();
                        break;
                    case 4:
                        cout << "Logging out...\n";
                        break;
                    default:
                        cout << "Invalid choice. Please try again." << endl;
                    }
                } while (accountChoice != 4);
            }
            else {
                cout << "Invalid account number or PIN. Please try again." << endl;
            }
            break;
        }
        case 3:
            cout << "Exiting the program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);

    return 0;
}