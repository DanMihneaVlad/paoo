#include <iostream>

using namespace std;

class Animal {
    protected: 
        int age;
        string color;
        string type;

    public:
        // Animal constructor with object initialization
        Animal(const int age, const string& color, const string& type)
       :age(age),
        color(color),
        type(type)
        {
            cout << "Created an animal" << endl;
        }

        ~Animal();

        void makeSound()
        {
            cout << "Animal sound" << endl;
        }
    
    private:
        // Disallow the use of compiler generated functions
        Animal(const Animal&);
        Animal& operator=(const Animal&);
};

class Dog : private Animal {
    public:
        Dog(const int age, const string& color, const string& type) 
       :Animal(age, color, type)
        {

        }

        void makeSound()
        {
            cout << "Woof" << endl;
        }
};

class Cat : private Animal {
    public:
        Cat(const int age, const string& color, const string& type) : Animal(age, color, type) {}

        void makeSound()
        {
            cout << "Meow" << endl;
        }
};

int main()
{
    Animal* a = new Animal(1, "Black", "Mammal");
    Dog* d = new Dog(4, "Brown", "Mammal");
    Cat *c = new Cat(2, "Yellow", "Mammal");

    d->makeSound();
    c->makeSound();
}