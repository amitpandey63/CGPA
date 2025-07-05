#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

// Forward declaration
class Transaction;

// ---------------------- Account Class ----------------------
class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(string accNum) : accountNumber(accNum), balance(0.0) {}

    string getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount);
    bool withdraw(double amount);
    bool transfer(Account &toAccount, double amount);

    void addTransaction(const Transaction &t);
    void showTransactions() const;
};

// ---------------------- Transaction Class ----------------------
class Transaction {
private:
    string type;
    double amount;
    string note;

public:
    Transaction(string t, double a, string n = "") : type(t), amount(a), note(n) {}

    void display() const {
        cout << "Type: " << type
             << " | Amount: " << fixed << setprecision(2) << amount;
        if (!note.empty())
            cout << " | Note: " << note;
        cout << endl;
    }

    friend class Account;
};

// ---------------------- Account Member Functions ----------------------
void Account::deposit(double amount) {
    balance += amount;
    addTransaction(Transaction("Deposit", amount));
    cout << "Deposit successful. New Balance: " << balance << endl;
}

bool Account::withdraw(double amount) {
    if (amount > balance) {
        cout << "Insufficient balance!\n";
        return false;
    }
    balance -= amount;
    addTransaction(Transaction("Withdraw", amount));
    cout << "Withdrawal successful. New Balance: " << balance << endl;
    return true;
}

bool Account::transfer(Account &toAccount, double amount) {
    if (amount > balance) {
        cout << "Insufficient balance for transfer!\n";
        return false;
    }
    balance -= amount;
    toAccount.balance += amount;

    addTransaction(Transaction("Transfer To", amount, toAccount.accountNumber));
    toAccount.addTransaction(Transaction("Transfer From", amount, accountNumber));

    cout << "Transfer successful!\n";
    return true;
}

void Account::addTransaction(const Transaction &t) {
    transactions.push_back(t);
}

void Account::showTransactions() const {
    cout << "\n--- Transaction History for Account " << accountNumber << " ---\n";
    if (transactions.empty()) {
        cout << "No transactions yet.\n";
    } else {
        for (const Transaction &t : transactions)
            t.display();
    }
    cout << "----------------------------------------\n";
}

// ---------------------- Customer Class ----------------------
class Customer {
private:
    string name;
    string customerId;
    Account account;

public:
    Customer(string n, string id) : name(n), customerId(id), account(id + "_ACC") {}

    void showInfo() const {
        cout << "\nCustomer Name: " << name
             << "\nCustomer ID: " << customerId
             << "\nAccount Number: " << account.getAccountNumber()
             << "\nBalance: " << account.getBalance() << endl;
    }

    Account &getAccount() {
        return account;
    }
};

// ---------------------- Main Program ----------------------
int main() {
    vector<Customer> customers;

    int choice;
    while (true) {
        cout << "\n===== BANK SYSTEM MENU =====\n";
        cout << "1. Create Customer\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Transfer\n";
        cout << "5. View Account Info\n";
        cout << "6. View Transactions\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 0) break;

        if (choice == 1) {
            string name, id;
            cout << "Enter Customer Name: ";
            cin >> name;
            cout << "Enter Customer ID: ";
            cin >> id;
            customers.push_back(Customer(name, id));
            cout << "Customer created successfully!\n";
        }

        else if (choice >= 2 && choice <= 6) {
            string id;
            cout << "Enter Customer ID: ";
            cin >> id;

            Customer *customer = nullptr;
            for (auto &c : customers) {
                if (id == c.getAccount().getAccountNumber().substr(0, id.length())) {
                    customer = &c;
                    break;
                }
            }

            if (!customer) {
                cout << "Customer not found.\n";
                continue;
            }

            Account &acc = customer->getAccount();

            if (choice == 2) {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc.deposit(amount);
            }

            else if (choice == 3) {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc.withdraw(amount);
            }

            else if (choice == 4) {
                string toId;
                cout << "Enter recipient Customer ID: ";
                cin >> toId;

                Customer *toCustomer = nullptr;
                for (auto &c : customers) {
                    if (toId == c.getAccount().getAccountNumber().substr(0, toId.length())) {
                        toCustomer = &c;
                        break;
                    }
                }

                if (!toCustomer) {
                    cout << "Recipient not found.\n";
                    continue;
                }

                double amount;
                cout << "Enter transfer amount: ";
                cin >> amount;

                acc.transfer(toCustomer->getAccount(), amount);
            }

            else if (choice == 5) {
                customer->showInfo();
            }

            else if (choice == 6) {
                acc.showTransactions();
            }
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
