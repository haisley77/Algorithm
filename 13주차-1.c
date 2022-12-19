/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// 간선리스트 노드
typedef struct enode {
	int v1;
	int v2;
	int state;
	int weight;
	struct enode* next;
} Enode;

// 인접행렬 노드
typedef struct inode {
	struct enode* edge;
} Inode;

// 간선리스트
typedef struct eList {
	struct enode* header;
} eList;

// 정점 노드
typedef struct vnode {
	int state;
	int min_w;
} Vnode;

// 전역변수
Vnode** vlist;
eList* elist;
Inode*** matrix;
int n, m;
int* Q;

// 함수 목록
void insertEdge(int v1, int v2, int state);
void push(int v);
int pop();
void prim();
void freememory();

int main() {

	scanf("%d%d", &n, &m);
	getchar();

	// 정점리스트 할당
	vlist = (Vnode**)malloc(sizeof(Vnode*) * n);
	for (int i = 0; i < n; i++) {
		vlist[i] = (Vnode*)malloc(sizeof(Vnode));
		vlist[i]->min_w = -1;
		vlist[i]->state = 0;
	}

	// 간선리스트 할당
	elist = (eList*)malloc(sizeof(eList));
	Enode* h1 = (Enode*)malloc(sizeof(Enode));
	h1->next = NULL;
	elist->header = h1;


	// 인접행렬 할당
	matrix = (Inode***)malloc(sizeof(Inode*) * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (Inode**)malloc(sizeof(Inode*) * n);
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (Inode*)malloc(sizeof(Inode));
			matrix[i][j]->edge = NULL;
		}
	}


	int v1, v2, w;
	// 인접행렬 생성
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(v1, v2, w);						// FRESH: 0, TREE: 1, CROSS: 2

	}

	Q = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		Q[i] = -1;
	}


	prim();

	// 인접행렬, 간선리스트, 정점리스트 메모리 해제
	freememory();


	return 0;
}

// 간선 생성 및 삽입
void insertEdge(int v1, int v2, int w) {
	Enode* node = (Enode*)malloc(sizeof(Enode));
	node->v1 = v1;
	node->v2 = v2;
	node->weight = w;
	node->state = 0;
	matrix[v1 - 1][v2 - 1]->edge = node;
	matrix[v2 - 1][v1 - 1]->edge = node;

	// 간선리스트에 삽입
	node->next = elist->header->next;
	elist->header->next = node;
}

// 인덱스 i 정점의 최소무게 우선순위큐에 삽입
void push(int i) {
	Q[i] = vlist[i]->min_w;
}

// 최소무게간선 정점 인덱스 출력 & 우선순위큐에서 삭제
int pop() {
	int minindex = -1;
	for (int i = 0; i < n; i++) {
		// 우선순위큐에 정점의 최소무게가 저장되어 있는 첫 노드를 만나면 최솟값의 인덱스로 설정
		if (minindex == -1) {
			if (Q[i] != -1) {
				minindex = i;
			}
			else continue;
		}
		else {
			// 최소무게가 저장되어 있고 최솟값보다 작으면 해당 인덱스를 최솟값의 인덱스로 설정
			if (Q[i] != -1 && Q[i] < Q[minindex]) {
				minindex = i;
			}
		}
	}

	// 최솟값이 존재하면 해당 인덱스에 저장된 무게를 삭제 (-1로 초기화)
	if (minindex != -1) {
		Q[minindex] = -1;
	}

	// minindex가 -1이면 프로그램 종료 (트리완성)
	return minindex;
}


// prim-jarnik MST 알고리즘
void prim() {
	int total = 0;
	int u, z;
	// 정점 1 방문
	printf(" 1");
	vlist[0]->state = 1;
	vlist[0]->min_w = 0;


	for (int i = 0; i < n; i++) {
		if (matrix[0][i]->edge != NULL) {
			vlist[i]->min_w = matrix[0][i]->edge->weight;
			push(i);
		}
	}


	while (1) {
		// 최소무게 정점 pop
		u = pop();
		// 정점이 없으면 종료
		if (u == -1) break;
		total += vlist[u]->min_w;
		
		printf(" %d", u + 1);
		// 정점 방문 처리
		vlist[u]->state = 1;

		for (int i = 0; i < n; i++) {
			if (matrix[u][i]->edge != NULL) {
				// 인접 정점 인덱스
				z = i;
				
				// 방문하지 않은 인접 정점에서 수행
				if (vlist[z]->state == 0) {
					// 처음 인접 정점으로 설정된 경우
					if (Q[z] == -1) {
						// 최소무게 설정 후 우선순위큐에 추가
						vlist[z]->min_w = matrix[u][z]->edge->weight;
						push(z);
					}
					// 인접 정점으로 설정된 적 있는 정점인 경우
					else {
						// 최소무게 수정 후 우선순위큐에 반영
						if (vlist[z]->min_w > matrix[u][z]->edge->weight) {
							vlist[z]->min_w = matrix[u][z]->edge->weight;
							push(z);
						}
					}
				}
				
				
			}
		}
		
	}
	// 최종 값 출력
	printf("\n%d", total);
	
}

// 메모리 해제
void freememory() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}
	free(matrix);

	Enode* bp = elist->header;
	Enode* p = elist->header->next;
	while (p != NULL) {
		free(bp);
		bp = p;
		p = p->next;
	}
	free(elist);

	for (int i = 0; i < n; i++){
		free(vlist[i]);
	}
	free(vlist);
}
*/