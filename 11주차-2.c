#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// ��������Ʈ ���
typedef struct enode {
	int v1;
	int v2;
	int state;
	struct enode* next;
} Enode;

// ������� ���
typedef struct inode {
	struct enode* edge;
} Inode;

// ��������Ʈ
typedef struct eList {
	struct enode* header;
	struct enode* tmp;
} eList;

// ť
typedef struct queue {
	int* storage;
	int front;
	int rear;
} Queue;

// ��������
int* vlist;
eList* elist;
int n, m, s;

// �Լ� ���
void insertEdge(Inode*** matrix, int v1, int v2, int state);
void BFS(Inode*** matrix, int s);
void push(Queue* Q,int v);
int pop(Queue* Q);
void freememory(Inode*** matrix);

int main() {

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	// ��������Ʈ �Ҵ�
	vlist = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		vlist[i] = 0;						// FRESH: 0, VISITED: 1
	}

	// ��������Ʈ �Ҵ�
	elist = (eList*)malloc(sizeof(eList));
	Enode* h1 = (Enode*)malloc(sizeof(Enode));
	h1->next = NULL;
	elist->header = h1;
	elist->tmp = h1;

	
	// ������� �Ҵ�
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
	// ������� ����
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &v1, &v2);
		getchar();
		insertEdge(matrix, v1, v2, 0);						// FRESH: 0, TREE: 1, CROSS: 2

	}

	// BFS ��ȸ
	BFS(matrix,s);

	// �������, ��������Ʈ, ��������Ʈ �޸� ����
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

	// ��������Ʈ�� ����
	elist->tmp->next = node;
	elist->tmp = elist->tmp->next;
}


void BFS(Inode*** matrix, int s) {


	// ť �Ҵ� �� �ʱ�ȭ
	Queue* Q = (Queue*)malloc(sizeof(Queue));
	Q->storage = (int*)malloc(sizeof(int) * n);
	Q->front = 0;
	Q->rear = 0;
	for (int i = 0; i < n; i++) {
		Q->storage[i] = 0;
	}


	// ���� ���� ť�� push & �湮 ó��
	push(Q, s);
	vlist[s - 1] = 1;
	int u;

	while (Q->front != Q->rear) {
		// pop
		u = pop(Q);
		// ���� ���
		printf("%d\n", u);


		// ��� ������ ���� �˻� ����
		for (int i = 0; i < n; i++) {
			// �湮���� �ʾҴ� �������� ����� ���
			if (matrix[u - 1][i]->edge != NULL && matrix[u - 1][i]->edge->state == 0) {							
				// ������ �湮���� �ʾҴٸ�
				if (vlist[i] == 0) {
					// ť�� push
					push(Q, i + 1);
					// ���� �湮 ó��
					vlist[i] = 1;
					// ���� tree ó��
					matrix[u - 1][i]->edge->state = 1;
				}
				else {
					// ���� cross ó��
					matrix[u - 1][i]->edge->state = 2;

				}
			}
		}

	}
	
	
}

// ť�� ������ ��忡 ����
void push(Queue* Q, int v) {
	Q->storage[Q->rear] = v;
	Q->rear++;
}

// ť�� ù ��� ��ȯ
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