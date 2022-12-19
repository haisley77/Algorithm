#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct inode {
	int edge;						// edge 인덱스
	struct inode* next;				// 다음 인접 edge
} Inode;

typedef struct dnode {
	int v;							// 정점 인덱스
	int dist;						// 실시간 최단 거리
} Dnode;

typedef struct vertex {
	int distindex;					// 큐 인덱스
	int state;						// 최단 거리 확정 여부
	struct inode* in;				// 인접리스트 헤더
} Vertex;

typedef struct edge {
	int v1;						// 정점 1 인덱스
	int v2;						// 정점 2 인덱스
	int w;						// 거리 
} Edge;


int INF = 30000;
int n, m, s;
// 간선리스트
Edge** E;
// 정점리스트
Vertex** V;
// 우선순위큐
Dnode** Q;
// 최단거리 저장 리스트
int* D;

// 그래프 함수
void insertVertex(int i);
void insertEdge(int i, int v1, int v2, int w);
int opposite(int u, Inode* e);

// 우선순위큐(힙) 함수
void downHeap(int i);
void rBuildHeap(int i);
int removeMin();
int isEmpty();
void replaceKey(int z, int d);

// 다익스트라 알고리즘
void DijkstraShortestPaths();

// 메모리 해제 함수
void freememory();

void main() {

	int v1, v2, w;

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	
	// 정점 리스트 초기화
	V = (Vertex**)malloc(sizeof(Vertex*) * n);
	for (int i = 0; i < n; i++) {
		
		insertVertex(i);
	}

	// 간선 리스트 초기화
	E = (Edge**)malloc(sizeof(Edge*) * m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(i, v1, v2, w);
	}

	// 최단거리 저장 리스트 초기화
	D = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		D[i] = INF;
	}
	// 우선순위큐 초기화
	Q = (Dnode**)malloc(sizeof(Dnode) * (n + 1));
	for (int i = 0; i <= n; i++) {
		Q[i] = (Dnode*)malloc(sizeof(Dnode));
		Q[i]->dist = INF;
		Q[i]->v = i - 1;
	}

	// 다익스트라 최단 경로 탐색
	DijkstraShortestPaths();

	freememory();

	return;
}

void insertVertex(int i) {
	V[i] = (Vertex*)malloc(sizeof(Vertex));
	// 경로 포함 여부
	V[i]->state = 0;
	// 인접리스트 헤더
	V[i]->in = (Inode*)malloc(sizeof(Inode));
	V[i]->in->next = NULL;
	// 정점의 우선순위큐 최단거리 저장 인덱스
	V[i]->distindex = i + 1;

}

void insertEdge(int i, int v1, int v2, int w) {
	// 간선 생성
	E[i] = (Edge*)malloc(sizeof(Edge));
	E[i]->v1 = v1 - 1;
	E[i]->v2 = v2 - 1;
	E[i]->w = w;

	// v1 정점 인접리스트 추가
	Inode* node1 = (Inode*)malloc(sizeof(Inode));
	node1->edge = i;
	node1->next = V[v1 - 1]->in->next;
	V[v1 - 1]->in->next = node1;

	// v2 정점 인접리스트 추가
	Inode* node2 = (Inode*)malloc(sizeof(Inode));
	node2->edge = i;
	node2->next = V[v2 - 1]->in->next;
	V[v2 - 1]->in->next = node2;

}


void downHeap(int i) {

	Dnode* tmp;
	int left = 2 * i, right = 2 * i + 1;

	if (left > n && right > n) return;

	if (right <= n) {
		if (Q[left]->dist > Q[right]->dist) {
			if (Q[right]->dist < Q[i]->dist) {
				// 정점의 우선순위큐 최단거리 저장 인덱스 수정
				V[Q[i]->v]->distindex = right;

				// 우선순위큐 원소 swap
				tmp = Q[i];
				Q[i] = Q[right];
				Q[right] = tmp;

				
				downHeap(right);
			}
		}
		else {
			if (Q[left]->dist < Q[i]->dist) {

				V[Q[i]->v]->distindex = left;

				tmp = Q[i];
				Q[i] = Q[left];
				Q[left] = tmp;

				downHeap(left);
			}
		}
	}
	else if (left <= n) {
		if (Q[left]->dist < Q[i]->dist) {

			V[Q[i]->v]->distindex = left;

			tmp = Q[i];
			Q[i] = Q[left];
			Q[left] = tmp;

			downHeap(left);
		}
	}
	else return;
}

// 상향식 최소 힙 구현
void rBuildHeap(int i) {
	if (i <= n) {
		rBuildHeap(2 * i);
		rBuildHeap(2 * i + 1);
		downHeap(i);
	}
}

void replaceKey(int z, int d) {
	// 우선순위큐 최단거리 수정
	Q[V[z]->distindex]->dist = d;
}

int isEmpty() {
	return (Q[1]->dist == INF);
}

// 우선순위큐에서 min 값 반환
int removeMin() {
	int v = Q[1]->v;
	if (Q[1]->dist == INF) {
		return -1;
	}
	else {
		Q[1]->dist = INF;
		rBuildHeap(1);
		return v;
	}
	
}


int opposite(int u, Inode* e) {
	if (u == E[e->edge]->v1) {
		return E[e->edge]->v2;
	}
	else {
		return E[e->edge]->v1;
	}
}

void DijkstraShortestPaths() {

	int u;
	Inode* e;

	// 출발 정점 최단거리 설정
	Q[s]->dist = 0;
	D[s - 1] = 0;
	rBuildHeap(1);


	while (!isEmpty()) {

		u = removeMin();
		// 정점의 최단거리 확정 여부 수정
		V[u]->state = 1;

		// 정점의 모든 부착간선에 대해서 실행
		e = V[u]->in->next;
		while (e != NULL) {
			int z = opposite(u, e);
			if (V[z]->state == 0) {
				if (D[u] + E[e->edge]->w < D[z]) {
					D[z] = D[u] + E[e->edge]->w;
					replaceKey(z, D[z]);
				}
			}
			e = e->next;
		}
		// replaceKey 작업 후 최소 힙 보정
		rBuildHeap(1);

		
	}

	// 최단거리 정보 출력
	for (int i = 0; i < n; i++) {
		if (i == s - 1 || D[i] == INF) {
			continue;
		}
		printf("%d %d\n", i + 1, D[i]);
	}

	

}
void freememory() {

	for (int i = 0; i < n; i++) {
		Inode* bp = V[i]->in;
		if (bp != NULL) {
			Inode* p = bp->next;
			while (p != NULL) {
				free(bp);
				bp = p;
				p = p->next;
			}
		}
		free(V[i]);
	}
	free(V);

	for (int i = 0; i < m; i++) {
		free(E[i]);
	}
	free(E);

	for (int i = 0; i <= n; i++) {
		free(Q[i]);
	}
	free(Q);

	free(D);
}
