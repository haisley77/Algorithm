#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
// ��������Ʈ ���
typedef struct enode {
	int origin;				// ����
	int destination;		// ����
} Enode;

// ����,���Ժ�����������Ʈ ���
typedef struct adjedge {
	int edge;				// ����
	struct adjedge* next;
} adjedge;


// ��������Ʈ ���
typedef struct vnode {
	char name;						// ���� ��ȣ
	struct adjedge* outEdges;			// ���������������Ʈ ��� ���
	struct adjedge* inEdges;			// ���Ժ�����������Ʈ ��� ���
	int inDegree;
} Vnode;

// �׷��� ����ü
typedef struct graph {
	Vnode** vlist;
	Enode** elist;
} Graph;

// ť ����ü
typedef struct queue {
	int storage[100];
	int front;
	int rear;
} Queue;

// ���� ����
int n, m;
Graph* G;
int topOrder[100];
Queue* Q;

// �Լ� ���
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

// ����׷��� ����
void buildGraph() {

	char vName, uName, wName;

	initializeGraph();

	scanf("%d", &n);
	getchar();

	// ���� ����
	for (int i = 0; i < n; i++) {
		scanf("%c", &vName);
		getchar();
		insertVertex(vName, i);
	}
	
	scanf("%d", &m);
	getchar();

	// ���� ���� ����
	for (int i = 0; i < m; i++) {
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i);
	}

}

// ���� ����
void insertVertex(char vName, int i) {
	
	G->vlist[i] = (Vnode*)malloc(sizeof(Vnode));
	G->vlist[i]->name = vName;

	// ���Ⱓ������Ʈ �ʱ�ȭ
	G->vlist[i]->outEdges = (adjedge*)malloc(sizeof(adjedge));
	G->vlist[i]->outEdges->next = NULL;

	// ���԰�������Ʈ �ʱ�ȭ
	G->vlist[i]->inEdges = (adjedge*)malloc(sizeof(adjedge));
	G->vlist[i]->inEdges->next = NULL;
	
	// ���� i �������� �ʱ�ȭ
	G->vlist[i]->inDegree = 0;							

}

// ���� ����
void insertDirectedEdge(char uName, char wName, int i) {
	int u, w;

	u = index(uName);
	w = index(wName);

	// ��������Ʈ�� ���� �߰�
	G->elist[i] = (Enode*)malloc(sizeof(Enode));
	G->elist[i]->origin = u;
	G->elist[i]->destination = w;

	// ����,���Ⱓ������Ʈ�� ���� ����
	addFirst(&(G->vlist[u]->outEdges), i);
	addFirst(&(G->vlist[w]->inEdges), i);

	// ���� w �������� ����
	G->vlist[w]->inDegree++;							
}

// ���� �ε��� ��ȯ
int index(char vName) {
	for (int i = 0; i < n; i++) {
		if (G->vlist[i]->name == vName) {
			return i;
		}
	}
}

// ����,���Ⱓ������Ʈ ����
void addFirst(adjedge** H, int i) {
	adjedge* node = (adjedge*)malloc(sizeof(adjedge));
	node->edge = i;
	node->next = (*H)->next;
	(*H)->next = node;
}

// ���� ����
void topologicalSort() {
	// ť �ʱ�ȭ
	Q = (Queue*)malloc(sizeof(Queue));
	Q->front = 0;
	Q->rear = 0;

	int in[100] = {0};				// �������� �迭

	// ���� ���� ���� ���� ������ ���� �ε��� ť�� ����
	for (int i = 0; i < n; i++) {
		in[i] = G->vlist[i]->inDegree;
		if (in[i] == 0) {
			enqueue(i);
		}
	}

	int t = 1;						// ���� ����
	int u, w;

	while (isEmpty() == 0) {
		// ���� ���� ����
		u = dequeue();
		topOrder[t] = u;
		t++;

		// ���� ���� ����
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

// �� �׷��� G �ʱ�ȭ
void initializeGraph() {
	G = (Graph*)malloc(sizeof(Graph));
	G->vlist = (Vnode**)malloc(sizeof(Vnode*) * 100);
	G->elist = (Enode**)malloc(sizeof(Enode*) * 1000);
}

// �޸� ����
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

