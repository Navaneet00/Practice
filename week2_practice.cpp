#include <thread>
#include <iostream>
#include <mutex>
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

    cout << "Main thread awake and finished!";
    return 0;
}