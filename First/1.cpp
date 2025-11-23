#include <iostream>
using namespace std;

class Animal {
protected:
    string name;
public:
    Animal(string n) : name(n) {}
    virtual void speak() = 0;
    virtual ~Animal() {}
};

class Mammal : virtual public Animal {
public:
    Mammal(string n) : Animal(n) {}
    void breathe() { cout << name << " дышит легкими" << endl; }
};

class WingedAnimal : virtual public Animal {
public:
    WingedAnimal(string n) : Animal(n) {}
    void fly() { cout << name << " может летать" << endl; }
};

// Множественное наследование с виртуальным наследованием
class Bat : public Mammal, public WingedAnimal {
public:
    Bat(string n) : Animal(n), Mammal(n), WingedAnimal(n) {}
    
    void speak() override {
        cout << name << " издает ультразвук" << endl;
    }
    
    void showAbilities() {
        breathe();
        fly();
        speak();
    }
};

// Пример без виртуального наследования (проблема)
class ProblemBase {
public:
    int data = 100;
};

class Derived1 : public ProblemBase {};
class Derived2 : public ProblemBase {};

class ProblemClass : public Derived1, public Derived2 {
public:
    void showProblem() {
        // cout << data; // Ошибка: неоднозначность
        cout << Derived1::data << endl; // Решение через указание scope
        cout << Derived2::data << endl;
    }
};

int main() {
    Bat bat("Летучая мышь");
    bat.showAbilities();
    
    ProblemClass prob;
    prob.showProblem();
    
    return 0;
}



/*Решения проблемы ромба:
Виртуальное наследование - как в примере выше

Явное указание scope - Derived1::data

Переопределение в производном классе

Использование композиции вместо наследования*\
