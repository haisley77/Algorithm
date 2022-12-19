/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


typedef struct edge {
	int v1;						// 정점 1 인덱스
	int v2;						// 정점 2 인덱스
	int w;						// 무게
} Edge;

int INF = 30000;
int n, m, s;
// 간선리스트
Edge** E;
// 최단 거리 정보 저장 리스트
int* D;

// 함수 목록
void insertEdge(int i, int v1, int v2, int w);
int getMin(int a, int b);
void BellmanFordShortestPaths();
void freememory();

int main() {

	int v1, v2, w;

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	// 최단 거리 정보 저장 리스트 초기화
	D = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		D[i] = INF;
	}

	// 간선 리스트 초기화
	E = (Edge**)malloc(sizeof(Edge*) * m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(i, v1, v2, w);
	}

	// 벨만포드 
	BellmanFordShortestPaths();

	// 메모리 해제
	freememory();


	return 0;  
}



void insertEdge(int i, int v1, int v2, int w) {
	E[i] = (Edge*)malloc(sizeof(Edge));
	E[i]->v1 = v1 - 1;
	E[i]->v2 = v2 - 1;
	E[i]->w = w;
}

int getMin(int a, int b) {
	if (a < b) return a;
	else return b;
}

void BellmanFordShortestPaths() {

	int u, z;
	D[s - 1] = 0;

	// n-1 번 수행
	for (int i = 1; i < n; i++) {
		// 모든 간선에 대해 수행
		for (int j = 0; j < m; j++) {
			u = E[j]->v1;
			z = E[j]->v2;
			if (D[u] != INF) {
				D[z] = getMin(D[z], D[u] + E[j]->w);
			}
		}

	}

	
	// 최단 거리 정보 출력
	for (int i = 0; i < n; i++) {
		if (i == s - 1 || D[i] == INF) {
			continue;
		}
		printf("%d %d\n", i + 1, D[i]);
	}
	
}

// 메모리 해제
void freememory() {
	
	for (int i = 0; i < m; i++) {
		free(E[i]);
	}
	free(E);

	free(D);
}
*/