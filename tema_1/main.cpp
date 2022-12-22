#include <iostream>
#include <memory>

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

        ~Animal() { cout << "Animal destructor" << endl; }

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

        string getColor()
        {
            return color;
        }

        string getAge()
        {
            return to_string(age);
        }

        static void lockAnimal(Animal *a)
        {
            cout << "Animal " << a->color << " age " << a->getAge() << " locked" << endl;
        }

        static void unlockAnimal(Animal *a)
        {
            cout << "Animal " << a->color << " age " << a->getAge() << " unlocked" << endl;
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

        ~Dog() { cout << "Dog destructor" << endl; }

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

        // Item 13
        static Dog* createDog(const int age, const string& color, const string& type, const string& breed)
        {
            return new Dog(age, color, type, breed);
        }
};

class Cat : public Animal {
    public:
        Cat() { }

        ~Cat() { cout << "Cat destructor" << endl; }

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

        // Item 13
        static Cat* createCat(const int age, const string& color, const string& type)
        {
            return new Cat(age, color, type);
        }
};

// Item 14
class lockAnimal {
    private:
        shared_ptr<Animal> a;

    public:
    ~lockAnimal() {
        cout << "lockAnimal destructor called" << endl;
    }

    explicit lockAnimal(Animal *animal) : a(animal, Animal::unlockAnimal)
    {
        Animal::lockAnimal(a.get());
    }
};

int main()
{
    /* Old demos
    Animal a(1, "Black", "Mammal");
    Dog d(4, "Brown", "Mammal", "German Shepherd");
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
    */

    // Item 13
    unique_ptr<Dog> dog1(Dog::createDog(4, "black", "mammal", "German Shepherd"));
    cout << dog1->getBreed() << endl;
    // The dog and animal destructors are called, the resource is released automatically

    //unique_ptr<Dog> dog2(dog1);
    // Won't compile because it should be unique
    
    shared_ptr<Cat> cat1(Cat::createCat(2, "orange and white", "Mammal"));
    cout << cat1->getColor() << endl;

    // By using a shared ptr we can copy
    shared_ptr<Cat> cat2(cat1);
    cout << cat2->getAge() << endl;
    cout << cat1->getAge() << endl;
    // At the end the destructor is called

    // Item 14
    Animal *a = new Animal(2, "black and brown", "Mammal");
    {
        // The animal is locked when created
        lockAnimal lockA(a);
        cout << a->getColor() << endl;
        // The animal is unlocked after lockAnimal destructor is called
    }
    cout << "Animal was unlocked" << endl;
}