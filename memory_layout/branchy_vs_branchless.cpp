#include <iostream>
#include <chrono>
#include <random>
using namespace std;

const int N = 100000000;
vector<int> arr(N);

// Fill with random positive and negative numbers
void fillRandom(){
    mt19937 rng(42);
    uniform_int_distribution<int> dist(-100, 100);
    for(int i = 0; i < N; i++){
        arr[i] = dist(rng);
    }
}

// Branchy version - branch misprediction on random data
long long sumBranchy(){
    long long sum = 0;
    for(int i = 0; i < N; i++){
        if(arr[i] > 0){          // unpredictable branch on random data
            sum += arr[i];
        }
    }
    return sum;
}

// Branchless version - no conditional, pure arithmetic (multiplication trick)
long long sumBranchless(){
    long long sum = 0;
    for(int i = 0; i < N; i++){
        sum += arr[i] * (arr[i] > 0);  // multiply by 1 or 0
    }
    return sum;
}

int main(){

    fillRandom();

    auto start1 = chrono::high_resolution_clock::now();
    long long branchySum = sumBranchy();
    auto end1 = chrono::high_resolution_clock::now();

    auto start2 = chrono::high_resolution_clock::now();
    long long branchlessSum = sumBranchless();
    auto end2 = chrono::high_resolution_clock::now();

    cout << "Branchy version: " << chrono::duration_cast<chrono::milliseconds>(end1-start1).count() << " ms. And Sum is: " << branchySum << endl;
    cout << "Branchless version: " << chrono::duration_cast<chrono::milliseconds>(end2-start2).count() << " ms. And Sum is: " << branchlessSum << endl;

    return 0;
}