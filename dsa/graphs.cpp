#include <iostream>
#include <list>
#include <queue>
#include <vector>
using namespace std;

// Graph class
class Graph{
    int V;
    list<int>* l;

    public:
    Graph(int vertices){
        this->V = vertices;
        this->l = new list<int> [V];
    }

    // Add edges
    void addEdge(int u, int v){
        l[u].push_back(v);
        l[v].push_back(u);
    }

    // Print Graph
    void print(){
        for(int i = 0; i < V; i++){
            cout << i << " : ";

            for(int neigh : l[i]){
                cout << neigh << " ";
            }
            cout << endl;
        }
    }

    // BFS (Breadth First Search) Traversal  (O(V+E))
    void bfs(){
        queue<int> q;
        vector<bool> visited(V, false);

        q.push(0);
        visited[0] = true;
        cout << "BFS Traversal: ";

        while(!q.empty()){
            int src = q.front();
            cout << src << " ";
            q.pop();

            for(int neigh : l[src]){
                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push(neigh);
                }
            }
        }

        cout << endl;
    }

    // DFS (Depth First Search) Traversal Helper
    void dfsHelper(int src, vector<bool>& visited){
        cout << src << " ";
        visited[src] = true;

        for(int dist : l[src]){
            if(!visited[dist]){
                dfsHelper(dist, visited);
            }
        }
    }

    // DFS (Depth First Search) Traversal  (O(V+E))
    void dfs(){
        vector<bool> visited(V, false);

        cout << "DFS Traversal: ";
        for(int i = 0; i < V; i++){
            if(!visited[i]){
                dfsHelper(i, visited);
            }
        }
        cout << endl;
    }

    // Check if cycle exists in Undirected Graph using DFS traversal
    bool isCycleUndirDFS(int src, int par, vector<bool>& visited){
        visited[src] = true;

        for(int dist : l[src]){
            if(!visited[dist]){
                if(isCycleUndirDFS(dist, src, visited)){
                    return true;
                }
            }
            else{
                if(dist != par){
                    return true;
                }
            }
        }

        return false;
    }

    // Detect if cycle exists using DFS traversal
    bool isCycle(){
        vector<bool> visited(V, false);

        for(int i = 0; i < V; i++){
            if(!visited[i]){
                if(isCycleUndirDFS(i, -1, visited)){
                    return true;
                }
            }
        }

        return false;
    }

    // Check if cycle exists in Undirected Graph using BFS traversal
    bool isCycleUndirBFS(int src, vector<bool> visited){
        queue<pair<int, int>> q;

        q.push({src, -1});
        visited[src] = true;

        while(!q.empty()){
            int front = q.front().first;
            int parFront = q.front().second;
            q.pop();

            for(int neigh : l[front]){
                if(!visited[neigh]){
                    visited[neigh] = true;
                    q.push({neigh, front});
                }
                else if(neigh != parFront){
                    return true;
                }
            }
        }

        return false;
    }

    // Detect if cycle exists using BFS traversal
    bool isCycle1(){
        vector<bool> visited(V, false);
        
        for(int i = 0; i < V; i++){
            if(!visited[i]){
                if(isCycleUndirBFS(i, visited)){
                    return true;
                }
            }
        }

        return false;
    }
};

int main(){
    Graph g(5);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);

    g.print();
    g.bfs();
    g.dfs();
    cout << "IsCycle exists (DFS)? " << (g.isCycle()? "True" : "False") << endl;
    cout << "IsCycle exists (BFS)? " << (g.isCycle1()? "True" : "False") << endl;

    return 0;
}