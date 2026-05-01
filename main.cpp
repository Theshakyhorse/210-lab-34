// COMSC 210 | Lab 34 | Alexander Sierra
#include <iostream>
#include <vector>
#include <queue>
#include <climits>
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
            adjList[edge.src].push_back({edge.dest, edge.weight});
            adjList[edge.dest].push_back({edge.src, edge.weight});
        }
    }

    string nodeName(int v) {
        switch (v) {
            case 0: return "Central Emergency Command Center";
            case 1: return "Police Dispatch Hub";
            case 2: return "City Surveillance Core";
            case 3: return "North Precinct Station";
            case 4: return "South Precinct Station";
            case 5: return "Fire Response Logistics Center";
            case 6: return "Hazardous Materials Unit";
            case 7: return "Traffic Monitoring AI Center";
            case 8: return "Emergency Drone Control Unit";
            default: return "Unknown Facility";
        }
    }

    void printGraph() {
        cout << "================================\n";
        cout << "SMART CITY EMERGENCY NETWORK MAP\n";
        cout << "================================\n\n";

        for (int i = 0; i < adjList.size(); i++) {
            cout << "Node " << i << " (" << nodeName(i) << ") connects to:\n";

            for (auto &p : adjList[i]) {
                cout << "  -> Node " << p.first << " (" << nodeName(p.first)
                     << ") - Signal Strength: " << p.second << "\n";
            }
            cout << "\n";
        }
    }

    void DFSUtil(int v, vector<bool> &visited) {
        visited[v] = true;

        cout << "Inspecting " << nodeName(v) << "\n";

        for (auto &neighbor : adjList[v]) {
            if (!visited[neighbor.first]) {
                cout << "  -> Potential emergency link to "
                     << nodeName(neighbor.first)
                     << " - Strength: " << neighbor.second << "\n";
                DFSUtil(neighbor.first, visited);
            }
        }
    }

    void DFS(int start) {
        vector<bool> visited(SIZE, false);

        cout << "=======================================\n";
        cout << "NETWORK TRACE (DFS) FROM COMMAND CENTER\n";
        cout << "=======================================\n\n";

        DFSUtil(start, visited);
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(SIZE, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "=======================================\n";
        cout << "LAYER-BY-LAYER ALERT DISTRIBUTION (BFS)\n";
        cout << "=======================================\n\n";

        while (!q.empty()) {
            int v = q.front();
            q.pop();

            cout << "Checking " << nodeName(v) << "\n";

            for (auto &neighbor : adjList[v]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);

                    cout << "  -> Next alert zone: "
                         << nodeName(neighbor.first)
                         << " - Strength: " << neighbor.second << "\n";
                }
            }
        }
    }

    void shortestPath(int start) {
        vector<int> dist(SIZE, INT_MAX);
        vector<bool> visited(SIZE, false);

        dist[start] = 0;

        for (int i = 0; i < SIZE - 1; i++) {
            int u = -1;

            // find unvisited node with smallest distance
            for (int j = 0; j < SIZE; j++) {
                if (!visited[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            visited[u] = true;

            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }

        cout << "\n=======================================\n";
        cout << "SHORTEST PATHS FROM NODE " << start << "\n";
        cout << "=======================================\n";

        for (int i = 0; i < SIZE; i++) {
            cout << start << " -> " << i << " : " << dist[i] << endl;
        }
    }

    void MST(int start) {
        vector<int> key(SIZE, INT_MAX);
        vector<bool> inMST(SIZE, false);
        vector<int> parent(SIZE, -1);

        key[start] = 0;

        for (int count = 0; count < SIZE - 1; count++) {
            int u = -1;

        // pick minimum key vertex not yet in MST
            for (int v = 0; v < SIZE; v++) {
                if (!inMST[v] && (u == -1 || key[v] < key[u])) {
                    u = v;
                }
            }

            if (u == -1) break; // safety check

            inMST[u] = true;

            // update adjacent vertices
            for (auto &neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (!inMST[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                }
            }
        }

        cout << "\n=======================================\n";
        cout << "MINIMUM SPANNING TREE (PRIM'S ALGORITHM)\n";
        cout << "=======================================\n";

        int totalWeight = 0;

        for (int i = 0; i < SIZE; i++) {
            if (parent[i] != -1) {
                cout << parent[i] << " -> " << i
                    << " (Weight: " << key[i] << ")\n";
                totalWeight += key[i];
            }
        }

        cout << "---------------------------------------\n";
        cout << "Total MST Weight: " << totalWeight << endl;
    }
};

void shortestPath(int);

int main() {
    vector<Edge> edges = {
        {0,1,8}, {0,2,21},
        {1,2,6}, {1,3,5}, {1,4,4},
        {3,4,9},
        {2,7,11}, {2,8,8},
        {5,6,10}, {5,7,15}, {5,8,5},
        {6,7,3}, {6,8,7}
    };

    int choice;
    Graph graph(edges);

    while (choice != 0) {
        cout << "Smart City Menu:" << endl;
        cout << "[1] Display network" << endl;
        cout << "[2] BFS" << endl;
        cout << "[3] DFS" << endl;
        cout << "[4] Shortest paths" << endl;
        cout << "[5] MST" << endl;
        cout << "[0] Exit" << endl;
        cout << "Enter choice: " << endl;
        cin >> choice;

        if (choice >= 1 && choice <= 5) {
            if (choice == 1) {
                graph.printGraph();
            } else if(choice == 2) {
                graph.BFS(0);
            } else if(choice == 3) {
                graph.DFS(0);
            } else if(choice == 4) {
                graph.shortestPath(0);
            } else if(choice == 5) {
                graph.MST(0);
            }
        }
        else if (choice == 0) {
            cout << "Exiting";
        }
        else {
            cout << "Invalid";
        }
        cout << endl;
    }

    return 0;
}