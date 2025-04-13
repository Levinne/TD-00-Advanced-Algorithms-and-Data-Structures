#include <stdio.h>
#include <stdlib.h>

#define MAX_NODES 100

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    Node* adjList[MAX_NODES];
    int numVertices;
} Graph;

// Function to create a graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        graph->adjList[i] = NULL;
    }
    return graph;
}

// Function to add an edge to the undirected graph
void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;

    newNode = malloc(sizeof(Node));
    newNode->vertex = src;
    newNode->next = graph->adjList[dest];
    graph->adjList[dest] = newNode;
}

// BFS implementation
void bfs(Graph* graph, int start) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal: ");
    while (front < rear) {
        int current = queue[front++];
        printf("%d ", current);

        Node* temp = graph->adjList[current];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                queue[rear++] = adjVertex;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

// DFS implementation
void dfsUtil(Graph* graph, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);

    Node* temp = graph->adjList[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            dfsUtil(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph* graph, int start) {
    int visited[MAX_NODES] = {0};
    printf("DFS Traversal: ");
    dfsUtil(graph, start, visited);
    printf("\n");
}

// Check connectivity and find shortest path using BFS
int isConnected(Graph* graph, int start, int end) {
    int visited[MAX_NODES] = {0};
    int queue[MAX_NODES];
    int front = 0, rear = 0;
    int parent[MAX_NODES] = {-1};

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int current = queue[front++];

        Node* temp = graph->adjList[current];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = 1;
                parent[adjVertex] = current;
                queue[rear++] = adjVertex;

                if (adjVertex == end) {
                    // Found the end, reconstruct the path
                    printf("Path from %d to %d: ", start, end);
                    int path[MAX_NODES], pathIndex = 0;
                    for (int v = end; v != -1; v = parent[v]) {
                        path[pathIndex++] = v;
                    }
                    for (int i = pathIndex - 1; i >= 0; i--) {
                        printf("%d ", path[i]);
                    }
                    printf("\n");
                    return 1; // Connected
                }
            }
            temp = temp->next;
        }
    }
    return 0; // Not connected
}

int main() {
    Graph* graph = createGraph(6); // Create a graph with 6 locations

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);

    bfs(graph, 0);
    dfs(graph, 0);

    int start = 0, end = 4;
    if (isConnected(graph, start, end)) {
        printf("Locations %d and %d are connected.\n", start, end);
    } else {
        printf("Locations %d and %d are not connected.\n", start, end);
    }

    return 0;
}