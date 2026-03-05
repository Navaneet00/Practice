#include <thread>
#include <iostream>
#include <mutex>
#include <chrono>
#include <future>
#include <queue>
#include <condition_variable>
using namespace std;

// Function
void func(){
    cout << "Hello from the thread! Thread Id: " << this_thread::get_id() << endl;
}

// Shared resource
int number = 0;

// Create mutex
mutex mtx;

// Condition variable
condition_variable cv;

// function to avoid spurios wakeup
bool data_ready = false;

// producer function working as sender
void producer(){

    // Simulate data production
    this_thread::sleep_for(chrono::seconds(2));

    // lock release
    lock_guard<mutex> lock(mtx);

    // variable to avoid spurious wakeup
    data_ready = true;

    // logging notification to console
    cout << "Data Produced!" << endl;

    // notify consumer when done
    cv.notify_one();
}

// consumer that will consume what producer has produced
// working as reciever
void consumer(){

    // locking
    unique_lock<mutex> lock(mtx);

    // waiting
    cv.wait(lock, []{
        return data_ready;
    });

    cout << "Data consumed!" << endl;
}

// Increment function
void increment(){

    // Lock the thread using lock()
    mtx.lock();

    for (int i = 0; i < 1000000; i++){
        number++;
    }

    // Release the lock using unlock()
    mtx.unlock();
}

// Get Thread Id with a message
void getId(int num){
    lock_guard<mutex> lock(mtx);
    cout << "Thread " << num << " is running!" << endl;
}

// Use of future class template and async function template
int get_the_answer(){
    this_thread::sleep_for(chrono::seconds(2));
    return 45;
}

// Using future with promise
void get_answer(promise<int> p){
    p.set_value(44);
}

// Thread Pool
class ThreadPool{
    public:

    // Constructor to create a thread pool with given number of threads
    ThreadPool(size_t num_threads = thread::hardware_concurrency())
    {
        // Creating worker threads
        for (size_t i = 0; i < num_threads; i++){
            threads.emplace_back([this] {
                while(true){
                    function<void()> task;

                    {
                        // Locking the queue so that data can be shared safely
                        unique_lock<mutex> lock(queue_mutex);

                        // Waiting until there is a task to execute or the pool is stopped
                        cv.wait(lock, [this]{
                            return !tasks.empty() || stopPool;
                        });

                        // Exit the thread if there are no tasks and pool is stopped
                        if(tasks.empty() && stopPool){
                            return;
                        }

                        // Get the next task from the queue
                        task = move(tasks.front());
                        tasks.pop();
                    }

                    task();
                }
            });
        }
    }

    // Destructor to stop thread pool
    ~ThreadPool()
    {
        {
            // Lock the queue to update the flag safely
            unique_lock<mutex> lock(queue_mutex);
            stopPool = true;
        }

        // Notify all threads
        cv.notify_all();

        // Joining all worker threads to ensure that they have completed their tasks
        for(auto& thread : threads){
            thread.join();
        }
    }

    // Enqueue task for execution by the thread pool
    void enqueue(function<void()> task)
    {
        {
            unique_lock<mutex> lock(queue_mutex);
            tasks.emplace(move(task));
        }
        cv.notify_one();
    }


    private:

    // Vector to store worker threads
    vector<thread> threads;

    // Queue of tasks
    queue<function<void()>> tasks;

    // Mutex to synchronize access to shared data
    mutex queue_mutex;

    // Condition variable to signal changes in the state of tasks queue
    condition_variable cv;

    // Flag to indicate whether thread pool should stop or not
    bool stopPool = false;
};

// cout Mutex
mutex cout_mutex;

// Deadlock Example (Two Mutexes)
mutex mt1, mt2;

// Thread1 function
void thread1() {
    lock_guard<mutex> lock1(mt1);
    this_thread::sleep_for(chrono::milliseconds(500));

    lock_guard<mutex> lock2(mt2);
    cout << "Thread1 finished!" << endl;
}

// Thread2 function
void thread2() {
    lock_guard<mutex> lock2(mt2);
    this_thread::sleep_for(chrono::milliseconds(500));

    lock_guard<mutex> lock1(mt1);
    cout << "Thread2 finished!" << endl;
}

// Deadlock-free locking
void safeTask(){
    lock(mt1, mt2);

    lock_guard<mutex> lock1(mt1, adopt_lock);
    lock_guard<mutex> lock2(mt2, adopt_lock);

    cout << "Tasks executed safely\n";
}

// Move Constructor Demo
class Practice {
    private:
    int* ptr;

    public:

