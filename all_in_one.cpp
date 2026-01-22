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

class Dog : public Animal {
private:
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
};

class Cat : public Animal {
private:
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
};

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

int main() {
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
    
    vector<unique_ptr<Animal>> smartAnimals;
    smartAnimals.push_back(make_unique<Dog>("Max", 4, "Husky"));
    smartAnimals.push_back(make_unique<Cat>("Luna", 1));
    smartAnimals.push_back(make_unique<Cow>("Daisy", 3));
    
    for (auto& animal : smartAnimals) {
        animal->sound();
    }
    
    whiskers.loseLife();
    bella.setMilk(false);
    
    return 0;
}