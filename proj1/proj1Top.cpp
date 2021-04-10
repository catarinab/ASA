#include <stdio.h>
#include <list>
#include <vector>
#include <string>
#include <stack>
#include <iostream>
#include <tuple>
#include <limits.h>
#include <queue>
#define NINF INT_MIN

using namespace std;

class Graph {
    public:
        int nodes, edges, nSources = 0;
        list<int> *adjList;
        list<int> *adjListRev;
        queue<int> qGraph;

    public:
        Graph(int n, int e) {
            nodes = n;
            edges = e;
            adjList = new list<int>[nodes];
            adjListRev = new list<int>[nodes];
        }

        void addEdge(int v1, int v2) {
            adjList[v1 - 1].push_front(v2 - 1);
            adjListRev[v2 - 1].push_front(v1 - 1);
        }

        vector<int> getSources() {
            vector<int> sources;
            for (int i = 0; i < nodes; i++) {
                if (adjListRev[i].empty()) {
                    sources.push_back(i);
                    nSources++;
                }
            }
            return sources;
        }

        void topologicalSortUtil(int v, bool visited[]);
        int longestPath(int s);
        void topOrder();
        void topologicalSort();
};


void Graph::topologicalSort(){
    vector<int> in_degree(nodes, 0);
  
    for (int u = 0; u < nodes; u++) {
        list<int>::iterator itr;
        for (itr = adjList[u].begin();
             itr != adjList[u].end(); itr++)
            in_degree[*itr]++;
    }
  
    queue<int> q;
    for (int i = 0; i < nodes; i++)
        if (in_degree[i] == 0)
            q.push(i);
  
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        qGraph.push(u);
  
        list<int>::iterator itr;
        for (itr = adjList[u].begin();
             itr != adjList[u].end(); itr++)
  
            if (--in_degree[*itr] == 0)
                q.push(*itr);
    }
}

int Graph::longestPath(int s){
    int dist[nodes];
   
    for (int i = 0; i < nodes; i++)
        dist[i] = NINF;
    dist[s] = 1;
    while (qGraph.empty() == false) {
        int u = qGraph.front();
        qGraph.pop();
   
        list<int>::iterator i;
        if (dist[u] != NINF) {
            for (i = adjList[u].begin(); i != adjList[u].end(); ++i){
                //printf("Distancia de %d (i): %d e distancia de %d (u): %d\n", *i, dist[*i], u, dist[u]);
                if (dist[*i] <= dist[u])
                    dist[*i] = dist[u] +1;
            }
        }
    }
   
    int longestPath = 0;
    for (int i = 0; i < nodes; i++){
        if(dist[i] != NINF && dist[i] > longestPath)
            longestPath = dist[i];
    }
        
    
    return longestPath;
}
   

Graph buildGraph() {
    int nodes, edges;
    scanf("%d %d", &nodes, &edges);
    Graph g(nodes, edges);
    for (int i = 0; i < edges; i++) {
        int v1, v2;
        scanf("%d %d", &v1, &v2);
        g.addEdge(v1, v2);
    }
    return g;
}

string domino() {
    Graph g = buildGraph();
    vector<int> sources = g.getSources();
    int minIter = g.nSources, maxSize = 0;
    for (int i = 0; i < g.nSources; i++) {
        g.topologicalSort();
        int size;
        size = g.longestPath(sources[i]);
        if (size > maxSize) {
            maxSize = size;
        }
    }
    
    return std::to_string(minIter) + " " + std::to_string(maxSize);
}

int main() {
    printf("%s\n", domino().c_str());
    return 0;
}