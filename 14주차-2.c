/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


typedef struct edge {
	int v1;						// ���� 1 �ε���
	int v2;						// ���� 2 �ε���
	int w;						// ����
} Edge;

int INF = 30000;
int n, m, s;
// ��������Ʈ
Edge** E;
// �ִ� �Ÿ� ���� ���� ����Ʈ
int* D;

// �Լ� ���
void insertEdge(int i, int v1, int v2, int w);
int getMin(int a, int b);
void BellmanFordShortestPaths();
void freememory();

int main() {

	int v1, v2, w;

	scanf("%d%d%d", &n, &m, &s);
	getchar();

	// �ִ� �Ÿ� ���� ���� ����Ʈ �ʱ�ȭ
	D = (int*)malloc(sizeof(int) * n);
	for (int i = 0; i < n; i++) {
		D[i] = INF;
	}

	// ���� ����Ʈ �ʱ�ȭ
	E = (Edge**)malloc(sizeof(Edge*) * m);
	for (int i = 0; i < m; i++) {
		scanf("%d%d%d", &v1, &v2, &w);
		getchar();
		insertEdge(i, v1, v2, w);
	}

	// �������� 
	BellmanFordShortestPaths();

	// �޸� ����
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

	// n-1 �� ����
	for (int i = 1; i < n; i++) {
		// ��� ������ ���� ����
		for (int j = 0; j < m; j++) {
			u = E[j]->v1;
			z = E[j]->v2;
			if (D[u] != INF) {
				D[z] = getMin(D[z], D[u] + E[j]->w);
			}
		}

	}

	
	// �ִ� �Ÿ� ���� ���
	for (int i = 0; i < n; i++) {
		if (i == s - 1 || D[i] == INF) {
			continue;
		}
		printf("%d %d\n", i + 1, D[i]);
	}
	
}

// �޸� ����
void freememory() {
	
	for (int i = 0; i < m; i++) {
		free(E[i]);
	}
	free(E);

	free(D);
}
*/