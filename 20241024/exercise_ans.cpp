#include <cassert>
#include <iostream>
#include <stdexcept>
#include <string>

/*=============================================== TODO 1 ===============================================
    1. Instruction:
        - Implement the Animal class, which is an abstract class.
        - Introduce a static numAnimals variable inside the class to track the number of Animal objects.
        - Ensure that external code can access the numAnimals variable directly.
          Becareful that you should initialize numAnimals.
        - The class should have a constructor that increments numAnimals and a destructor
          that decrements it.
        - The `move` function should be a pure virtual function with no parameters and should return void.
          It will be implemented by derived classes to describe how each animal moves.
=======================================================================================================*/
class Animal {
public:
    static int numAnimals;  
    Animal() { numAnimals++; }
    virtual void move() const = 0;      
    virtual ~Animal() { numAnimals--; }
};


int Animal::numAnimals = 0;

/*=============================================== TODO 2 ===============================================
    1. Instruction:
        - Implement the Mammal class derived from Animal.
        - Override the move function to print "Mammal walks on land!".
    2. Example:
        - ```Mammal mammal; mammal.move();''' should output "Mammal walks on land!".
=======================================================================================================*/
class Mammal : public Animal {
public:
    void move() const override {
        std::cout << "Mammal walks on land!" << std::endl;
    }
};


/*=============================================== TODO 3 ===============================================
    1. Instruction:
        - Implement the Bird class derived from Animal.
        - Override the move function to print "Bird flies in the sky!".
        - Add a fly function that prints "Bird is flying!".
    2. Example:
        - ```Bird bird; bird.move(); bird.fly();''' should output:
          "Bird flies in the sky!"
          "Bird is flying!"
=======================================================================================================*/

class Bird : public Animal {
public:
    void move() const override {
        std::cout << "Bird flies in the sky!" << std::endl;
    }
    virtual void fly() const {
        std::cout << "Bird is flying!" << std::endl;
    }
};


/*=============================================== TODO 4 ===============================================
    1. Instruction:
        - Implement the Penguin class derived from Bird.
        - Override the move function to print "Penguin swims but cannot fly."
        - Override the fly function to throw a `logic_error` since penguins cannot fly.
    2. Example:
        - ```Penguin penguin; penguin.move();''' should output:
          "Penguin swims but cannot fly."
        - ```penguin.fly();''' should throw an error with the message "Penguins cannot fly!"
=======================================================================================================*/
class Penguin : public Bird {
public:
    void move() const override {
        std::cout << "Penguin swims but cannot fly." << std::endl;
    }
    void fly() const override {
        throw std::logic_error("Penguins cannot fly!");
    }
};


///////////////////////// DO NOT MODIFY THIS ///////////////////////// 
void testAnimalMovement(Animal* animal) {
    animal->move();
    
    Bird* bird = dynamic_cast<Bird*>(animal);
    if (bird) {
        try {
            bird->fly();
        } catch (const std::logic_error& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }
    }
}
///////////////////////// DO NOT MODIFY THIS ///////////////////////// 

int main() {
    /*=============================================== TODO 5 ===============================================
        1. Instruction:
            - Dynamically create 3 objects of type Mammal, Bird, and Penguin class, 
              but each object should be created and accessed using a pointer of type Animal*.
            - After creation, print the number of animals using the static numAnimals.
        2. Example:
            - After creating the objects, the output should be:
              "Number of animals: 3"
    ========================================================================================================*/
    Animal* mammal = new Mammal();
    Animal* bird = new Bird();
    Animal* penguin = new Penguin();

    std::cout << "Number of animals: " << Animal::numAnimals << '\n';

    ///////////////////////// DO NOT MODIFY THIS ///////////////////////// 
    std::cout << "Testing Mammal:" << std::endl;
    testAnimalMovement(mammal);  // Expected output: "Mammal walks on land!"
    std::cout << std::endl;

    std::cout << "Testing Bird:" << std::endl;
    testAnimalMovement(bird);    // Expected output:
                                 // "Bird flies in the sky!"
                                 // "Bird is flying!"
    std::cout << std::endl;

    std::cout << "Testing Penguin:" << std::endl;
    testAnimalMovement(penguin); // Expected output:
                                 // "Penguin swims but cannot fly."
                                 // "Error: Penguins cannot fly!"
    std::cout << std::endl;
    ///////////////////////// DO NOT MODIFY THIS /////////////////////////



    /*=============================================== TODO 6 ===============================================
        1. Instruction:
            - Properly delete all objects created earlier.
            - After deletion, print the number of animals again.
        2. Example:
            - After deletion, the output should be:
              "Number of animals: 0"
    ========================================================================================================*/
    delete mammal;
    delete bird;
    delete penguin;

    std::cout << "Number of animals: " << Animal::numAnimals << '\n';

    return 0;
}
