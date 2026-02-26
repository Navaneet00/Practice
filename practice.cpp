#include <iostream>
#include <vector>
#include <memory>
#include <unordered_map>
using namespace std;

// Pass by Reference using pointers
void changeA (int* ptr) {
    *ptr = 25;
}

// Pass by Reference using alias
void changeAUsingAlias (int &b) {
    b = 30;
}

// Pointers Concept
void pointers(){
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


    // Array Pointer (This is const pointer that is, not modifiable)
    int arr[] = {1, 2, 3, 4, 5};
    cout << "Array pointer address: " << arr << endl;
    cout << "Array pointer Zeroth index: " << *arr << endl;
    cout << "Array pointer First index: " << *(arr + 1) << endl;
    cout << "Array pointer Third index: " << *(arr + 3) << endl;


    // Pointer Arithmetic
    int c = 94;
    int* cPtr = &c;

    cout << "Pointer address: " << cPtr << endl;

    cPtr++; // No. of bytes of that variable type is added (+1 => +4 bytes)
    cout << "Pointer new address: " << cPtr << endl;

    cPtr--; // No. of bytes of that variable type is subtracted (-1 => -4 bytes)
    cout << "Pointer updated address: " << cPtr << endl;


    // Subtract pointers
    int* ptr1;
    int* ptr2 = ptr1 + 4;

    cout << "ptr1 - ptr2 = " << ptr1 - ptr2 << endl;
    cout << "ptr2 - ptr1 = " << ptr2 - ptr1 << endl;


    // Compare pointers (<, <=, >, >=, ==, !=)
    int* ptr3;
    int* ptr4;
    
    cout << "ptr3: " << ptr3 << endl;
    cout << "ptr4: " << ptr4 << endl;
    cout << "ptr3 < ptr4 = " << ((ptr3 < ptr4)? "True" : "False") << endl;
    cout << "ptr3 <= ptr4 = " << ((ptr3 <= ptr4)? "True" : "False") << endl;
    cout << "ptr3 > ptr4 = " << ((ptr3 > ptr4)? "True" : "False") << endl;
    cout << "ptr3 >= ptr4 = " << ((ptr3 >= ptr4)? "True" : "False") << endl;
    cout << "ptr3 == ptr4 = " << ((ptr3 == ptr4)? "True" : "False") << endl;
    cout << "ptr3 != ptr4 = " << ((ptr3 != ptr4)? "True" : "False") << endl;
}

// Add function
int add(int num1, int num2){
    return num1+num2;
}

// Stack Memory Allocation Concept (All the variables & functions get memory allocated one by one) - Fixed Memory
void stack(){
    int a = 10, b = 15;

    int sum = add(a, b);
    cout << "Sum: " << sum << endl;
}

// Heap Memory Allocation (Dynamic Memory or Free Store)
void heap(){
    int a = 10;  // stored in stack

    int* p = new int();  // allocate memory in heap
    *p = 10;

    delete(p);  // deallocate memory

    p = new int[4];

    delete[] p;  // Now p is dangling pointer (a pointer that points to a memory location that has been deallocated earlier in the program)

    p = NULL;  // Assign NULL or nullptr to the Pointers that are Not in Use
}


// A program that dynamically allocates an array, fills it, prints it, then frees it
void program1(){
    int n;

    cout<<"Enter number of elements: ";
    cin>>n;

    // Dynamically allocate memory
    int* arr = new int[n];

    // Fill the array
    for(int i = 0; i<n; i++){
        cout<<"Enter the element "<<i+1<<" : ";
        cin>>arr[i];
    }

    // Print the array
    for(int i = 0; i<n; i++){
        cout<<"Element "<<i+1<<" : "<<arr[i]<<endl;
    }

    // Free the allocated memory
    delete[] arr;
}

// A program that demonstrates a dangling pointer (then fix it)
void program2(){
    int* p = new int(20);
    cout << "Value: " << *p << endl;

    delete(p);
    p = nullptr;  // Fix: Remove dangling reference

    if (p != nullptr) {
        cout << *p << endl;
    } else {
        cout << "Pointer is null, cannot access memory." << endl;
    }

    // Or can use this method
    unique_ptr<int> ptr = make_unique<int>(10);

    cout << "Value: " << *ptr << endl;

    // Memory automatically freed when ptr goes out of scope
}


// LeetCode Problem: Remove Duplicates from Sorted Array
int removeDuplicates(vector<int>& arr){
    if (arr.empty()) return 0;

    int k = 1;

    for (int i=1; i<arr.size(); i++){
        if(arr[i] != arr[i-1]){
            arr[k] = arr[i];
            k++;
        }
    }

    for (int i = 0; i < arr.size(); i++) {
        cout << arr[i] << " ";
    }
    cout<<endl;

    return k;
}

// Struct: By Default the members of Struct are public
struct practice{
    int practiceVal = 10;
};

// Class: By Default the members of class are private
class practice1{
    int practiceVal1 = 20;
    const static int practiceVal2 = 35;
    int age;
    string data;

    public:

    // Default Constructor
    practice1(){
        cout << "Constructor called" << endl;
    }

    // Parametrized Constructor
    practice1(string data){
        cout << "Parametrized Constructor called and data is: " << data << endl;
    }

