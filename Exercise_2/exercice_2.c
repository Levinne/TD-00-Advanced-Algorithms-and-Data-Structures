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

// Check connectivity and find the path using BFS
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
    Graph* graph = createGraph(8); // Create a graph with 8 locations

    // Add edges based on the example graph
    // A-B-C-D-E
    addEdge(graph, 0, 1); // A-B
    addEdge(graph, 0, 2); // A-C
    addEdge(graph, 1, 3); // B-D
    addEdge(graph, 1, 4); // B-E
    addEdge(graph, 2, 4); // C-E
    addEdge(graph, 3, 4); // D-E
    addEdge(graph, 3, 5); // D-F

    // G-H-I (second component)
    addEdge(graph, 6, 7); // G-H

    // Run BFS and DFS
    printf("BFS Traversal from A:\nInput: BFS(graph, \"A\")\n");
    bfs(graph, 0); // Start from A (0)

    printf("DFS Traversal from A:\nInput: DFS(graph, \"A\", visited)\n");
    dfs(graph, 0); // Start from A (0)

    // Check connectivity and find path from A (0) to F (5)
    int start = 0, end = 5; // A to F
    if (isConnected(graph, start, end)) {
        printf("Connectivity Check:\nInput: are_connected(graph, \"A\", \"F\")\nOutput: True\n");
    } else {
        printf("Connectivity Check:\nInput: are_connected(graph, \"A\", \"F\")\nOutput: False\n");
    }

    // Find shortest path from A (0) to F (5)
    if (isConnected(graph, start, end)) {
        int path[MAX_NODES], pathIndex = 0;
        int parent[MAX_NODES] = {-1};
        // Re-run BFS to find the path
        isConnected(graph, start, end); // Populate parent array for path
        printf("Find Shortest Path:\nInput: shortest_path(graph, \"A\", \"F\")\nOutput: [");
        for (int v = end; v != -1; v = parent[v]) {
            path[pathIndex++] = v;
        }
        for (int i = pathIndex - 1; i > 0; i--) {
            printf("%d, ", path[i]);
        }
        printf("%d]\n", path[0]); // Print the last element without a comma
    }

    return 0;
}