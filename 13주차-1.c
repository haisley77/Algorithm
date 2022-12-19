/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// ��������Ʈ ���
typedef struct enode {
	int v1;
	int v2;
	int state;
	int weight;
	struct enode* next;
} Enode;

// ������� ���
typedef struct inode {
	struct enode* edge;
} Inode;

// ��������Ʈ
typedef struct eList {
	struct enode* header;
} eList;

// ���� ���
typedef struct vnode {
	int state;
	int min_w;
} Vnode;

// ��������
Vnode** vlist;
eList* elist;
Inode*** matrix;
int n, m;
int* Q;

// �Լ� ���
void insertEdge(int v1, int v2, int state);
void push(int v);
int pop();
void prim();
void freememory();

int main() {

	scanf("%d%d", &n, &m);
	getchar();

	// ��������Ʈ �Ҵ�
	vlist = (Vnode**)malloc(sizeof(Vnode*) * n);
	for (int i = 0; i < n; i++) {
		vlist[i] = (Vnode*)malloc(sizeof(Vnode));
		vlist[i]->min_w = -1;
		vlist[i]->state = 0;
	}

	// ��������Ʈ �Ҵ�
	elist = (eList*)malloc(sizeof(eList));
	Enode* h1 = (Enode*)malloc(sizeof(Enode));
	h1->next = NULL;
	elist->header = h1;


	// ������� �Ҵ�
	matrix = (Inode***)malloc(sizeof(Inode*) * n);
	for (int i = 0; i < n; i++) {
		matrix[i] = (Inode**)malloc(sizeof(Inode*) * n);
		for (int j = 0; j < n; j++) {
			matrix[i][j] = (Inode*)malloc(sizeof(Inode));
			matrix[i][j]->edge = NULL;
		}
	}


	int v1, v2, w;
	// ������� ����
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

	// �������, ��������Ʈ, ��������Ʈ �޸� ����
	freememory();


	return 0;
}

// ���� ���� �� ����
void insertEdge(int v1, int v2, int w) {
	Enode* node = (Enode*)malloc(sizeof(Enode));
	node->v1 = v1;
	node->v2 = v2;
	node->weight = w;
	node->state = 0;
	matrix[v1 - 1][v2 - 1]->edge = node;
	matrix[v2 - 1][v1 - 1]->edge = node;

	// ��������Ʈ�� ����
	node->next = elist->header->next;
	elist->header->next = node;
}

// �ε��� i ������ �ּҹ��� �켱����ť�� ����
void push(int i) {
	Q[i] = vlist[i]->min_w;
}

// �ּҹ��԰��� ���� �ε��� ��� & �켱����ť���� ����
int pop() {
	int minindex = -1;
	for (int i = 0; i < n; i++) {
		// �켱����ť�� ������ �ּҹ��԰� ����Ǿ� �ִ� ù ��带 ������ �ּڰ��� �ε����� ����
		if (minindex == -1) {
			if (Q[i] != -1) {
				minindex = i;
			}
			else continue;
		}
		else {
			// �ּҹ��԰� ����Ǿ� �ְ� �ּڰ����� ������ �ش� �ε����� �ּڰ��� �ε����� ����
			if (Q[i] != -1 && Q[i] < Q[minindex]) {
				minindex = i;
			}
		}
	}

	// �ּڰ��� �����ϸ� �ش� �ε����� ����� ���Ը� ���� (-1�� �ʱ�ȭ)
	if (minindex != -1) {
		Q[minindex] = -1;
	}

	// minindex�� -1�̸� ���α׷� ���� (Ʈ���ϼ�)
	return minindex;
}


// prim-jarnik MST �˰���
void prim() {
	int total = 0;
	int u, z;
	// ���� 1 �湮
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
		// �ּҹ��� ���� pop
		u = pop();
		// ������ ������ ����
		if (u == -1) break;
		total += vlist[u]->min_w;
		
		printf(" %d", u + 1);
		// ���� �湮 ó��
		vlist[u]->state = 1;

		for (int i = 0; i < n; i++) {
			if (matrix[u][i]->edge != NULL) {
				// ���� ���� �ε���
				z = i;
				
				// �湮���� ���� ���� �������� ����
				if (vlist[z]->state == 0) {
					// ó�� ���� �������� ������ ���
					if (Q[z] == -1) {
						// �ּҹ��� ���� �� �켱����ť�� �߰�
						vlist[z]->min_w = matrix[u][z]->edge->weight;
						push(z);
					}
					// ���� �������� ������ �� �ִ� ������ ���
					else {
						// �ּҹ��� ���� �� �켱����ť�� �ݿ�
						if (vlist[z]->min_w > matrix[u][z]->edge->weight) {
							vlist[z]->min_w = matrix[u][z]->edge->weight;
							push(z);
						}
					}
				}
				
				
			}
		}
		
	}
	// ���� �� ���
	printf("\n%d", total);
	
}

// �޸� ����
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