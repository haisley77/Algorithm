#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// 간선리스트 노드
typedef struct enode {
	int v1;
	int v2;
	int state;
	struct enode* next;
} Enode;

// 인접행렬 노드
typedef struct inode {
	struct enode* edge;
} Inode;

// 간선리스트
typedef struct eList {
	struct enode* header;
	struct enode* tmp;
} eList;

// 큐
typedef struct queue {
	int* storage;
	int front;
	int rear;
} Queue;

// 전역변수
int* vlist;
eList* elist;
int n, m, s;

// 함수 목록
void insertEdge(Inode*** matrix, int v1, int v2, int state);
void BFS(Inode*** matrix, int s);
void push(Queue* Q,int v);
int pop(Queue* Q);
void freememory(Inode*** matrix);

int main() {

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	// 정점리스트 할당
	vlist = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		vlist[i] = 0;						// FRESH: 0, VISITED: 1
	}

	// 간선리스트 할당
	elist = (eList*)malloc(sizeof(eList));
	Enode* h1 = (Enode*)malloc(sizeof(Enode));
	h1->next = NULL;
	elist->header = h1;
	elist->tmp = h1;

	
	// 인접행렬 할당
	Inode*** matrix = NULL;
	matrix = (Inode***)malloc(sizeof(Inode*) * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (Inode**)malloc(sizeof(Inode*) * n);
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (Inode*)malloc(sizeof(Inode));
			matrix[i][j]->edge = NULL;
		}
	}

	int v1, v2;
	// 인접행렬 생성
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &v1, &v2);
		getchar();
		insertEdge(matrix, v1, v2, 0);						// FRESH: 0, TREE: 1, CROSS: 2

	}

	// BFS 순회
	BFS(matrix,s);

	// 인접행렬, 간선리스트, 정점리스트 메모리 해제
	freememory(matrix);
	free(vlist);

	return 0;
}

void insertEdge(Inode*** matrix, int v1, int v2, int state) {
	Enode* node = (Enode*)malloc(sizeof(Enode));
	node->state = state;
	node->next = NULL;
	node->v1 = v1;
	node->v2 = v2;
	matrix[v1-1][v2-1]->edge = node;
	matrix[v2-1][v1-1]->edge = node;

	// 간선리스트에 삽입
	elist->tmp->next = node;
	elist->tmp = elist->tmp->next;
}


void BFS(Inode*** matrix, int s) {


	// 큐 할당 및 초기화
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->storage = (int*)malloc(sizeof(int) * n);
	Q->front = 0;
	Q->rear = 0;
	for (int i = 0; i < n; i++) {
		Q->storage[i] = 0;
	}


	// 시작 정점 큐에 push & 방문 처리
	push(Q, s);
	vlist[s - 1] = 1;
	int u;

	while (Q->front != Q->rear) {
		// pop
		u = pop(Q);
		// 정점 출력
		printf("%d\n", u);


		// 모든 정점에 대해 검사 수행
		for (int i = 0; i < n; i++) {
			// 방문하지 않았던 간선으로 연결된 경우
			if (matrix[u - 1][i]->edge != NULL && matrix[u - 1][i]->edge->state == 0) {							
				// 정점을 방문하지 않았다면
				if (vlist[i] == 0) {
					// 큐에 push
					push(Q, i + 1);
					// 정점 방문 처리
					vlist[i] = 1;
					// 간선 tree 처리
					matrix[u - 1][i]->edge->state = 1;
				}
				else {
					// 간선 cross 처리
					matrix[u - 1][i]->edge->state = 2;

				}
			}
		}

	}
	
	
}

// 큐의 마지막 노드에 삽입
void push(Queue* Q, int v) {
	Q->storage[Q->rear] = v;
	Q->rear++;
}

// 큐의 첫 노드 반환
int pop(Queue* Q) {
	int e = Q->storage[Q->front];
	Q->storage[Q->front] = 0;
	Q->front++;
	return e;
}


void freememory(Inode*** matrix) {
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

}