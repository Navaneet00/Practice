#include <iostream>
#include <vector>
using namespace std;

// Pass by Reference using pointers
void changeA (int* ptr) {
    *ptr = 25;
}

// Pass by Reference using alias
void changeAUsingAlias (int &b) {
    b = 30;
}

int main() {

    int a = 10;

    // Print the memory address of a (which is Hexadecimal)
    cout << "Address of a: " << &a << endl;
    cout << "Value of a: " << a << endl;

    changeA(&a);
    cout << "New value of a: " << a << endl;

    changeAUsingAlias(a);
    cout << "Updated value of a: " << a << endl;

    // Create pointer
    int* ptr = &a;
    cout << "Pointer value: " << ptr << endl;
    cout << "Pointer address: " << &ptr << endl;

    // Create parent pointer
    int** parPtr = &ptr;
    cout << "Parent Pointer value: " << parPtr << endl;

    // Deference value a, ptr & parPtr (Deference - Gets the value stored at the address)
    cout << "Deference value of a: " << *(&a) << endl;
    cout << "Deference value of ptr: " << *(&ptr) << endl;
    cout << "Deference value of parPtr: " << *(&parPtr) << endl;

    // NULL Pointer
    int* nullPtr = NULL;
    cout << "Pointer value: " << nullPtr << endl;
    cout << "NULL Pointer address: " << &nullPtr << endl;
    // cout << "Deference NULL Pointer: " << *nullPtr << endl;

    return 0;
}