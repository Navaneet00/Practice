#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

struct SharedData{
    long long a = 0;
    long long b = 0;   // Adjacent in memory -> same cache line
};

const long long ITER = 100000000;

int main(){

    SharedData data;

    auto start = chrono::high_resolution_clock::now();

    thread t1([&](){
        for(long long i = 0; i < ITER; i++){
            data.a++;
        }
    });

    thread t2([&](){
        for(long long i = 0; i < ITER; i++){
            data.b++;
        }
    });

    t1.join();
    t2.join();

    auto end = chrono::high_resolution_clock::now();

    cout << "Time (false sharing): " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms." << endl;

    return 0;
}