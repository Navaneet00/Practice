#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

// Cache line aligned
struct alignas(64) PaddedData{
    long long a = 0;
};

struct SharedData{
    PaddedData x;
    PaddedData y;
};

const long long ITER = 100000000;

int main(){

    SharedData data;

    auto start = chrono::high_resolution_clock::now();

    thread t1([&](){
        for(long long i = 0; i < ITER; i++){
            data.x.a++;
        }
    });

    thread t2([&](){
        for(long long i = 0; i < ITER; i++){
            data.y.a++;
        }
    });

    t1.join();
    t2.join();

    auto end = chrono::high_resolution_clock::now();

    cout << "Time (padded): " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms." << endl;

    return 0;
}