#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000
#define MAX_EDGES 100000

// 간선 구조체
typedef struct Edge {
    int from, to, weight;
} Edge;

int parent[MAX_VERTICES]; // 각 정점의 부모 저장
int rank[MAX_VERTICES]; // 각 정점의 랭크 저장
Edge edges[MAX_EDGES]; // 간선 저장
Edge mst[MAX_VERTICES - 1]; // 최소 신장 트리 저장
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

// collapsing find : 루트를 찾는 과정에서 경로를 압축
int collapsing_find(int i) {
    int root = i; // 시작정점 및 끝정점
    // 부모 노드 설정
    while (root != parent[root]) { // 현재 노드가 부모 노드가 아니면?
        root = parent[root]; // 현재 노드가 부모 노드에 도착할때까지 반복
    }
    while (i != root) { // i가 루트 노드가 아니면
        int tmp = parent[i]; // i에서 i의 부모노드로 이동
        parent[i] = root; // 부모노드는 루트노드로
        i = tmp; 
    }
    return root; // 루트 노드를 반환
}

// weighted union : 트리 합치는 과정에서 rank값이 작은 트리를 큰 트리의 서버트리에 병합
void weighted_union(int i, int j) {
    int root_i = collapsing_find(i); // 시작 정점이 있는 노드의 루트 노드 반환
    int root_j = collapsing_find(j); // 끝 정점이 있는 노드의 루트 노드 반환
    if (root_i == root_j) return; // 루트 노드가 같으면 같은 집합이므로 종료

    if (rank[root_i] > rank[root_j]) { // 랭크값이 시작 정점이 있는 집합이 더 크면?
        parent[root_j] = root_i; // root_j의 부모 노드에 root_i 연결
    }
    else { // 랭크값이 끝 정점이 있는 집합이 더 크거나 같으면?
        parent[root_i] = root_j; // root_i의 부모 노드에 root_j 연결
        if (rank[root_i] == rank[root_j]) { // 만약 크기가 같았으면?
            rank[root_j]++; 
        }
    }
}

// 간선 비교 함수
int compare(const void* a, const void* b) {
    Edge* edge1 = (Edge*)a;
    Edge* edge2 = (Edge*)b;
    return edge1->weight - edge2->weight;
}

// Kruskal 알고리즘 함수
void kruskal(int n, int m, Edge* edges, Edge* mst) {
    
    // 집합 별 부모 노드와 rank값을 초기화
    for (int i = 0; i < n; i++) {
        parent[i] = i; // 부모 노드는 본인으로 초기화
        rank[i] = 0; // 각 집합의 값은 0으로 초기화
    }

    // 간선을 가중치 오름차순으로 정렬
    qsort(edges, m, sizeof(Edge), compare); 

    int mst_size = 0; // mst에 존재하는 간선의 개수
    for (int i = 0; i < m; i++) { // 그래프의 간선 개수 만큼 진행
        Edge e = edges[i]; // (정렬된) 첫 번째 간선부터
        if (collapsing_find(e.from) != collapsing_find(e.to)) { // 사이클이 아니면 MST에 간선 추가
            printf("O : %d - %d 간선 연결\n", e.from, e.to);
            mst[mst_size++] = e; // 간선 배열에 간선 추가
            weighted_union(e.from, e.to); // weighted union을 이용해 트리 병합
        }
        else { // 사이클이면 해당 메시지를 출력
            printf("X : %d - %d는 사이클을 형성합니다\n", e.from, e.to);
        }
    }

    // 최소 신장 트리의 간선 정보 출력
    printf("최소 신장 트리의 간선 정보:\n");
    for (int i = 0; i < mst_size; i++) {
        Edge e = mst[i]; 
        printf("%d - %d (%d)\n", e.from, e.to, e.weight);
    }
}

int main() {
    int n; // 정점 개수
    int m; // 간선 개수
    Edge* edges; // 간선 : 시작위치, 끝위치, 가중치
    int index = 0; // 두 그래프 구분

    // 그래프 1
    n = 5;
    m = 7;
    edges = (Edge*)malloc(sizeof(Edge) * m); // 그래프 간선 저장 공간

    // 간선 정보 저장
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph_1[i][j] != 0) { // 간선 존재할시 시작위치 i, 끝위치 j, 가중치 저장
                Edge e; // 간선 하나의 정보 보관
                e.from = i; // 간선 시작 위치
                e.to = j; // 간선 끝 위치
                e.weight = graph_1[i][j]; // 간선 가중치
                edges[index++] = e; // 간선을 보관하는 배열에 구조체 저장
            }
        }
    }

    // Kruskal 실행
    printf("#######[그래프 1]##################\n");
    kruskal(n, m, edges, mst);

    // 그래프 2
    n = 6;
    m = 9;
    edges = (Edge*)malloc(sizeof(Edge) * m);

    // 간선 정보 저장
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

    // Kruskal 알고리즘 실행
    printf("#######[그래프 2]##################\n");
    kruskal(n, m, edges, mst);

    free(edges);
    return 0;
}