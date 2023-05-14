#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int src, dest, weight;
} Edge;

typedef struct {
    int num_vertices, num_edges;
    Edge* edges;
} Graph;

Graph* create_graph(int num_vertices, int num_edges) {
    Graph* graph = (Graph*) malloc(sizeof(Graph));
    graph->num_vertices = num_vertices;
    graph->num_edges = num_edges;
    graph->edges = (Edge*) malloc(num_edges * sizeof(Edge));
    return graph;
}

void add_edge(Graph* graph, int src, int dest, int weight, int index) {
    graph->edges[index].src = src;
    graph->edges[index].dest = dest;
    graph->edges[index].weight = weight;
}

int compare_edges(const void* a, const void* b) {
    Edge* edge_a = (Edge*) a;
    Edge* edge_b = (Edge*) b;
    return edge_a->weight - edge_b->weight;
}

int find(int parent[], int i) {
    if (parent[i] == -1) {
        return i;
    }
    return find(parent, parent[i]);
}

void union_vertices(int parent[], int x, int y) {
    parent[x] = y;
}

void kruskal_mst(Graph* graph) {
    int* parent = (int*) malloc(graph->num_vertices * sizeof(int));
    for (int i = 0; i < graph->num_vertices; i++) {
        parent[i] = -1;
    }
    Edge mst[graph->num_vertices];
    qsort(graph->edges, graph->num_edges, sizeof(Edge), compare_edges);
    int mst_index = 0, edge_index = 0;
    while (mst_index < graph->num_vertices - 1) {
        Edge next_edge = graph->edges[edge_index++];
        int x = find(parent, next_edge.src);
        int y = find(parent, next_edge.dest);
        if (x != y) {
            mst[mst_index++] = next_edge;
            union_vertices(parent, x, y);
        }
    }
    printf("Edge \tWeight\n");
    for (int i = 0; i < mst_index; i++) {
        printf("%d - %d \t%d\n", mst[i].src, mst[i].dest, mst[i].weight);
    }
}

int main() {
    Graph* graph = create_graph(15, 21);
    add_edge(graph, 0, 1, 1, 0);
    add_edge(graph, 0, 2, 3, 1);
    add_edge(graph, 0, 3, 2, 2);
    add_edge(graph, 1, 2, 4, 3);
    add_edge(graph, 1, 4, 2, 4);
    add_edge(graph, 2, 5, 5, 5);
    add_edge(graph, 3, 4, 3, 6);
    add_edge(graph, 3, 5, 6, 7);
    add_edge(graph, 3, 6, 2, 8);
    add_edge(graph, 4, 7, 1, 9);
    add_edge(graph, 5, 7, 4, 10);
    add_edge(graph, 5, 8, 5, 11);
    add_edge(graph, 6, 8, 3, 12);
    add_edge(graph, 7, 9, 2, 13);
    add_edge(graph, 7, 10, 3, 14);
    add_edge(graph, 8, 10, 4, 15);
    add_edge(graph, 8, 11, 1, 16);
    add_edge(graph, 9, 12, 5, 17);
    add_edge(graph, 10, 13, 2, 18);
    add_edge(graph, 11, 14, 4, 19);
    add_edge(graph, 12, 13, 3, 20);
    kruskal_mst(graph);
    return 0;
}