    // Parametrized Constructor (Use Member Initializer List)
    practice1(int age, string data): age(age), data(data){
        cout << "Parametrized Constructor using member initializer list called and age is: " << this->age << " , data is: " << this-> data << endl;
    }

    // Get Data Function
    void getData(int age, string data){
        this->age = age;
        this->data = data;
        cout<< "Age: " << this->age << endl;
        cout<< "Data: " << this->data << endl;
    }

    // Static member function
    static int fun(){
        cout << "Static member function invoked" << endl;
        // cout << "Data member: " << practiceVal1 << endl;  // a nonstatic member reference must be relative to a specific object
        cout << "Data member: " << practiceVal2 << endl;

        return 0;
    }

    // Defining function outside the class using scope resolution operator
    static int newFun();
    int newFun1();

    // Destructor
    ~practice1(){
        cout << "Destructor called" << endl;
    }
};

int practice1::newFun(){
    cout << "Defined static function outside class using scope resolution operator" << endl;
    return 0;
}

int practice1::newFun1(){
    cout << "Defined function outside class using scope resolution operator" << endl;
    return 0;
}

// Access specifiers
class accessSpecifiers {
    private:
    int a;

    protected:
    int b;

    public:
    int c;

    accessSpecifiers() {}
    accessSpecifiers(int a, int b, int c): a(a), b(b), c(c){}

    void setData(){
        a = 19;
        b = 25;
        c = 73;
    }

    void showData(){
        cout << a << " " << b << " " << c << endl;
    }
};

// Child Class of accessSpecifiers
class childAccessSpecifiers : public accessSpecifiers {

    public:
    childAccessSpecifiers(): accessSpecifiers(101, 627, 829){
        cout << "Value of 'b' printed using child class function: " << b << endl;
    }
};

// Program 3: BankAccount
class BankAccount {
    private:
    double balance;
    static int totalAccounts;

    public:

    // Constructor
    BankAccount(double initialBalance = 0.0){
        if(initialBalance >= 0){
            balance = initialBalance;
        }
        else{
            balance = 0.0;
        }
        totalAccounts++;
    }

    // Deposit money
    void deposit(double amount){
        if(amount > 0){
            balance += amount;
            cout << "Amount accepted" << endl;
        }
        else{
            cout << "Invalid amount" << endl;
        }
    }

    // Withdraw money
    void withDraw(double amount){
        if(amount <= 0){
            cout << "Invalid amount" << endl;
        }
        else if(amount > balance){
            cout << "Insufficient balance!" << endl;
        }
        else {
            balance -= amount;
            cout << "Withdraw successful!: " << amount << endl;
        }
    }

    // Get Current Balance
    double getBalance() {
        return balance;
    }

    // Get Total Accounts
    static int getAccounts() {
        return totalAccounts;
    }
};

int BankAccount::totalAccounts = 0;

bool isValid(string s) {
    unordered_map<char, char> mp = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    stack<char> st;

    for (char c : s) {
        if (mp.count(c) == 0) {
            st.push(c);
        } else {
            if (st.empty() || st.top() != mp[c])
                return false;
            st.pop();
        }
    }

    return st.empty();
}


int main() {

    // Pointers Concept
    // pointers();

    // Stack Memory Allocation (If many variables & functions occur, this can overflow or can overflow from recursive function, if no ending point)
    // stack();

    // Heap Memory Allocation 
    // heap();

    // Program 1
    // program1();

    // Program 2
    // program2();

    // LeetCode Problem 1
    // vector<int> arr = {1, 1, 2, 3, 4, 4, 5, 5, 5, 5, 6};
    // int k = removeDuplicates(arr);
    // cout<<"k: "<<k;

    // Struct vs Class
    // practice p;
    // practice1 p1;
    // cout << 10*p.practiceVal << endl;  // 100
    // cout << 10*p1.practiceVal1 << endl;  // member "practice1::practiceVal1" (declared at line 203) is inaccessible

    // Constructor Vs Destructor & Use of 'this' pointer in getData function
    // practice1 p1, p2("Hello"), p3(195, "Henry");
    // p1.getData(10, "Harry");

    // Static member function & Usage of Scope Resolution operator
    // practice1::fun();
    // practice1::newFun();
    // practice1 p1;
    // p1.newFun1();

    // Access specifiers
    // accessSpecifiers aS;
    // aS.setData();
    // aS.showData();
    // // cout << "Data 'a': " << aS.a << endl;  // member "accessSpecifiers::a" (declared at line 265) is inaccessible
    // // cout << "Data 'b': " << aS.b << endl;  // member "accessSpecifiers::b" (declared at line 268) is inaccessible
    // cout << "Data 'c': " << aS.c << endl;
    // // aS.a = 100;  // member "accessSpecifiers::a" (declared at line 265) is inaccessible
    // // aS.b = 256;  // member "accessSpecifiers::b" (declared at line 268) is inaccessible
    // aS.c = 624;
    // cout << "New 'c': " << aS.c << endl;
    // childAccessSpecifiers cAS;

    // Program 3: BankAccount
    // BankAccount account(1890), account1(902);
    // account.deposit(-19);
    // account.deposit(110);
    // account.withDraw(15000);
    // account.withDraw(1000);
    // cout << "Current balance: " << account.getBalance() << endl;
    // cout << "Total Accounts: " << BankAccount::getAccounts() << endl;

    return 0;
}