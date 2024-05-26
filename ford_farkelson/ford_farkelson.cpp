#include <iostream>
using namespace std;

const int MAX_E = (int)1e6;
const int MAX_V = (int)1e3;
const int INF = (int)1e9;

int numOfVertex, numOfEdge, sourceVertex, destinationVertex;
int capacity[MAX_E], onEnd[MAX_E], nextEdge[MAX_E], edgeCount;
int firstEdge[MAX_V], visited[MAX_V];

void addEdge(int u, int v, int cap) {
    // straight edge
    onEnd[edgeCount] = v;                   // at the end of straight v
    nextEdge[edgeCount] = firstEdge[u];     // add to the beginning of the list for u
    firstEdge[u] = edgeCount;               // now the beginning of the list is a new edge
    capacity[edgeCount++] = cap;            // set the bandwidth
    // reverse edge
    onEnd[edgeCount] = u;                   // the same procedure as with a straight edge
    nextEdge[edgeCount] = firstEdge[v];     
    firstEdge[v] = edgeCount;               
    capacity[edgeCount++] = 0;              
}

int findFlow(int u, int flow) {
    if (u == destinationVertex) return flow; // return the resulting minimum on the way
    visited[u] = true;
    for (int edge = firstEdge[u]; edge != -1; edge = nextEdge[edge]) {
        int to = onEnd[edge];
        if (!visited[to] && capacity[edge] > 0) {
            int minResult = findFlow(to, min(flow, capacity[edge])); // looking for a stream in the subtree
            if (minResult > 0) {                    // if found
                capacity[edge] -= minResult;   // at straight edges we subtract the flow
                capacity[edge ^ 1] += minResult;   // add to the reciprocals
                return minResult;
            }
        }
    }
    return 0; // if we did not find a flow from this vertex, return 0
}

int main() {
    fill(firstEdge, firstEdge + MAX_V, -1);     // -1 means no edge
    cin >> numOfVertex >> numOfEdge;            // read the number of vertices and edges
    cin >> sourceVertex >> destinationVertex;   // read the source and sink
    for (int i = 0, u, v, cap; i < numOfEdge; i++) {
        cin >> u >> v >> cap;
        addEdge(u, v, cap);
    }
    // Finding the maximum flow
    int maxFlow = 0;
    int iterationResult = 0;
    while ((iterationResult = findFlow(sourceVertex, INF)) > 0) {
        fill(visited, visited + MAX_V, false);
        maxFlow += iterationResult;
    }
    cout << maxFlow << endl;
    return 0;
}