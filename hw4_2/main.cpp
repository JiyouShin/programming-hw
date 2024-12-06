#include "prob2.hpp"
#include <iostream>

int main() {
    
    int n1 = 6;
    std::vector<std::pair<int, int>> comparisons1 = {{1, 5}, {3, 4}, {5, 4}, {4, 2}, {4, 6}, {5, 2}}; 

    int n2 = 4;
    std::vector<std::pair<int, int>> comparisons2 = {};

    int n3 = 5;
    std::vector<std::pair<int, int>> comparisons3 = {{1, 2}, {2, 3}, {4, 5}};

    int n4 = 4;
    std::vector<std::pair<int, int>> comparisons4 = {{1, 2}, {1, 3}, {1, 4}, {2, 3}, {2, 4}, {3, 4}};

    int n5 = 3;
    std::vector<std::pair<int, int>> comparisons5 = {{1, 2}, {2, 3}, {3, 1}};


    std::cout << findKnownOrderStudents(n1, comparisons1) << std::endl;
    std::cout << findKnownOrderStudents(n2, comparisons2) << std::endl;
    std::cout << findKnownOrderStudents(n3, comparisons3) << std::endl;
    std::cout << findKnownOrderStudents(n4, comparisons4) << std::endl;
    std::cout << findKnownOrderStudents(n5, comparisons5) << std::endl;

    return 0;
}
