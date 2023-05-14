#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 15

int min_key(int key[], int mst_set[]) {
    int min = INT_MAX, min_index;
    for (int i = 0; i < V; i++) {
        if (mst_set[i] == 0 && key[i] < min) {
            min = key[i];
            min_index = i;
        }
    }
    return min_index;
}

void print_mst(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++) {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
    }
}

void prim_mst(int graph[V][V]) {
    int parent[V];
    int key[V];
    int mst_set[V];
    for (int i = 0; i < V; i++) {
        key[i] = INT_MAX;
        mst_set[i] = 0;
    }
    key[0] = 0;
    parent[0] = -1;
    for (int i = 0; i < V - 1; i++) {
        int u = min_key(key, mst_set);
        mst_set[u] = 1;
        for (int v = 0; v < V; v++) {
            if (graph[u][v] && mst_set[v] == 0 && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    print_mst(parent, graph);
}

int main() {
    int graph[V][V] = {
        {0, 2, 0, 6, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
        {2, 0, 3, 8, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0},
        {0, 3, 0, 0, 9, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0},
        {6, 8, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 7, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 5, 0, 0, 0, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 6, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 3, 0},
        {5, 4, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 1, 4},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 5},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 5, 0}
    };
    prim_mst(graph);
    return 0;
}
