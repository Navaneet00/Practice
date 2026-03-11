#include <thread>
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
using namespace std;

mutex mtx;
queue<int> buffer;
const int MAX_SIZE = 10;
condition_variable cv_full, cv_empty;

// Producer
void producer(int id){
    for (int i = 0; i < 20; i++){
        unique_lock<mutex> lock(mtx);
        cv_full.wait(lock, []{ return buffer.size() < MAX_SIZE; });
        buffer.push(i);
        cout << "Producer " << id << " produced: " << i << endl;
        cv_empty.notify_one(); // Tells consumer that data is available
    }
}

// Consumer
void consumer(int id){
    for (int i = 0; i < 20; i++){
        unique_lock<mutex> lock(mtx);
        cv_empty.wait(lock, []{ return !buffer.empty(); });
        int val = buffer.front();
        buffer.pop();
        cout << "Consumer " << id << " consumed: " << val << endl;
        cv_full.notify_one(); // Tells producer that space is available
    }
}

int main(){
    thread p(producer, 1), c(consumer, 1);
    p.join(), c.join();
    return 0;
}