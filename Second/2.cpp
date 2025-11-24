#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BankAccount {
private:
    string owner;
    double balance;
    string accountNumber;

public:
    BankAccount(string own, double bal, string accNum) 
        : owner(own), balance(bal), accountNumber(accNum) {}
    
    // Перегрузка оператора сложения (объединение счетов)
    BankAccount operator+(const BankAccount& other) const {
        string newOwner = this->owner + " & " + other.owner;
        double newBalance = this->balance + other.balance;
        string newAccNum = this->accountNumber + "_merged";
        
        return BankAccount(newOwner, newBalance, newAccNum);
    }
    
    // Перегрузка оператора +=
    BankAccount& operator+=(double amount) {
        this->balance += amount;
        return *this;
    }
    
    // Перегрузка оператора -=
    BankAccount& operator-=(double amount) {
        if (this->balance >= amount) {
            this->balance -= amount;
        }
        return *this;
    }
    
    // Перегрузка оператора сравнения
    bool operator>(const BankAccount& other) const {
        return this->balance > other.balance;
    }
    
    bool operator==(const BankAccount& other) const {
        return this->accountNumber == other.accountNumber;
    }
    
    // Перегрузка оператора вывода
    friend ostream& operator<<(ostream& os, const BankAccount& acc) {
        os << "Владелец: " << acc.owner 
           << ", Баланс: " << acc.balance 
           << ", Счет: " << acc.accountNumber;
        return os;
    }
    
    // Перегрузка оператора ввода
    friend istream& operator>>(istream& is, BankAccount& acc) {
        cout << "Введите владельца: ";
        is >> acc.owner;
        cout << "Введите баланс: ";
        is >> acc.balance;
        cout << "Введите номер счета: ";
        is >> acc.accountNumber;
        return is;
    }
    
    // Геттеры
    string getOwner() const { return owner; }
    double getBalance() const { return balance; }
    string getAccountNumber() const { return accountNumber; }
};

class Bank {
private:
    vector<BankAccount> accounts;

public:
    // Перегрузка оператора += для добавления счета
    Bank& operator+=(const BankAccount& account) {
        accounts.push_back(account);
        return *this;
    }
    
    // Перегрузка оператора [] для доступа к счетам
    BankAccount& operator[](size_t index) {
        if (index >= accounts.size()) {
            throw out_of_range("Индекс вне диапазона");
        }
        return accounts[index];
    }
    
    // Перегрузка оператора вывода для банка
    friend ostream& operator<<(ostream& os, const Bank& bank) {
        os << "Банк содержит " << bank.accounts.size() << " счетов:\n";
        for (const auto& acc : bank.accounts) {
            os << acc << endl;
        }
        return os;
    }
    
    // Сортировка счетов по балансу (использует перегруженный оператор >)
    void sortAccounts() {
        sort(accounts.begin(), accounts.end(), 
             [](const BankAccount& a, const BankAccount& b) {
                 return a > b;
             });
    }
};

int main() {
    BankAccount acc1("Иван Иванов", 1000.0, "ACC001");
    BankAccount acc2("Петр Петров", 2000.0, "ACC002");
    
    // Использование перегруженных операторов
    cout << "Счет 1: " << acc1 << endl;
    cout << "Счет 2: " << acc2 << endl;
    
    // Оператор сложения
    BankAccount merged = acc1 + acc2;
    cout << "Объединенный счет: " << merged << endl;
    
    // Операторы += и -=
    acc1 += 500.0;
    acc2 -= 300.0;
    cout << "После операций: " << acc1 << endl;
    cout << "После операций: " << acc2 << endl;
    
    // Оператор сравнения
    if (acc1 > acc2) {
        cout << "Счет 1 имеет больший баланс" << endl;
    }
    
    // Работа с банком
    Bank bank;
    bank += acc1;
    bank += acc2;
    bank += merged;
    
    cout << bank << endl;
    
    return 0;
}
