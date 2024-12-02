#include <string>
#include <iostream>

using namespace std;

int operator+(const string &lhs, const int rhs){
    return 1;
}

int operator+(string &lhs, const int rhs){
    return 2;
}

int operator+(const string &lhs, const string rhs){
    return 3;
}

int operator+(string &lhs, const string rhs){
    return 4;
}


int main(){
    string str1 = "Hello ";
    string str2 = "World!";
    int result1 = str1 + 3;
    int result2 = str1 + str2;
    cout << "result1: " << result1 << endl;
    cout << "result2: " << result2 << endl;
    return 0;
}

