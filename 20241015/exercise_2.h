#ifndef EXERCISE_H
#define EXERCISE_H

#include <iostream>
#include <cmath>
#include <initializer_list>

using namespace std;

template<typename T>
class Point {
private:
    T x, y;  

public:

    Point(T xVal = 0, T yVal = 0) : x(xVal), y(yVal) {

    }

    T getX() const { return x; }
    T getY() const { return y; }

    /*=============================================== TODO 1 ===============================================
        1. Instruction:
            - Implement a copy constructor for the Point class.
        2. Example:
            - When calling ```Point<int> p1(3, 4); Point<int> p2 = p1;```, p2 should be a copy of p1.
    =======================================================================================================*/
    Point(const Point<T>& src):
    x(src.x), y(src.y) {};
    
    


    Point(const Point<T>& src)
    : x(src.x), y(src.y) {
        cout << "Copy constructor called." << endl;
    }

    /*=============================================== TODO 2 ===============================================
        1. Instruction:
            - Implement a move constructor for the Point class.
        2. Example:
            - When calling ```Point<int> p1(3, 4); Point<int> p2 = std::move(p1);```, 
              p2 should take the values from p1, and p1 should be reset.
    =======================================================================================================*/
    Point(const Point<T>& src):
    x(src.x), y(src.y) {
        src.x = 0;
        src.y = 0;
    }
    
    
    
    
    Point(const Point&& src) 
    :x(src.x), y(src.y) {
        src.x = 0;
        src.y = 0;
        cout << "Move constructor called." << endl;
    }


    /*=============================================== TODO 3 ===============================================
        1. Instruction:
            - Implement the copy assignment operator for the Point class.
        2. Example:
            - When calling ```Point<int> p1(3, 4); Point<int> p2; p2 = p1;```,
              p2 should have the same values as p1.
    =======================================================================================================*/
    Point<T>& operator=(const Point<T>& src) {
        if (this != &src) {
            x = src.x;
            y = src.y;
        }
        return *this;
    }


    
    
    
    Point<T>& operator=(
        const Point<T>& src
    ) {
        if (this != &src) {
            x = src.x;
            y = src.y;
        }
        cout << "Copy assingment operator called" << endl;
        return *this;
    }


    /*=============================================== TODO 4 ===============================================
        1. Instruction:
            - Implement the move assignment operator for the Point class.
        2. Example:
            - When calling ```Point<int> p1(3, 4); Point<int> p2; p2 = std::move(p1);```, 
              p2 should take the values from p1, and p1 should be reset.
    =======================================================================================================*/
    Point<T>& operator=(const Point<T>&& src) noexcept {
        if (this != &src) {
            x = src.x;
            y = src.y;

            src.x = 0;
            src.y = 0;
        }
        return *this;
    }
    
    
    
    
    
    Point<T>& operator=(Point&& src)  {
        if (this != &src) {
            x = src.x;
            y = src.y;

            src.x = 0;
            src.y = 0;
        }
        cout << "Move assignment operator called" << endl;
        return *this;
    }
    

    /*=============================================== TODO 5 ===============================================
        1. Instruction:
            - Implement an assignment operator for the Point class using initializer list .
        2. Function Definition:
            - If the initializer list does not have exactly two elements, throw an invalid_argument exception.
              `` You must provide exactly 2 values (for x and y). ``
        3. Example:
            - When calling ```Point<int> p1; p1 = {3, 4};```, 
              p1 should have x = 3 and y = 4.
    =======================================================================================================*/
    Point<T>& operator=(const initializer_list::<T> elements) {
        if (elementes.size() != 2) {
            throw out_of_range("size should be 2");
        } else {
            auto it = elements.begin();
            x = *it++;
            y = *it;
        }
        return *this;
    }


    
    
    
    
    Point<T>&  operator=(initializer_list<T> values) {
        if (values.size() != 2) {
            throw invalid_argument("You must provide exactly 2 values");
        }
        auto it = values.begin();
        x = *it++;
        y = *it;
        return *this;
    }


    /*=============================================== TODO 6 ===============================================
        1. Instruction:
            - Implement the [] operator to access the x or y coordinates using an index.
        2. Function Definition:
            - If the index is anything other than 0 or 1, throw an out_of_range exception.
              `` Index must be 0 or 1. ``
        3. Example:
            - p[0] should return the x coordinate, and p[1] should return the y coordinate.
    =======================================================================================================*/
     
     
     
     
     T& operator[](
        int index
     ) {
        if (index == 0) {
            return x;
        } else if (index == 1) {
            return y;
        } else {
            throw out_of_range("Index must be 0 or 1");
        }
     }


    /*=============================================== TODO 7 ===============================================
        1. Instruction:
            - Implement the * operator to calculate the dot product of two Point objects.
        2. Function Definition:
            - Return the result of the dot product calculation.
        3. Example:
            - When calling ```Point<int> p1(1, 2), p2(3, 4); int result = p1 * p2;```, the result should be 11.
    =======================================================================================================*/
    T operator*(const Point& rhs) const{
        return x * rhs.x + y * rhs.y;
    }


    /*=============================================== TODO 8 ===============================================
        1. Instruction:
            - Implement the ^ operator to calculate the norm (length) of a Point object.
            - Support both the L1 norm and L2 norm.
        2. Function Definition:
            - L1 norm : |x| + |y|.
            - L2 norm : sqrt(x^2 + y^2).
            - If the norm type is not 1 or 2, throw an invalid_argument exception.
              `` Invalid norm type. Use 1 for L1 norm and 2 for L2 norm. ``
        3. Example:
            - When calling ```Point<int> p1(3, 4); double result = p1^2;```, the result should be 5.0.
    =======================================================================================================*/
    double operator^(int normType) {
        if (normType == 1) {
            return abs(x) + abs(y);
        } else if (normType == 2) {
            return sqrt(x*x + y*y);
        } else {
            throw out_of_range("normType must be 1 or 2");
        }
    }



    /*=============================================== TODO 9 ===============================================
        1. Instruction:
            - Implement the != operator to check if two Point objects are not equal.
        2. Function Definition:
            - The != operator should return true if the x or y coordinates of the two points are different. 
            - Otherwise, it should return false.
        4. Example:
            - When calling ```Point<int> p1(3, 4); Point<int> p2(3, 5); bool result = (p1 != p2);```, 
              the result should be `true` because the `y` coordinates are different.
            - It should return `false` if both `x` and `y` are the same.
    =======================================================================================================*/
    bool operator!=(const Point<T>& rhs) const {
        return x != rhs.x || y != rhs.y;
    }
    
    
    
    
    bool operator!=(const Point& rhs) const {
        return x != rhs.x || y != rhs.y;
    }
    

    /////////////// DO NOT MODIFY THIS ////////////////
    friend ostream& operator<<(ostream& os, const Point<T>& point) {
        os << "(" << point.x << ", " << point.y << ")";
        return os;
    };
    /////////////// DO NOT MODIFY THIS ////////////////

    friend ostream& operator<<(ostream& os, const Point<T>& point) {
        os << "(" << point.x << "," << point.y << ")";
        return os;
    }
};


#endif 