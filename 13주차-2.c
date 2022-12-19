#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


// ���� ���
typedef struct vnode {
	int v;
	int set;
	struct vnode* next;
} Vnode;

// ���� ���
typedef struct edge {
	Vnode* v1;
	Vnode* v2;
	int w;
} Edge;

// �и����� ���
typedef struct dnode {
	int size;
	struct vnode* head;
	struct vnode* tail;
} Dnode;


// �и�����
Dnode** D;
// ���� ����Ʈ (�켱����ť)
Edge** E;

// ��������
int n, m;
int index = 1;					// insertEdge �� �ε���
int front, rear;				// �켱����ť�� front, rear ����

// �Լ� ���
void insertEdge(int v1, int v2, int w);
void insertVertex(int v);
void rBuildHeap(int i);
void downHeap(int i, int n);
void makePQ();
Edge* pop();
int find(Vnode* u,Vnode* v);
void union_(Vnode* u,Vnode* v);
void kruskal();
void freememory();

int main() {

	int v1, v2, w;

	scanf("%d%d", &n, &m);
	getchar();

	// �и����� ����
	D = (Dnode**)malloc(sizeof(Dnode*) * n);
	for (int i = 0; i < n; i++) {
		D[i] = (Dnode*)malloc(sizeof(Dnode));
		insertVertex(i);
	}

	// ���� ����Ʈ ����
	E = (Edge**)malloc(sizeof(Edge*) * (m + 1));
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(v1, v2, w);
	}

	// front, rear ����
	front = 1;
	rear = m;

	// ��������Ʈ -> �켱����ť
	makePQ();

	// ũ�罺Į
	kruskal();


	return 0;
}

// ���� ����
void insertEdge(int v1, int v2, int w) {
	E[index] = (Edge*)malloc(sizeof(Edge));
	E[index]->v1 = D[v1-1]->head;
	E[index]->v2 = D[v2-1]->head;
	E[index]->w = w;

	// ���� ���� ������ ���� �ε��� �缳��
	index++;

}

// ���� ����
void insertVertex(int v) {
	Vnode* node = (Vnode*)malloc(sizeof(Vnode));
	node->v = v;
	node->set = v;
	node->next = NULL;

	D[v]->head = node;
	D[v]->tail = node;
	D[v]->size = 1;
}

// ����� �ִ��� ����
void rBuildHeap(int i) {
	if (i <= m) {
		rBuildHeap(2 * i);
		rBuildHeap(2 * i + 1);
		downHeap(i, m);
	}
}

void downHeap(int i,int n) {
	Edge* tmp;
	int left, right;
	left = 2 * i;
	right = 2 * i + 1;

	if (left > n && right > n) return;

	if (right <= n) {
		if (E[left]->w < E[right]->w) {
			if (E[right]->w > E[i]->w) {
				tmp = E[i];
				E[i] = E[right];
				E[right] = tmp;
				downHeap(right, n);
			}
		}
		else {
			if (E[left]->w > E[i]->w) {
				tmp = E[i];
				E[i] = E[left];
				E[left] = tmp;
				downHeap(left, n);
			}
		}
	}
	else if (left <= n) {
		if (E[left]->w > E[i]->w) {
			tmp = E[i];
			E[i] = E[left];
			E[left] = tmp;
			downHeap(left, n);
		}
	}
	else return;
}

// �켱����ť ����
void makePQ() {

	rBuildHeap(1);

	Edge* tmp;
	for (int i = m; i > 1; i--) {
		tmp = E[i];
		E[i] = E[1];
		E[1] = tmp;
		downHeap(1, i - 1);
	}
}

// �켱����ť���� �ּ� ����ġ ���� ��ȯ
Edge* pop() {
	if (front > rear) return NULL;
	else return E[front++];
}

// �� ������ ���� ���տ� �ִ��� Ȯ���ϴ� �Լ�
int find(Vnode* u, Vnode* v) {

	if (u->set == v->set) return 1;
	else return 0;

	return 0;

}

// �� ������ ���� �������� ���ϴ� �Լ�
void union_(Vnode* u, Vnode* v) {
	if (D[u->set]->size < D[v->set]->size) {

		Vnode* p = D[u->set]->head;
		while (p != NULL) {
			p->set = v->set;
			p = p->next;
		}
		D[v->set]->size += D[u->set]->size;
		D[v->set]->tail->next = D[u->set]->head;
		D[u->set]->size = 0;
		D[u->set]->head = NULL;
		D[u->set]->tail = NULL;
	}


	else {

		Vnode* p = D[v->set]->head;
		while (p != NULL) {
			p->set = u->set;
			p = p->next;
		}

		D[u->set]->size += D[v->set]->size;
		D[u->set]->tail->next = D[v->set]->head;
		D[v->set]->size = 0;
		D[v->set]->head = NULL;
		D[v->set]->tail = NULL;
	}

}

// ũ�罺Į
void kruskal() {
	int total = 0;
	Edge* e;

	while (1) {
		// �ּ� ����ġ ���� pop
		e = pop();
		if (e == NULL) break;
		
		// ���� ���տ� �������� �ʴ� ���
		if (find(e->v1, e->v2) == 0) {
			total += e->w;
			printf(" %d", e->w);
			// ���� �������� ���ϱ�
			union_(e->v1, e->v2);
		}
		
	}

	// ���� �� ���
	printf("\n%d", total);
}



// �޸� ����
void freememory() {
	for (int i = 0; i < n; i++) {
		Vnode* bp = D[i]->head;
		if (bp != NULL) {
			Vnode* p = bp->next;
			while (p != NULL) {
				free(bp);
				bp = p;
				p = p->next;
			}
		}
		free(D[i]);
	}
	free(D);

	for (int i = 0; i <= m; i++) {
		free(E[i]);
	}
	free(E);

}