    // Constructor
    Practice(int value){

        // Dynamically allocate memory
        ptr = new int(value);
        cout << "Constructor called!" << endl;
    }

    // Noexcept Move Constructor 
    Practice(Practice&& obj) noexcept {
        cout << "Move constructor called!" << endl;

        // Steal the pointer
        ptr = obj.ptr;
        obj.ptr = nullptr;
    }

    ~Practice(){
        if(ptr != nullptr){
            cout << "Destructor deleting data: " << *ptr << endl;
        }
        else{
            cout << "Destructor called on nullptr" << endl;
        }
        delete ptr;
    }

    // Display function
    void display(){
        if(ptr){
            cout << "Pointer value: " << *ptr << endl;
        }
        else{
            cout << "No value" << endl;
        }
    }
};


// Resource Manager for Execution of Rule of Five
class ResourceManager{
    private:
    int* data;
    size_t size;

    public:

    // Default Constructor
    ResourceManager(size_t sz=0) : data(new int[sz]), size(sz){
        cout << "Default Constructor called!" << endl;
    }

    // Destructor
    ~ResourceManager(){
        delete[] data;
        cout << "Destructor called!" << endl;
    }

    // Copy Constructor
    ResourceManager(const ResourceManager& other) : data(new int[other.size]), size(other.size){
        copy(other.data, other.data + other.size, data);
        cout << "Copy Constructor Called!" << endl;
    }

    // Copy Assignment Operator
    ResourceManager& operator=(const ResourceManager& other){
        if(this != &other){
            delete[] data;
            data = new int[other.size];
            size = other.size;
            copy(other.data, other.data + other.size, data);
        }
        cout << "Copy Assignment Operator Is Called!" << endl;
        return *this;
    }

    // Move Constructor
    ResourceManager(ResourceManager&& other) noexcept : data(other.data), size(other.size){
        other.data = nullptr;
        other.size = 0;
        cout << "Move Constructor Called!" << endl;
    }

    // Move Assignment Operator
    ResourceManager& operator=(ResourceManager&& other){
        if(this != &other){
            delete[] data;
            data = other.data;
            size = other.size;
            other.data = nullptr;
            other.size = 0;
        }
        cout << "Move Assignment Operator Is Called!" << endl;
        return *this;
    }
};


// Shared Counter Using atomic<int> (No Mutex)
atomic<int> counter(0);

void increment1(){
    for(int i = 0; i < 100000; i++){
        counter++;
    }
}


// Benchmark: Mutex vs Atomic (1 Million Increments)
const int numThreads = 10;
const int increments = 1000000;

// --- Mutex Part ---
mutex mtxMillion;
int mtxCounter = 0;

void incrementMillion(){
    for (int i = 0; i < increments; i++){
        lock_guard<mutex> lock(mtxMillion);
        mtxCounter++;
    }
}

// --- Atomic Part ---
atomic<int> atomicCounter(0);

void incrementMillion1(){
    for (int i = 0; i < increments; i++){
        atomicCounter++;
    }
}


// Lock-free flag using atomic<bool>
atomic<bool> ready(false);

void worker(){
    if(!ready.load()){
        // spin-wait
    }

    cout << "Worker proceeding after signal!" << endl;
}



