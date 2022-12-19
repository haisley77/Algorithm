/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct inode {
	int edge;						// edge �ε���
	struct inode* next;				// ���� ���� edge
} Inode;

typedef struct dnode {
	int v;							// ���� �ε���
	int dist;						// �ǽð� �ִ� �Ÿ�
} Dnode;

typedef struct vertex {
	int distindex;					// ť �ε���
	int state;						// �ִ� �Ÿ� Ȯ�� ����
	struct inode* in;				// ��������Ʈ ���
} Vertex;

typedef struct edge {
	int v1;						// ���� 1 �ε���
	int v2;						// ���� 2 �ε���
	int w;						// �Ÿ� 
} Edge;


int INF = 30000;
int n, m, s;
// ��������Ʈ
Edge** E;
// ��������Ʈ
Vertex** V;
// �켱����ť
Dnode** Q;
// �ִܰŸ� ���� ����Ʈ
int* D;

// �׷��� �Լ�
void insertVertex(int i);
void insertEdge(int i, int v1, int v2, int w);
int opposite(int u, Inode* e);

// �켱����ť(��) �Լ�
void downHeap(int i);
void rBuildHeap(int i);
int removeMin();
int isEmpty();
void replaceKey(int z, int d);

// ���ͽ�Ʈ�� �˰���
void DijkstraShortestPaths();

// �޸� ���� �Լ�
void freememory();

void main() {

	int v1, v2, w;

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	
	// ���� ����Ʈ �ʱ�ȭ
	V = (Vertex**)malloc(sizeof(Vertex*) * n);
	for (int i = 0; i < n; i++) {
		
		insertVertex(i);
	}

	// ���� ����Ʈ �ʱ�ȭ
	E = (Edge**)malloc(sizeof(Edge*) * m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(i, v1, v2, w);
	}

	// �ִܰŸ� ���� ����Ʈ �ʱ�ȭ
	D = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		D[i] = INF;
	}
	// �켱����ť �ʱ�ȭ
	Q = (Dnode**)malloc(sizeof(Dnode) * (n + 1));
	for (int i = 0; i <= n; i++) {
		Q[i] = (Dnode*)malloc(sizeof(Dnode));
		Q[i]->dist = INF;
		Q[i]->v = i - 1;
	}

	// ���ͽ�Ʈ�� �ִ� ��� Ž��
	DijkstraShortestPaths();

	freememory();

	return;
}

void insertVertex(int i) {
	V[i] = (Vertex*)malloc(sizeof(Vertex));
	// ��� ���� ����
	V[i]->state = 0;
	// ��������Ʈ ���
	V[i]->in = (Inode*)malloc(sizeof(Inode));
	V[i]->in->next = NULL;
	// ������ �켱����ť �ִܰŸ� ���� �ε���
	V[i]->distindex = i + 1;

}

void insertEdge(int i, int v1, int v2, int w) {
	// ���� ����
	E[i] = (Edge*)malloc(sizeof(Edge));
	E[i]->v1 = v1 - 1;
	E[i]->v2 = v2 - 1;
	E[i]->w = w;

	// v1 ���� ��������Ʈ �߰�
	Inode* node1 = (Inode*)malloc(sizeof(Inode));
	node1->edge = i;
	node1->next = V[v1 - 1]->in->next;
	V[v1 - 1]->in->next = node1;

	// v2 ���� ��������Ʈ �߰�
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
				// ������ �켱����ť �ִܰŸ� ���� �ε��� ����
				V[Q[i]->v]->distindex = right;

				// �켱����ť ���� swap
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

// ����� �ּ� �� ����
void rBuildHeap(int i) {
	if (i <= n) {
		rBuildHeap(2 * i);
		rBuildHeap(2 * i + 1);
		downHeap(i);
	}
}

void replaceKey(int z, int d) {
	// �켱����ť �ִܰŸ� ����
	Q[V[z]->distindex]->dist = d;
}

int isEmpty() {
	return (Q[1]->dist == INF);
}

// �켱����ť���� min �� ��ȯ
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

	// ��� ���� �ִܰŸ� ����
	Q[s]->dist = 0;
	D[s - 1] = 0;
	rBuildHeap(1);


	while (!isEmpty()) {

		u = removeMin();
		// ������ �ִܰŸ� Ȯ�� ���� ����
		V[u]->state = 1;

		// ������ ��� ���������� ���ؼ� ����
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
		// replaceKey �۾� �� �ּ� �� ����
		rBuildHeap(1);

		
	}

	// �ִܰŸ� ���� ���
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
*/