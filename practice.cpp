#include <iostream>
#include <vector>
#include <stack>
#include <memory>
#include <unordered_map>
#include <map>
#include <stack>
#include <sstream>
#include <algorithm>
#include <numeric>
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

// Is Parentheses valid function
bool isValid(string s) {
    unordered_map<char, char> mp = {
        {')', '('},
        {'}', '{'},
        {']', '['}
    };

    std::stack<char> st;

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

// Pure Virtual Function Example
class Shape {
    public:
    virtual void draw() = 0;

    virtual ~Shape(){
        cout << "Shape Destructor" << endl;
    }
};

class Circle : public Shape {
    public:
    void draw() override {
        cout << "Draw a circle" << endl;
    }

    ~Circle(){
        cout << "Circle Destructor" << endl;
    }
};

class Triangle : public Shape {
    public:
    void draw(){
        cout << "Draw a Triangle" << endl;
    }

    ~Triangle(){
        cout << "Triangle Destructor" << endl;
    }
};

// Ordered Vs Unordered Map
void orderedVsUnorderedMap(){

    // Ordered map
    map<string, int> ordered;

    ordered["Hi"] = 5;
    ordered["Hello"] = 9;
    ordered["Bye"] = 11;

    cout << "Ordered map" << endl;
    for (auto i = ordered.begin(); i != ordered.end(); i++){
        cout << i->first << " : " << i->second << endl;
    }

    // Unordered map
    unordered_map<string, int> unOrdered;

    unOrdered["Hello"] = 10;
    unOrdered["Bye"] = 13;
    unOrdered["Hey"] = 19;

    cout << "Unordered map" << endl;
    for (auto i = unOrdered.begin(); i != unOrdered.end(); i++){
        cout << i->first << " : " << i->second << endl;
    }
}

// Word and Character Frequency counter
void wordCharFrequencyCounter(string sentence){
    unordered_map<string, int> wordFreq;
    unordered_map<char, int> charFreq;

    stringstream ss(sentence);
    string word;
    char character;

    while (ss >> word){
        wordFreq[word]++;

        stringstream ss1(word);
        while (ss1 >> character){
            charFreq[character]++;
        }
    }

    if(!wordFreq.empty()){
        cout << "Word Frequency - " << endl;
        for (auto it = wordFreq.begin(); it != wordFreq.end(); it++){
            cout << it->first << " : " << it->second << endl;
        }

        cout << endl;
        cout << "Character Frequency - " << endl;
        for (auto it = charFreq.begin(); it != charFreq.end(); it++){
            cout << it->first << " : " << it->second << endl;
        }
    }
    else {
        cout << "Map is empty" << endl;
    }
}

// Is Parentheses Balanced
bool isBalanced(string s) {
    std::stack<char> st;

    for (char c : s){
        if (c == '(' || c == '{' || c == '['){
            st.push(c);
        }
        else{
            if (st.empty()){
                return false;
            }

            char top = st.top();
            st.pop();

            if ((c == '}' && top != '{') || (c == ')' && top != '(') || (c == ']' && top != '[')){
                return false;
            }
        }
    }

    return st.empty();
}

// sort(), find(), count(), accumulate(), min_element(), max_element(), upper_bound() and lower_bound()
void vectorFunctions(vector<int>& v1){
    // Before sorting
    cout << "Before sorting: ";
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
        cout << *it << " ";
    }

    sort(v1.begin(), v1.end());

    // After sorting
    cout << endl << "After sorting: ";
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
        cout << *it << " ";
    }
    
    int targetVal = 31;
    cout << endl << "Is " << targetVal << " found? " << ((find(v1.begin(), v1.end(), targetVal) != v1.end())? "True" : "False") << endl;

    int targetFreq = 62;
    cout << "Frequency of " << targetFreq << ": " << count(v1.begin(), v1.end(), 62) << endl;

    cout << "Sum: " << accumulate(v1.begin(), v1.end(), 0) << endl;

    cout << "Minimum value in vector: " << *min_element(v1.begin(), v1.end()) << endl;

    cout << "Maximum value in vector: " << *max_element(v1.begin(), v1.end()) << endl;

    cout << "Upper bound of " << targetVal << " in vector: " << *upper_bound(v1.begin(), v1.end(), targetVal) << endl;
    cout << "Lower bound of " << targetVal << " in vector: " << *lower_bound(v1.begin(), v1.end(), targetVal) << endl;
}

