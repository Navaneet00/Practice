#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int v;
    int wt;

    Edge(int vertex, int weight) : v(vertex), wt(weight){}
};

// Dijkstra's Algorithm (Only for +ve weighted graphs)
void dijkstra(int src, vector<vector<Edge>> g, int V){
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    // priority_queue<pair<int, int>> pq;   // This is Max-heap but we want Min-heap
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({0, src});

    while(!pq.empty()){
        int u = pq.top().second;
        pq.pop();

        for(Edge e : g[u]){
            if(dist[e.v] > dist[u] + e.wt){
                dist[e.v] = dist[u] + e.wt;
                pq.push({dist[e.v], e.v});
            }
        }
    }

    // Print Distances
    for(int d : dist){
        cout << d << " ";
    }
    cout << endl;
}

// Bellman Ford Algorithm
void bellmanFord(int src, vector<vector<Edge>> g, int V){
    vector<int> dist(V, INT_MAX);
    dist[src] = 0;

    for(int i = 0; i < V-1; i++){
        for(int u = 0; u < V; u++){
            for(Edge e : g[u]){
                if(dist[e.v] > dist[u] + e.wt){
                    dist[e.v] = dist[u] + e.wt;
                }
            }
        }
    }

    // Print Distances
    for(int d : dist){
        cout << d << " ";
    }
    cout << endl;
}

int main(){

    // // Dijkstra's Algorithm
    // {
    //     int V = 6;
    //     vector<vector<Edge>> g(V);

    //     g[0].push_back(Edge(1, 2));
    //     g[0].push_back(Edge(2, 4));

    //     g[1].push_back(Edge(2, 1));
    //     g[1].push_back(Edge(3, 7));

    //     g[2].push_back(Edge(4, 3));

    //     g[3].push_back(Edge(5, 1));

    //     g[4].push_back(Edge(3, 2));
    //     g[4].push_back(Edge(5, 5));

    //     dijkstra(0, g, V);
    // }

    // Bellman Ford Algorithm
    {
        int V = 5;
        vector<vector<Edge>> g(V);

        g[0].push_back(Edge(1, 2));
        g[0].push_back(Edge(2, 4));

        g[1].push_back(Edge(2, -4));
        g[1].push_back(Edge(4, -1));

        g[2].push_back(Edge(3, 2));

        g[3].push_back(Edge(4, 4));

        bellmanFord(0, g, V);
    }

    return 0;
}


// Network Delay Problem - LeetCode
class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<Edge>> l(n + 1);

        for(vector<int>& edge : times){
            l[edge[0]].push_back(Edge(edge[1], edge[2]));
        }

        vector<int> dist(n+1, INT_MAX);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        dist[k] = 0;

        pq.push({0, k});

        while(!pq.empty()){
            int curr = pq.top().second;
            int currDist = pq.top().first;
            pq.pop();

            if(currDist > dist[curr]) continue;

            for(Edge& e : l[curr]){
                if(dist[e.v] > dist[curr] + e.wt){
                    dist[e.v] = dist[curr] + e.wt;
                    pq.push({dist[e.v], e.v});
                }
            }
        }

        int ans = 0;
        for(int i = 1; i <= n; i++){
            if(dist[i] == INT_MAX) return -1;
            ans = max(ans, dist[i]);
        }

        return ans;
    }
};