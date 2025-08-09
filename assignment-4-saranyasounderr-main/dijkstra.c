/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Saranya Sounder Rajan
 * Email: sounders@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>

#define DATA_FILE "airports.dat"
#define START_NODE 0
#define INF 9999999  // Arbitrarily large number to represent infinity

// Find the node with the minimum distance that hasn't been visited yet
int find_min_distance(int* distances, int* visited, int n_nodes) {
    int min_distance = INF;
    int min_index = -1;

    for (int i = 0; i < n_nodes; i++) {
        if (!visited[i] && distances[i] < min_distance) {
            min_distance = distances[i];
            min_index = i;
        }
    }
    return min_index;
}

int main() {
    int n_nodes, n_edges;

    FILE* file = fopen(DATA_FILE, "r");
    if (!file) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fscanf(file, " %d %d ", &n_nodes, &n_edges);

/*Each element adj_mat[i][j] holds the cost of the edge from node i to node j.
 *  If there is no edge between them, it is initialized to 0. */ 
    int** adj_mat = malloc(n_nodes * sizeof(int*));
    for (int i = 0; i < n_nodes; i++) {
        adj_mat[i] = calloc(n_nodes, sizeof(int));
    }
/*each edge is represented by two nodes (node_i and node_j) 
and the cost. The adjacency matrix is populated accordingly. */
    for (int i = 0; i < n_edges; i++) {
        int node_i, node_j, cost;
        fscanf(file, " %d %d %d ", &node_i, &node_j, &cost);
        adj_mat[node_i][node_j] = cost;
    }
    fclose(file);

    int* distances = malloc(n_nodes * sizeof(int));
    int* visited = calloc(n_nodes, sizeof(int)); 
    int* prev_nodes = malloc(n_nodes * sizeof(int));

    for (int i = 0; i < n_nodes; i++) {
        distances[i] = INF; 
        prev_nodes[i] = -1;  
    }
    distances[START_NODE] = 0;  

  
    for (int count = 0; count < n_nodes - 1; count++) {
       
        int u = find_min_distance(distances, visited, n_nodes);
        if (u == -1) break; 
        visited[u] = 1;

        for (int v = 0; v < n_nodes; v++) {
            if (!visited[v] && adj_mat[u][v] && distances[u] != INF &&
                distances[u] + adj_mat[u][v] < distances[v]) {
                distances[v] = distances[u] + adj_mat[u][v];
                prev_nodes[v] = u;
            }
        }
    }

    
    prev_nodes[START_NODE] = START_NODE;

    
    printf("Shortest path costs from node %d:\n", START_NODE);
    for (int i = 0; i < n_nodes; i++) {
        printf("To node %d: %d, Previous node: %d\n", i, distances[i], prev_nodes[i]);
    }

    for (int i = 0; i < n_nodes; i++) {
        free(adj_mat[i]);
    }
    free(adj_mat);
    free(distances);
    free(visited);
    free(prev_nodes);

    return 0;
}
