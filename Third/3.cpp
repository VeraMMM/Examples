#include <iostream>
#include <string>
using namespace std;

class Address {
private:
    string street;
    string city;
    int zipCode;

public:
    Address(string st, string ct, int zip) 
        : street(st), city(ct), zipCode(zip) {}
    
    void display() const {
        cout << street << ", " << city << ", " << zipCode;
    }
    
    string getStreet() const { return street; }
    string getCity() const { return city; }
    int getZipCode() const { return zipCode; }
};

class Customer {
private:
    string name;
    Address address;  // Композиция - объект как член класса
    double balance;

public:
    // Конструктор с объектом Address в качестве параметра
    Customer(string n, const Address& addr, double bal = 0.0)
        : name(n), address(addr), balance(bal) {}
    
    // Метод с объектом в качестве параметра
    bool transferTo(Customer& recipient, double amount) {
        if (this->balance >= amount && amount > 0) {
            this->balance -= amount;
            recipient.balance += amount;
            cout << "Перевод " << amount << " от " << name 
                 << " к " << recipient.name << " выполнен" << endl;
            return true;
        }
        cout << "Ошибка перевода" << endl;
        return false;
    }
    
    // Метод, возвращающий объект
    Address getAddress() const {
        return address;
    }
    
    // Функция-друг с объектами в качестве параметров
    friend bool areNeighbors(const Customer& c1, const Customer& c2);
    
    void display() const {
        cout << "Клиент: " << name << ", Баланс: " << balance 
             << ", Адрес: ";
        address.display();
        cout << endl;
    }
    
    string getName() const { return name; }
    double getBalance() const { return balance; }
};

// Функция с объектами в качестве параметров
bool areNeighbors(const Customer& c1, const Customer& c2) {
    return c1.address.getCity() == c2.address.getCity() && 
           c1.address.getZipCode() == c2.address.getZipCode();
}

// Функция, принимающая массив объектов
void processCustomers(Customer customers[], int size, double bonus) {
    for (int i = 0; i < size; i++) {
        cout << "Обработка: " << customers[i].getName() << endl;
        // Здесь может быть логика начисления бонуса
    }
}

// Функция, возвращающая объект
Customer createPremiumCustomer(string name, const Address& addr) {
    Customer premium(name, addr, 1000.0); // Начальный бонус
    return premium;
}

int main() {
    Address addr1("ул. Ленина 10", "Москва", 101000);
    Address addr2("пр. Мира 25", "Москва", 101000);
    Address addr3("ул. Садовая 5", "Санкт-Петербург", 190000);
    
    Customer cust1("Иван Иванов", addr1, 5000.0);
    Customer cust2("Петр Петров", addr2, 3000.0);
    Customer cust3("Мария Сидорова", addr3, 7000.0);
    
    // Объекты как аргументы методов
    cust1.transferTo(cust2, 1000.0);
    
    // Объекты как аргументы функций
    if (areNeighbors(cust1, cust2)) {
        cout << cust1.getName() << " и " << cust2.getName() 
             << " соседи" << endl;
    }
    
    // Массив объектов как аргумент
    Customer customers[] = {cust1, cust2, cust3};
    processCustomers(customers, 3, 100.0);
    
    // Функция, возвращающая объект
    Customer premium = createPremiumCustomer("VIP Клиент", addr1);
    premium.display();
    
    return 0;
}
