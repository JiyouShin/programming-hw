#include <iostream>
#include <cassert>
#include "exercise_2.h"  


void runTests() {

    std::cout << "Test 1: Copy constructor\n";
    Point<int> p1(3, 4);
    Point<int> p2 = p1;
    assert(p1.getX() == p2.getX() && p1.getY() == p2.getY());  
    std::cout << "Test 1 passed: p1 = " << p1 << ", p2 = " << p2 << "\n";

    std::cout << std::endl;

    std::cout << "Test 2: Move constructor\n";
    Point<int> p3 = std::move(p1);
    assert(p3.getX() == 3 && p3.getY() == 4);  
    assert(p1.getX() == 0 && p1.getY() == 0);  
    std::cout << "Test 2 passed: p3 = " << p3 << ", p1 (moved) = " << p1 << "\n";

    std::cout << std::endl;

    std::cout << "Test 3: Copy assignment operator\n";
    Point<int> p4(10, 20);
    p4 = p3;
    assert(p4.getX() == p3.getX() && p4.getY() == p3.getY());  
    std::cout << "Test 3 Passed: p4 = " << p4 << "\n";

    std::cout << std::endl;

    std::cout << "Test 4: Move assignment operator\n";
    Point<int> p5(15, 25);
    p5 = std::move(p4);
    assert(p5.getX() == 3 && p5.getY() == 4);  
    assert(p4.getX() == 0 && p4.getY() == 0); 
    std::cout << "Test 4 passed: p5 = " << p5 << "\n";

    std::cout << std::endl;

    std::cout << "Test 5: Initializer list assignment\n";
    Point<int> p6;
    p6 = {5, 10};  
    assert(p6.getX() == 5 && p6.getY() == 10);
    std::cout << "Test 5 Passed: p6 = " << p6 << "\n";

    std::cout << std::endl;


    std::cout << "Test 6: [] Operator Access\n";
    assert(p6.getX() == 5 && p6.getY() == 10);
    p6[0] = 7;
    p6[1] = 14;
    assert(p6.getX() == 7 && p6.getY() == 14);
    std::cout << "Test 6 Passed: p6 = " << p6 << "\n";

    std::cout << std::endl;


    std::cout << "Test 7: Dot Product\n";
    Point<int> p7(1, 2);
    Point<int> p8(3, 4);
    int dot_product = p7 * p8;  
    assert(dot_product == 11);  
    std::cout << "Test 7 Passed: Dot product of p7 and p8 = " << dot_product << "\n";

    std::cout << std::endl;


    std::cout << "Test 8: L1 Norm\n";
    double l1_norm = p7 ^ 1; 
    assert(l1_norm == 3); 
    std::cout << "Test 8 Passed: L1 norm of p7 = " << l1_norm << "\n";

    std::cout << std::endl;


    std::cout << "Test 9: L2 Norm\n";
    double l2_norm = p7 ^ 2; 
    assert(abs(l2_norm - 2.236) < 1e-3);  
    std::cout << "Test 9 Passed: L2 norm of p7 = " << l2_norm << "\n";

    std::cout << std::endl;


    std::cout << "Test 10: Inequality Operator\n";
    assert(p7 != p8);  
    std::cout << "Test 10 Passed: p7 != p8\n";

    std::cout << std::endl;


    std::cout << "Test 11: Invalid initializer list assignment (too few elements)\n";
    try {
        Point<int> p9;
        p9 = {3};  
        std::cout << "Test 11 Failed: Exception not thrown for invalid initializer list.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Test 11 Passed: Exception caught: " << e.what() << "\n";
    }


    std::cout << std::endl;


    std::cout << "Test 12: Invalid initializer list assignment (too many elements)\n";
    try {
        Point<int> p10;
        p10 = {1, 2, 3};  
        std::cout << "Test 12 Failed: Exception not thrown for invalid initializer list.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Test 12 Passed: Exception caught: " << e.what() << "\n";
    }

    std::cout << std::endl;


    std::cout << "Test 13: Invalid [] operator access (out of bounds)\n";
    try {
        Point<int> p11(3, 4);
        int value = p11[2]; 
        std::cout << "Test 13 Failed: Exception not thrown for out-of-bounds access.\n";
    } catch (const std::out_of_range& e) {
        std::cout << "Test 13 Passed: Exception caught: " << e.what() << "\n";
    }

    std::cout << std::endl;


    std::cout << "Test 14: Float dot product\n";
    Point<float> p12(1.5f, 2.5f);
    Point<float> p13(3.0f, 4.0f);
    float dot_product_2 = p12 * p13;  
    assert(dot_product_2 == 1.5f * 3.0f + 2.5f * 4.0f);
    std::cout << "Test 14 Passed: Dot product of p11 and p12 = " << dot_product_2 << "\n";

    std::cout << std::endl;


    std::cout << "Test 15: Floating-point L2 Norm\n";
    double l2_norm_2 = p12^2;  
    assert(abs(l2_norm_2 - sqrt(1.5 * 1.5 + 2.5 * 2.5)) < 1e-6);
    std::cout << "Test 15 Passed: L2 norm of p11 = " << l2_norm_2 << "\n";

    std::cout << std::endl;


    std::cout << "Test 16: Invalid norm type\n";
    try {
        double invalid_norm = p12^3;  
        std::cout << "Test 16 Failed: No exception thrown for invalid norm type.\n";
    } catch (const std::invalid_argument& e) {
        std::cout << "Test 16 Passed: Exception caught: " << e.what() << "\n";
    }
}

int main() {
    try {
        runTests();
        std::cout << "\nAll test cases passed successfully.\n";
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
