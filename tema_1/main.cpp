#include <iostream>

using namespace std;

class Animal {
    protected: 
        int age;
        string color;
        string type;

    public:
        Animal() { }

        // Animal constructor with object initialization
        Animal(const int age, const string& color, const string& type)
       :age(age),
        color(color),
        type(type)
        {
            cout << "Created an animal" << endl;
        }

        ~Animal() { }

        void makeSound()
        {
            cout << "Animal sound" << endl;
        }

        Animal& operator=(const Animal& rhs)
        {
            cout << "Assignment operator for animal" << endl;

            // Handle assignment to self
            if (this == &rhs) return *this;

            age = rhs.age; // Copy all parts of object
            color = rhs.color;
            type = rhs.type;

            return *this;        // Return reference to this
        }
    
    private:
        // Disallow the use of compiler generated functions
        //Animal(const Animal&);
};

class Dog : public Animal {
    protected:
        string breed;
    
    public:
        Dog() { }

        Dog(const int age, const string& color, const string& type, const string& breed) 
       :Animal(age, color, type),
        breed(breed)
        {

        }

        Dog(const Dog& rhs)
        : Animal(rhs),
          breed(rhs.breed)
        {
            cout << "Copy constructor for dog" << endl; // Copy all parts of an objet in copy constructor
        }
        
        Dog& operator=(const Dog& rhs)
        {
            cout << "Assignment operator for dog" << endl;

            // Handle assignment to self
            if (this == &rhs) return *this;

            Animal::operator=(rhs); // Copy all parts of an object
            breed = rhs.breed;
            
            return *this;        // Return reference to this
        }

        void makeSound()
        {
            cout << "Woof" << endl;
        }

        void setBreed(string newBreed)
        {
            breed = newBreed;
        }

        string getBreed()
        {
            return breed;
        }
};

class Cat : public Animal {
    public:
        Cat() { }

        Cat(const int age, const string& color, const string& type) : Animal(age, color, type) {}

        Cat(const Cat& rhs)
        : Animal(rhs)
        {
            cout << "Copy constructor for cat" << endl; // Copy all parts of an objet in copy constructor
        }

        Cat& operator=(const Cat& rhs)
        {
            cout << "Assignment operator for cat" << endl;

            // Handle assignment to self
            if (this == &rhs) return *this;

            Animal::operator=(rhs); // Copy all parts of an object
            
            return *this;        // Return reference to this
        }

        void makeSound()
        {
            cout << "Meow" << endl;
        }
};

int main()
{
    Animal a(1, "Black", "Mammal");
    Dog d(4, "Brown", "Mammal", "German Shephard");
    Cat c(2, "Yellow", "Mammal");
    
    cout << d.getBreed() << endl;
    d.makeSound();

    Dog d1(3, "White", "Mammal", "Husky");
    Dog d2;
    Dog d3;

    d1 = d1; // assignment to self
    cout << d1.getBreed() << endl;

    d1.makeSound();

    d3 = d2 = d1; // chain of assignments

    cout << d3.getBreed() << endl;
    d2.makeSound();
    
    c.makeSound();
}