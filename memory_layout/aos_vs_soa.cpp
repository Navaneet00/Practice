#include <iostream>
#include <vector>
#include <chrono>
using namespace std;

// AoS
struct Order{
    uint64_t id;
    double price;
    int quantity;
};

// SoA
struct Orders{
    vector<uint64_t> ids;
    vector<double> prices;
    vector<int> quantities;
};

const size_t N = 100000000;

int main(){

    // AoS Execution
    {
        vector<Order> orders(N);

        for(size_t i = 0; i < N; i++){
            orders[i] = {i, 100.0 + i, 10};
        }

        auto start = chrono::high_resolution_clock::now();

        double sum = 0;
        for(size_t i = 0; i < N; i++){
            sum += orders[i].price;
        }

        auto end = chrono::high_resolution_clock::now();

        cout << "AoS Execution Time: " << chrono::duration_cast<chrono::milliseconds>(end-start).count() << " ms." << endl;
    }

    // SoA Execution
    {
        Orders orders;
        orders.ids.resize(N);
        orders.prices.resize(N);
        orders.quantities.resize(N);

        for(size_t i = 0; i < N; i++){
            orders.ids[i] = i;
            orders.prices[i] = 100.0+i;
            orders.quantities[i] = 10;
        }

        auto start1 = chrono::high_resolution_clock::now();

        double sum1 = 0;
        for(size_t i = 0; i < N; i++){
            sum1 += orders.prices[i];
        }

        auto end1 = chrono::high_resolution_clock::now();

        cout << "SoA Execution Time: " << chrono::duration_cast<chrono::milliseconds>(end1-start1).count() << " ms." << endl;
    }

    return 0;
}


// Output
// AoS Execution Time: 1152 ms.
// SoA Execution Time: 245 ms.