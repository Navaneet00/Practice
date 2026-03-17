#include <iostream>
#include <queue>
#include <list>
using namespace std;

struct Edge{
    int v, wt;

    Edge(int vertex, int weight) : v(vertex), wt(weight){}
};
 
class Graph{
    int V;
    list<Edge>* l;

    public:

    Graph(int vertices) : V(vertices), l(new list<Edge> [V]){}

    // Add edge between u & v
    void addEdge(int u, int v, int wt){
        l[u].push_back(Edge(v, wt));
        l[v].push_back(Edge(u, wt));
    }

    // Prim's Algorithm (To find MST - Minimum Spanning Tree)
    void primsAlgo(){
        vector<bool> visited(V, false);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        pq.push({0, 0});
        int minCost = 0;

        while(!pq.empty()){
            auto [wt, u] = pq.top();
            pq.pop();

            if(!visited[u]){
                visited[u] = true;
                minCost += wt;

                for(Edge& e : l[u]){
                    if(!visited[e.v]){
                        pq.push({e.wt, e.v});
                    }
                }
            }
        }

        cout << "Minimum Cost of MST: " << minCost << endl;
    }
};


int main(){
    Graph g(7);
    
    // g.addEdge(0, 1, 10);
    // g.addEdge(0, 2, 15);
    // g.addEdge(0, 3, 30);
    // g.addEdge(1, 3, 40);
    // g.addEdge(2, 3, 50);

    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 3);

    g.addEdge(1, 2, 4);
    g.addEdge(1, 3, 6);
    g.addEdge(1, 4, 2);

    g.addEdge(2, 3, 5);
    g.addEdge(2, 5, 6);

    g.addEdge(3, 4, 6);
    g.addEdge(3, 5, 6);

    g.addEdge(4, 5, 3);
    g.addEdge(4, 6, 4);

    g.addEdge(5, 6, 4);

    g.primsAlgo();

    return 0;
}