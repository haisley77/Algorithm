#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
// 간선리스트 노드
typedef struct enode {
	int origin;				// 시점
	int destination;		// 종점
} Enode;

// 진출,진입부착간선리스트 노드
typedef struct adjedge {
	int edge;				// 간선
	struct adjedge* next;
} adjedge;


// 정점리스트 노드
typedef struct vnode {
	char name;						// 정점 번호
	struct adjedge* outEdges;			// 진출부착간선리스트 헤더 노드
	struct adjedge* inEdges;			// 진입부착간선리스트 헤더 노드
	int inDegree;
} Vnode;

// 그래프 구조체
typedef struct graph {
	Vnode** vlist;
	Enode** elist;
} Graph;

// 큐 구조체
typedef struct queue {
	int storage[100];
	int front;
	int rear;
} Queue;

// 전역 변수
int n, m;
Graph* G;
int topOrder[100];
Queue* Q;

// 함수 목록
void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
int index(char vName);
void addFirst(adjedge** H, int i);
void topologicalSort();
int isEmpty();
void enqueue(int v);
int dequeue();
void initializeGraph();
void freememory();



void main() {

	buildGraph();
	topologicalSort();

	if (topOrder[0] == 0) {
		printf("0\n");
	}
	else {
		for (int i = 1; i <= n; i++) {
			printf("%c ", G->vlist[topOrder[i]]->name);
		}
	}

	freememory();

	return;
}

// 방향그래프 생성
void buildGraph() {

	char vName, uName, wName;

	initializeGraph();

	scanf("%d", &n);
	getchar();

	// 정점 삽입
	for (int i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}
	
	scanf("%d", &m);
	getchar();

	// 방향 간선 삽입
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}

}

// 정점 삽입
void insertVertex(char vName, int i) {
	
	G->vlist[i] = (Vnode*)malloc(sizeof(Vnode));
	G->vlist[i]->name = vName;

	// 진출간선리스트 초기화
	G->vlist[i]->outEdges = (adjedge*)malloc(sizeof(adjedge));
	G->vlist[i]->outEdges->next = NULL;

	// 진입간선리스트 초기화
	G->vlist[i]->inEdges = (adjedge*)malloc(sizeof(adjedge));
	G->vlist[i]->inEdges->next = NULL;
	
	// 정점 i 진입차수 초기화
	G->vlist[i]->inDegree = 0;							

}

// 간선 삽입
void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	// 간선리스트에 간선 추가
	G->elist[i] = (Enode*)malloc(sizeof(Enode));
	G->elist[i]->origin = u;
	G->elist[i]->destination = w;

	// 진입,진출간선리스트에 간선 삽입
	addFirst(&(G->vlist[u]->outEdges), i);
	addFirst(&(G->vlist[w]->inEdges), i);

	// 정점 w 진입차수 갱신
	G->vlist[w]->inDegree++;							
}

// 정점 인덱스 반환
int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (G->vlist[i]->name == vName) {
			return i;
		}
	}
}

// 진입,진출간선리스트 삽입
void addFirst(adjedge** H, int i) {
	adjedge* node = (adjedge*)malloc(sizeof(adjedge));
	node->edge = i;
	node->next = (*H)->next;
	(*H)->next = node;
}

// 위상 정렬
void topologicalSort() {
	// 큐 초기화
	Q = (Queue*)malloc(sizeof(Queue));
	Q->front = 0;
	Q->rear = 0;

	int in[100] = {0};				// 진입차수 배열

	// 다음 위상 순위 지정 가능한 정점 인덱스 큐에 삽입
	for (int i = 0; i < n; i++) {
		in[i] = G->vlist[i]->inDegree;
		if (in[i] == 0) {
			enqueue(i);
		}
	}

	int t = 1;						// 위상 순위
	int u, w;

	while (isEmpty() == 0) {
		// 위상 순위 지정
		u = dequeue();
		topOrder[t] = u;
		t++;

		// 진입 차수 수정
		adjedge* p = G->vlist[u]->outEdges->next;
		while (p != NULL) {
			w = G->elist[p->edge]->destination;
			in[w]--;
			if (in[w] == 0) {
				enqueue(w);
			}
			p = p->next;
		}
	}

	if (t <= n) {
		topOrder[0] = 0;
	}
	else {
		topOrder[0] = 1;
	}

}
int isEmpty() {
	if (Q->front == Q->rear) return 1;
	else return 0;
}

void enqueue(int v) {
	Q->storage[Q->rear++] = v;
}

int dequeue() {
	return Q->storage[Q->front++];
}

// 빈 그래프 G 초기화
void initializeGraph() {
	G = (Graph*)malloc(sizeof(Graph));
	G->vlist = (Vnode**)malloc(sizeof(Vnode*) * 100);
	G->elist = (Enode**)malloc(sizeof(Enode*) * 1000);
}

// 메모리 해제
void freememory() {

	free(Q);
	
	for (int i = 0; i < n; i++) {
		adjedge* bp = G->vlist[i]->outEdges;
		adjedge* p = G->vlist[i]->outEdges->next;
		while (p != NULL) {
			free(bp);
			bp = p;
			p = p->next;
		}
		free(G->vlist[i]);
	}
	free(G->vlist);

	for (int i = 0; i < m; i++) {
		free(G->elist[i]);
	}
	free(G->elist);
	free(G);

}

