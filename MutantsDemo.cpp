#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

class Animal {
protected:
    string name;
    int age;
    
public:
    Animal(const string& animalName, int animalAge) 
        : name(animalName), age(animalAge) {}
    
    virtual ~Animal() {}
    
    virtual void sound() const = 0; 
    
    string getName() const { return name; }
    int getAge() const { return age; }
    void setAge(int newAge) { if (newAge > 0) age = newAge; }
    
    friend void printAnimalInfo(const Animal& animal); 
};

void printAnimalInfo(const Animal& animal) {
    cout << animal.name << " " << animal.age << endl;
}

// внедрил виртуальное наследование для того чтобы решить ромбовидное)
class Dog : virtual public Animal {
protected:
    string breed;
    
public:
    Dog(const string& name, int age, const string& dogBreed) 
        : Animal(name, age), breed(dogBreed) {}
    
    void sound() const override {
        cout << "woof" << endl;
    }
    
    string getBreed() const {
        return breed;
    }
    
    void setBreed(const string& newBreed) {
        breed = newBreed;
    }
    
    void dogFeature() const {
        cout << name << " сan life " <<endl;
    }
};

// еще одно внедрение виртуального
class Cat : virtual public Animal {
protected:
    int lives;
    
public:
    Cat(const string& name, int age, int catLives = 9) 
        : Animal(name, age), lives(catLives) {}
    
    void sound() const override {
        cout << "meow" << endl;
    }
    
    int getLives() const {
        return lives;
    }
    
    void loseLife() {
        if (lives > 0) lives--;
        cout << name << " lost a life(( -----" << lives << endl;
    }
    
    void catFeature() const {
        cout << name << " spit" << endl;
    }
};

// корова не участвует(оставил как было)
class Cow : public Animal {
private:
    bool givesMilk;
    
public:
    Cow(const string& name, int age, bool milk = true) 
        : Animal(name, age), givesMilk(milk) {}
    
    void sound() const override {
        cout << "moo" << endl;
    }
    
    bool isGivingMilk() const {
        return givesMilk;
    }
    
    void setMilk(bool milk) {
        givesMilk = milk;
    }
};

// множественное наследовпние с решением ромбовидного
class CatDog : public Cat, public Dog {
public:
    // котопес вызывает конструктор животного
    CatDog(const string& name, int age, const string& dogBreed, int catLives = 9)
        : Animal(name, age),  
          Cat(name, age, catLives), 
          Dog(name, age, dogBreed) 
    {}
    
    void sound() const override {
        cout << name << " says meowwoof" << endl;  
    }
    
    // метод от родителя 1 и 2
    void hybridFeature() const {
        cout << name << " can live  and spat" << endl;
    }
    
    // свойства от родителей
    void showParentsFeatures() const {
        cout << "cat features " << getLives() << " lives" << endl;
        cout << "dog features poroda " << getBreed() << endl;
    }
};

// котопес наоборот(особо ничего не поменялось)
class DogCat : public Dog, public Cat {
public:
    DogCat(const string& name, int age, const string& dogBreed, int catLives = 9)
        : Animal(name, age), 
          Dog(name, age, dogBreed),
          Cat(name, age, catLives)
    {}
    
    void sound() const override {
        cout << name << " says woofmeow" << endl;
    }
    //доступ к методам родителей
    void specialAbility() const {
        dogFeature();
        catFeature();
    }
};

int main() {
    cout << " Basic animals " << endl;
    Dog rex("Rex", 3, "Sh");
    Cat whiskers("whiskers", 2, 7);
    Cow bella("bella", 5, true);
    
    Animal* animals[] = {&rex, &whiskers, &bella};
    
    for (Animal* animal : animals) {
        animal->sound();
    }
    
    printAnimalInfo(rex);
    printAnimalInfo(whiskers);
    printAnimalInfo(bella);
    
    cout << "\n Smart ukazatili" << endl;
    vector<unique_ptr<Animal>> smartAnimals;
    smartAnimals.push_back(make_unique<Dog>("Max", 4, "Husky"));
    smartAnimals.push_back(make_unique<Cat>("Luna", 1));
    smartAnimals.push_back(make_unique<Cow>("Daisy", 3));
    
    for (auto& animal : smartAnimals) {
        animal->sound();
    }
    
    cout << "\n Experimental mutants " << endl;
    
    // создание котопса
    CatDog mutt("Mutant", 2, "Labrador", 5);
    mutt.sound(); 
    
    Animal* hybridPtr = &mutt;
    cout << "Through Animal ukazatell ";
    hybridPtr->sound();
    
    mutt.hybridFeature();
    mutt.showParentsFeatures();
    
    // создание песокота
    DogCat reverseHybrid("R", 3, "P", 6);
    cout << "\n DogCat ";
    reverseHybrid.sound();
    reverseHybrid.specialAbility();
    
    cout << "\n Original animall" << endl;
    whiskers.loseLife();
    bella.setMilk(false);
    
    return 0;
}