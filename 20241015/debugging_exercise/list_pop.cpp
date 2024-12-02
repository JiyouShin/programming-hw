#include <list>
#include <iostream>

using namespace std;

int main(){
    list<int> lst = {1,2,3,4,5};

    // i want to practice using pop_back function in list!
    for(int v : lst){
        lst.pop_back();
        // cout << "popped" << endl;
    }
    return 0;
}