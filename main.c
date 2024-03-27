#include <stdlib.h>
#include <stdio.h>

#define EDGE struct edge

EDGE {
    //structure of edge
    int start;
    int end;
    long long value;
};

void check(int n, int m) {
    //to check input data
    if (n < 0 || n > 5000) {
        printf("bad number of vertices");
        exit(0);
    }

    if (m < 0 || m > (n * (n + 1)) / 2) {
        printf("bad number of edges");
        exit(0);
    }

}

int cmp(const void *a, const void *b) {
    //comparator for qsort
    return ((EDGE *) a)->value - ((EDGE *) b)->value;
}

int findParent(int parent[], int elem) {
    //to find the absolute parent
    if (parent[elem] == elem)
        return elem;
    return parent[elem] = findParent(parent, parent[elem]);
}

void unionSet(int a, int b, int parent[], int rank[]) {
    //need to union two set in one
    a = findParent(parent, a);
    b = findParent(parent, b);

    if (rank[a] > rank[b])
        parent[b] = a;
    else if (rank[b] > rank[a])
        parent[a] = b;
    else {
        parent[a] = b;
        rank[a]++;
    }
}

void printRes(EDGE *res, int n) {
    //to print the result
    for (int i = 0; i < n; ++i)
        printf("%d %d\n", res[i].start, res[i].end);

}

void kruskal(int n, EDGE *edges) {
    //need two arrays
    int *parent, *rank;
    parent = (int *) malloc(n * sizeof(int));
    rank = (int *) malloc(n * sizeof(int));

    EDGE *res;
    int edgeMST = 0, numVert = 0;
    int parent1, parent2;

    for (int k = 0; k < n; ++k) {
        parent[k] = k;
        rank[k] = 0;
    }

    res = (EDGE *) malloc((n - 1) * sizeof(EDGE));
    qsort(edges, n, sizeof(EDGE), cmp);

    while (edgeMST < (n - 1) && numVert < n) {
        EDGE cur = edges[numVert++];

        parent1 = findParent(parent, cur.start - 1);
        parent2 = findParent(parent, cur.end - 1);

        if (parent1 != parent2) {
            res[edgeMST++] = cur;
            unionSet(parent1, parent2, parent, rank);
        }
    }

    if (edgeMST != n - 1) {
        printf("no spanning tree");
        exit(0);
    }

    printRes(res, edgeMST);
    free(parent);
    free(rank);
}

int main() {
    int n, m, count = 0;
    int start, end;
    long long value;
    EDGE *edges;

    scanf("%d", &n);
    scanf("%d", &m);

    if (n == 1) {
        printf("");
        exit(0);
    }

    edges = (EDGE *) malloc(sizeof(EDGE) * m);

    for (int i = 0; i < m; ++i) {
        if (scanf("%d %d %lld", &start, &end, &value) != 3) {
            printf("bad number of lines");
            exit(0);
        }

        if (start < 1 || start > n || end < 1 || end > n) {
            printf("bad vertex");
            exit(0);
        }

        if (value < 0 || value > INT_MAX) {
            printf("bad length");
            exit(0);
        }

        if (start == n || end == n)
            count++;

        edges[i].start = start;
        edges[i].end = end;
        edges[i].value = value;
    }
    check(n, m);

    if (count == 0) {
        printf("no spanning tree");
        exit(0);
    }

    kruskal(n, edges);
    free(edges);

    return 0;
}
