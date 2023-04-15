#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000
#define MAX_EDGES 100000

// ���� ����ü
typedef struct Edge {
    int from, to, weight;
} Edge;

int parent[MAX_VERTICES]; // �� ������ �θ� ����
int rank[MAX_VERTICES]; // �� ������ ��ũ ����
Edge edges[MAX_EDGES]; // ���� ����
Edge mst[MAX_VERTICES - 1]; // �ּ� ���� Ʈ�� ����
int graph_1[5][5] =
{
    {0, 2, 0, 6, 0},
    {2, 0, 3, 8, 5},
    {0, 3, 0, 0, 7},
    {6, 8, 0, 0, 9},
    {0, 5, 7, 9, 0}
};
int graph_2[6][6] =
{
    {0, 7, 9, 0, 0, 14},
    {7, 0, 10, 15, 0, 0},
    {9, 10, 0, 11, 0, 2},
    {0, 15, 11, 0, 6, 0},
    {0, 0, 0, 6, 0, 9},
    {14, 0, 2, 0, 9, 0}
};

// collapsing find : ��Ʈ�� ã�� �������� ��θ� ����
int collapsing_find(int i) {
    int root = i; // �������� �� ������
    // �θ� ��� ����
    while (root != parent[root]) { // ���� ��尡 �θ� ��尡 �ƴϸ�?
        root = parent[root]; // ���� ��尡 �θ� ��忡 �����Ҷ����� �ݺ�
    }
    while (i != root) { // i�� ��Ʈ ��尡 �ƴϸ�
        int tmp = parent[i]; // i���� i�� �θ���� �̵�
        parent[i] = root; // �θ���� ��Ʈ����
        i = tmp; 
    }
    return root; // ��Ʈ ��带 ��ȯ
}

// weighted union : Ʈ�� ��ġ�� �������� rank���� ���� Ʈ���� ū Ʈ���� ����Ʈ���� ����
void weighted_union(int i, int j) {
    int root_i = collapsing_find(i); // ���� ������ �ִ� ����� ��Ʈ ��� ��ȯ
    int root_j = collapsing_find(j); // �� ������ �ִ� ����� ��Ʈ ��� ��ȯ
    if (root_i == root_j) return; // ��Ʈ ��尡 ������ ���� �����̹Ƿ� ����

    if (rank[root_i] > rank[root_j]) { // ��ũ���� ���� ������ �ִ� ������ �� ũ��?
        parent[root_j] = root_i; // root_j�� �θ� ��忡 root_i ����
    }
    else { // ��ũ���� �� ������ �ִ� ������ �� ũ�ų� ������?
        parent[root_i] = root_j; // root_i�� �θ� ��忡 root_j ����
        if (rank[root_i] == rank[root_j]) { // ���� ũ�Ⱑ ��������?
            rank[root_j]++; 
        }
    }
}

// ���� �� �Լ�
int compare(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal �˰��� �Լ�
void kruskal(int n, int m, Edge* edges, Edge* mst) {
    
    // ���� �� �θ� ���� rank���� �ʱ�ȭ
    for (int i = 0; i < n; i++) {
        parent[i] = i; // �θ� ���� �������� �ʱ�ȭ
        rank[i] = 0; // �� ������ ���� 0���� �ʱ�ȭ
    }

    // ������ ����ġ ������������ ����
    qsort(edges, m, sizeof(Edge), compare); 

    int mst_size = 0; // mst�� �����ϴ� ������ ����
    for (int i = 0; i < m; i++) { // �׷����� ���� ���� ��ŭ ����
        Edge e = edges[i]; // (���ĵ�) ù ��° ��������
        if (collapsing_find(e.from) != collapsing_find(e.to)) { // ����Ŭ�� �ƴϸ� MST�� ���� �߰�
            printf("O : %d - %d ���� ����\n", e.from, e.to);
            mst[mst_size++] = e; // ���� �迭�� ���� �߰�
            weighted_union(e.from, e.to); // weighted union�� �̿��� Ʈ�� ����
        }
        else { // ����Ŭ�̸� �ش� �޽����� ���
            printf("X : %d - %d�� ����Ŭ�� �����մϴ�\n", e.from, e.to);
        }
    }

    // �ּ� ���� Ʈ���� ���� ���� ���
    printf("�ּ� ���� Ʈ���� ���� ����:\n");
    for (int i = 0; i < mst_size; i++) {
        Edge e = mst[i]; 
        printf("%d - %d (%d)\n", e.from, e.to, e.weight);
    }
}

int main() {
    int n; // ���� ����
    int m; // ���� ����
    Edge* edges; // ���� : ������ġ, ����ġ, ����ġ
    int index = 0; // �� �׷��� ����

    // �׷��� 1
    n = 5;
    m = 7;
    edges = (Edge*)malloc(sizeof(Edge) * m); // �׷��� ���� ���� ����

    // ���� ���� ����
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph_1[i][j] != 0) { // ���� �����ҽ� ������ġ i, ����ġ j, ����ġ ����
                Edge e; // ���� �ϳ��� ���� ����
                e.from = i; // ���� ���� ��ġ
                e.to = j; // ���� �� ��ġ
                e.weight = graph_1[i][j]; // ���� ����ġ
                edges[index++] = e; // ������ �����ϴ� �迭�� ����ü ����
            }
        }
    }

    // Kruskal ����
    printf("#######[�׷��� 1]##################\n");
    kruskal(n, m, edges, mst);

    // �׷��� 2
    n = 6;
    m = 9;
    edges = (Edge*)malloc(sizeof(Edge) * m);

    // ���� ���� ����
    index = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph_2[i][j] != 0) {
                Edge e;
                e.from = i;
                e.to = j;
                e.weight = graph_2[i][j];
                edges[index++] = e;
            }
        }
    }

    // Kruskal �˰��� ����
    printf("#######[�׷��� 2]##################\n");
    kruskal(n, m, edges, mst);

    free(edges);
    return 0;
}