// Lambda Capture Clause
void lambdaCaptureClause(vector<int> v1, vector<int> v2) {
    // Capture values by Value
    auto lambda = [v1]() {
        cout << "v1: ";
        for (int num : v1){
            cout << (num += 1) << " ";
        }
        cout << endl;
    };

    lambda();

    // Capture values by Reference
    auto lambda1 = [&v2](){
        for (int& num : v2){
            num += 1;
        }
    };

    lambda1();

    // Capture values by Reference and Value
    auto lambda2 = [&v1, v2](){
        for (int& num : v1){
            num *= 2;
        }

        cout << "v2: ";
        for (int num : v2){
            cout << (num += 2) << " ";
        }
        cout << endl;
    };

    lambda2();

    cout << "v1: ";
    for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
        cout << *it << " ";
    }

    cout << endl;

    cout << "v2: ";
    for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++){
        cout << *it << " ";
    }
}

// Function Template
template <typename T> T maxValue(T x, T y){
    return x > y ? x : y;
}

// Class Template
template <typename T> class Geek{
    public:
    T x;
    T y;

    // Constructor
    Geek(T val1, T val2) : x(val1), y(val2){}

    // Method to get the values
    void getValues(){
        cout << x << " " << y << endl;
    }
};

// Template Variable
template <typename T> constexpr T pi = T(3.14);


// Student class
class Student {
    public:
    string name;
    double grade;

    Student(string val1, double val2) : name(val1), grade(val2){}
};

// Sort a vector of custom objects (students by grade) using lambda
void sortStudentsByGrade(vector<Student>& students){

    sort(students.begin(), students.end(), [](const Student& a, const Student& b){
        return a.grade > b.grade;
    });

    for (auto& s : students){
        cout << s.name << ": " << s.grade << endl;
    }
}

// Find Max Value Function Template
template <typename T> T findMax(T x, T y) {
    return x > y ? x : y;
}

// Use accumulate with a lambda to compute product of all elements
void productOfAllElements(vector<int>& v1){

    cout << accumulate(v1.begin(), v1.end(), 1, [](int a, int b){
        return a * b;
    }) << endl;
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

    // Valid Parentheses - LeetCode Problem 2
    // bool valid = isValid("{](");
    // cout << "Is '{](' valid? " << ((valid)? "True" : "False") << endl;

    // Illustrating Pure Virtual Function
    // Shape* ptr;
    // Circle c;
    // ptr = &c;
    // ptr->draw();

    // Illustrating Pure Virtual Function & Virtual Destructor using smart pointers
    // vector<unique_ptr<Shape>> shapes;
    // shapes.push_back(make_unique<Circle>());
    // shapes.push_back(make_unique<Triangle>());
    // for(const auto& s : shapes){
    //     s->draw();
    // }

    // Ordered Vs Unordered map
    // orderedVsUnorderedMap();

    // Tuple And Pair
    // tuple<int, string, char> t1 = make_tuple(5, "Hi", 'c');
    // pair<int, string> p1 = make_pair(14, "Hello");
    // cout << "First element of Tuple: " << get<0>(t1) << endl;
    // cout << p1.first << " : " << p1.second << endl;

    // Iterators
    // vector<int> v1 = {10, 40, 25, 82, 33, 91};
    // for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++){
    //     cout << *it << " ";
    // }
    // cout << endl;
    // for (vector<int>::reverse_iterator it = v1.rbegin(); it != v1.rend(); it++){
    //     cout << *it << " ";
    // }

    // Word and Character Frequency Counter
    // wordCharFrequencyCounter("This is very awesome and this is very nice and pretty.");

    // Balanced Parentheses Using Stack
    // cout << (isBalanced("([{}])")? "True" : "False") << endl;

    // Vector Functions
    // vector<int> v1 = {53, 62, 31, 12, 92, 66, 27, 62, 62};
    // vectorFunctions(v1);

    // Lambda Capture Clause
    // vector<int> v1 = {10, 30, 20, 40, 50};
    // vector<int> v2 = {50, 60, 30, 10, 90, 40, 20};
    // lambdaCaptureClause(v1, v2);

    // Use of function template
    // cout << maxValue<int>(7, 5) << endl;
    // cout << maxValue<char>('g', 't') << endl;
    // cout << maxValue<double>(9.8, 2.2) << endl;

    // Use of class template
    // Geek<string> geek("Hi", "Hello");
    // geek.getValues();

    // Use of template variable
    // cout << "Pi as float: " << pi<float> << endl;
    // cout << "Pi as int: " << pi<int> << endl;

    // Sort students by grade
    // vector<Student> students = {
    //     Student("Anand", 78.0),
    //     Student("Akash", 85.8),
    //     Student("Aditya", 66.9),
    //     Student("Bharat", 91.0),
    //     Student("Akash", 83.6),
    //     Student("Anirudh", 72.8),
    // };
    // sortStudentsByGrade(students);

    // Find Max Value using Function template
    // cout << findMax<int>(9, 2) << endl;
    // cout << findMax<float>(2.3, 2.9) << endl;
    // cout << findMax<string>("Hi", "Hello") << endl;

    // Product of all elements using accumulate with lambda
    // vector<int> v1 = {2, 3, 4, 5};
    // productOfAllElements(v1);

    return 0;
}