int main() {

    // // Create new thread
    // thread t(func);
    
    // // Check if thread is joinable
    // if(t.joinable()){
    //     t.join();
    // }

    // // To detach a thread from main thread
    // // t.detach();

    // // Main thread sleeping for 1 second
    // cout << "Main thread sleeping for 1 second..." << endl;
    // this_thread::sleep_for(chrono::seconds(1));



    // int n = 3;
    // thread t1([](int n){
    //     cout << "Number: " << n;
    // }, n);

    // t1.join();
    // cout << endl;



    // // Create thread t2 & t3 to perform increment
    // thread t2(increment);
    // thread t3(increment);

    // t2.join();
    // t3.join();

    // // Print the number after the execution of both threads
    // cout << "Number after execution of t1 and t2 is " << number << endl;



    // Use of Condition Variable
    // thread consumer_thread(consumer);
    // thread producer_thread(producer);

    // consumer_thread.join();
    // producer_thread.join();



    // // Create 5 Threads → Observe Race Condition & Fix Using mutex
    // thread t1(getId, 1);
    // thread t2(getId, 2);
    // thread t3(getId, 3);
    // thread t4(getId, 4);
    // thread t5(getId, 5);

    // t1.join();
    // t2.join();
    // t3.join();
    // t4.join();
    // t5.join();



    // // Launch the function asynchronously and get a future
    // future<int> future_value = async(launch::async, get_the_answer);

    // // Do other work while waiting
    // cout << "Doing other work..." << endl;

    // // Wait for the result and get it
    // // The call to .get() will block if the result isn't ready yet
    // cout << "Future value: " << future_value.get() << endl;



    // // Using future with promise
    // promise<int> p;
    // future<int> f1 = p.get_future();
    // thread t(get_answer, move(p));
    // t.join();
    // cout << "Future value: " << f1.get() << endl;



    // // Create a thread pool with 4 threads
    // ThreadPool pool(4);

    // // Enqueue tasks for execution
    // for(int i = 0; i < 5; ++i){
    //     pool.enqueue([i]{
    //         unique_lock<mutex> lock(cout_mutex);
    //         cout << "Task " << i << " is running by Thread " << this_thread::get_id() << endl;

    //         // Simulate some work
    //         this_thread::sleep_for(chrono::microseconds(10));
    //     });
    // }



    // // Deadlock Example (Two Mutexes)
    // thread t1(safeTask);
    // thread t2(safeTask);
    // t1.join();
    // t2.join();


    // Move constructor demo
    // Practice p(40);
    // Practice p1 = move(p);
    // cout << "display p: ";
    // p.display();
    // cout << "display p1: ";
    // p1.display();


    // // Move Assignment Operator
    // vector<int> a = {1, 2, 3, 4};
    // vector<int> b;
    // cout << "Before moving" << endl;
    // cout << "Size of a: " << a.size() << endl;
    // cout << "Size of b: " << b.size() << endl;
    // b = move(a);  // Move assignment
    // cout << "After moving" << endl;
    // cout << "Size of a: " << a.size() << endl;
    // cout << "Size of b: " << b.size() << endl;


    // // ResourceManager - Execution of Rule of Five
    // ResourceManager r1(10);
    // ResourceManager r2 = r1;
    // ResourceManager r3;
    // r3 = r1;
    // ResourceManager r4 = move(r1);
    // ResourceManager r5;
    // r5 = move(r1);


    // Shared Counter Using atomic<int> (No Mutex)
    // cout << "Counter value before incrementing: " << counter << endl;
    // vector<thread> threads;
    // for(int i = 0; i < 5; i++){
    //     threads.emplace_back(increment1);
    // }
    // for(thread& t : threads){
    //     t.join();
    // }
    // cout << "Counter value after incrementing: " << counter << endl;


    // // Benchmark: Mutex vs Atomic (1 Million Increments)
    // {
    //     // --- Mutex Benchmark ---

    //     auto start = chrono::high_resolution_clock::now();

    //     vector<thread> threads;
    //     mtxCounter = 0;

    //     for (int i = 0; i < numThreads; i++){
    //         threads.emplace_back(incrementMillion);
    //     }

    //     for (thread& t : threads){
    //         t.join();
    //     }
    
    //     auto end = chrono::high_resolution_clock::now();

    //     cout << "Mutex counter value: " << mtxCounter << endl;
    //     cout << "Mutex Time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms." << endl;
    // }

    // {
    //     // --- Atomic Benchmark ---
    //     atomicCounter = 0;

    //     auto start = chrono::high_resolution_clock::now();

    //     vector<thread> threads;

    //     for (int i = 0; i < numThreads; i++){
    //         threads.emplace_back(incrementMillion1);
    //     }

    //     for (thread& t : threads){
    //         t.join();
    //     }

    //     auto end = chrono::high_resolution_clock::now();

    //     cout << "Atomic counter value: " << atomicCounter << endl;
    //     cout << "Atomic Time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms." << endl;
    // }


    // Lock-Free Flag using atomic<bool>
    // thread t(worker);
    // this_thread::sleep_for(chrono::seconds(10));
    // ready.store(true);   // signal
    // t.join();


    // {
    //     // Measure Performance: Copy vs Move Vector
    //     vector<int> big = {50'000'000, 4, 82};

    //     auto start1 = chrono::high_resolution_clock::now();
    //     vector<int> otherBig = big;
    //     auto end1 = chrono::high_resolution_clock::now();

    //     cout << "Time taken for 'copy': " << chrono::duration_cast<chrono::microseconds>(end1-start1).count() << " ms." << endl;

    //     auto start2 = chrono::high_resolution_clock::now();
    //     vector<int> anotherBig = move(big);
    //     auto end2 = chrono::high_resolution_clock::now();

    //     cout << "Time taken for 'move': " << chrono::duration_cast<chrono::microseconds>(end2-start2).count() << " ms." << endl;
    // }


    cout << "Main thread awake and finished!" << endl;
    return 0;
}