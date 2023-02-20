#include <iostream>

using namespace std;

class Heap {
    public: 
        int num;
        string str;
        int* ptr = &num;
        int cpnum = *ptr;
        void numPtr() {
            cout << ptr << endl;
        };
};

int main() {
    // Heap sample;
    // sample.num = 10;
    // sample.str = "hello, world!";
    // cout << sample.num << endl;
    // sample.numPtr();
    // cout << sample.cpnum << endl;
    // sample.num = 15;
    // cout << sample.cpnum << endl;
    // return 0;
    int num = 10;
    string str;
    int* ptr = &num;
    int& cpnum = num;
    cout << cpnum << endl;
    num = 15;
    cout << cpnum << endl;
};

