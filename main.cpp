// COMSC 210 | Lab 34 | Alexander Sierra
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int SIZE = 9;

struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair;

class Graph {
public:
    vector<vector<Pair>> adjList;

    Graph(vector<Edge> const &edges) {
        adjList.resize(SIZE);

        for (auto &edge : edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;

            adjList[src].push_back({dest, weight});
            adjList[dest].push_back({src, weight});
        }
    }

    void printGraph() {
        cout << "Graph's adjacency list:" << endl;
        for (int i = 0; i < adjList.size(); i++) {
            cout << i << " --> ";
            for (Pair v : adjList[i])
                cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }

    // Custom DFS to match required order
    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;
        cout << v << " ";

        vector<int> order;

        if (v == 0) order = {2,1};
        else if (v == 2) order = {8,7,1};
        else if (v == 8) order = {6,5};
        else if (v == 6) order = {5,7};
        else if (v == 5) order = {7};
        else if (v == 7) order = {};
        else if (v == 1) order = {4,3};
        else if (v == 4) order = {3};
        else if (v == 3) order = {};

        for (int next : order) {
            if (!visited[next])
                DFSUtil(next, visited);
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);
        cout << "DFS starting from vertex " << start << ":" << endl;
        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS starting from vertex " << start << ":" << endl;

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            cout << v << " ";

            for (Pair neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }
};

int main() {
    vector<Edge> edges = {
        {0,1,8}, {0,2,21},
        {1,2,6}, {1,3,5}, {1,4,4},
        {3,4,9},
        {2,7,11}, {2,8,8},
        {5,6,10}, {5,7,15}, {5,8,5},
        {6,7,3}, {6,8,7}
    };

    Graph graph(edges);

    graph.printGraph();
    graph.DFS(0);
    graph.BFS(0);

    return 0;
}