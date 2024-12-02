#include "custommap.hpp"

int main(void) {
    CustomMap<int, string> map;
    map.insert(5, "Five");
    // map.insert(3, "Three");
    map.insert(8, "Eight");
    map.insert(10, "Ten");
    map.insert(7, "Seven");
    // map.insert(2, "Two");
    // map.insert(4, "Four");
    map.insert(9, "Nine");
    // map.insert(1, "One");
    map.insert(12, "Twelve");
    map.insert(11, "Eleven");

    // map.print_map();

    map.deleteKey(5);
    map.print_map();



}