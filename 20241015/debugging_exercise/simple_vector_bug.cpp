#include <iostream>
#include <memory>
#include <initializer_list>

template <typename T>
class SimpleVector {
private:
    T* array;
    int size;
    int capacity;

    void resize();

public:
    SimpleVector(int initialCapacity);
    SimpleVector(std::initializer_list<T> elements);
    ~SimpleVector();

    void addElement(T element);
    int getSize() const;
    
    T& operator[](int index) const;
};

template <typename T>
SimpleVector<T>::SimpleVector(int initialCapacity) : size(0), capacity(initialCapacity) {
    array = new T[capacity];
}

template <typename T>
SimpleVector<T>::SimpleVector(std::initializer_list<T> elements)
: size(0), capacity(elements.size()) {
    // cout << "Initializer list constructor called" << endl;
    array = new T[capacity];
    for (auto element : elements) {
        addElement(element);
    }
}

template <typename T>
SimpleVector<T>::~SimpleVector() {
    delete[] array;
}

template <typename T>
void SimpleVector<T>::addElement(T element) {
    if (size == capacity)
        resize();
    array[size] = element;
    size++;
}

template <typename T>
int SimpleVector<T>::getSize() const {
    return size;
}

template <typename T>
void SimpleVector<T>::resize() {
    capacity = capacity * 2;
    T* newArray = new T[capacity];
    for (int i = 0; i < size; i++)
        newArray[i] = array[i];
    delete[] array;
    array = newArray;
}

template <typename T>
T& SimpleVector<T>::operator[](int index) const {
    return array[index];
}

int main() {
    SimpleVector<int> vec1 = {1, 2, 3};
    SimpleVector<int> vec2 = vec1;

    vec1.addElement(4);
    vec2.addElement(5);

    std::cout << "vec1: ";
    for (int i = 0; i < vec1.getSize(); i++) {
        std::cout << vec1[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "vec2: ";
    for (int i = 0; i < vec2.getSize(); i++) {
        std::cout << vec2[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}