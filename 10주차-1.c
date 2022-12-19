#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct inode {
	int vertex;
	int weight;
	struct inode* next;
}Inode;

typedef struct graph {
	// 인접리스트
	Inode* adjList[7]; 
}Graph;

// 그래프의 간선 수
int numOfEdge;


void insertEdge(Graph* G, int a, int b, int weight);
void printAdjNode(Graph* G, int num);
void sortGraph(Graph* G, int v);
void removeEdge(Graph* G, int a, int b);
Inode* resetWeight(Graph* G, int a, int b, int weight);
void modifyWeight(Graph* G, int a, int b, int weight);

void freememory(Graph* G);

int main() {
	// 그래프 초기화
	Graph* G = (Graph*)malloc(sizeof(Graph));
	for (int i = 1; i <= 6; i++) {
		G->adjList[i] = NULL;
	}
	// 그래프 생성
	insertEdge(G, 1, 2, 1);
	insertEdge(G, 1, 3, 1);
	insertEdge(G, 1, 4, 1);
	insertEdge(G, 1, 6, 2);
	insertEdge(G, 2, 3, 1);
	insertEdge(G, 3, 5, 4);
	insertEdge(G, 5, 5, 4);
	insertEdge(G, 5, 6, 3);

	numOfEdge = 8;

	char type;
	int v, a, b, w;
	while (1) {
		scanf("%c", &type);
		getchar();

		if (type == 'a') {
			scanf("%d", &v);
			getchar();
			if (v < 1 || v > 6) {
				printf("-1\n");
				continue;
			}
			printAdjNode(G, v);
		}
		if (type == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();
			if (a < 1 || a > 6 || b < 1 || b > 6) {
				printf("-1\n");
				continue;
			}
			modifyWeight(G, a, b, w);
		}
		if (type == 'q') {
			break;
		}
	}

	freememory(G);

	return 0;
}

void insertEdge(Graph* G, int a, int b, int weight) {
	Inode* Node1 = (Inode*)malloc(sizeof(Inode));
	// 정점 a로 향하는 가중치 weight의 간선을, 정점 b의 인접리스트에 추가
	Node1->vertex = a;
	Node1->weight = weight;
	Node1->next = G->adjList[b];

	G->adjList[b] = Node1;

	// 싸이클 처리
	if (a == b) return;

	Inode* Node2 = (Inode*)malloc(sizeof(Inode));
	// 정점 b로 향하는 가중치 weight의 간선을, 정점 a의 인접리스트에 추가
	Node2->vertex = b;
	Node2->weight = weight;
	Node2->next = G->adjList[a];

	G->adjList[a] = Node2;
}

void printAdjList(Graph* G) {
	for (int i = 1; i <= 6; i++) {
		// 정점 i 노드에 대한 인접한 정점번호 모두 출력
		Inode* p = G->adjList[i];
		while (p != NULL) {
			printf(" %d", p->vertex);
			p = p->next;
		}
		printf("\n");
	}
}

void printAdjNode(Graph* G, int v) {
	
	// 정점 v의 인접리스트 정점 기준 오름차순 정렬
	sortGraph(G, v);

	// 정점 v의 인접리스트 출력
	Inode* p = G->adjList[v];
	while (p != NULL) {
		printf(" %d %d", p->vertex, p->weight);
		p = p->next;
	}
	printf("\n");
}

void sortGraph(Graph* G, int v) {
	// 정점 v의 인접리스트 첫 노드 p로 설정
	Inode* p = G->adjList[v];
	while (p != NULL) {
		// p 노드가 인접리스트 마지막 노드 접근 시 종료
		if (p->next == NULL) {
			break;
		}
		// p 노드의 다음 노드를 p1으로 설정
		Inode* p1 = p->next;
		
		// 정점 오름차순 정렬
		while (p1 != NULL) {
			if (p->vertex > p1->vertex) {
				int tmp1, tmp2;
				tmp1 = p->vertex;
				p->vertex = p1->vertex;
				p1->vertex = tmp1;
				tmp2 = p->weight;
				p->weight = p1->weight;
				p1->weight = tmp2;
			}
			p1 = p1->next;
		}
		p = p->next;
	}
}

void removeEdge(Graph* G, int a, int b) {
	Inode* p = G->adjList[a];
	Inode* tmp = NULL;
	Inode* startpoint = p;

	while (p != NULL) {
		// 정점 a의 인접리스트에서 정점 b와 연결된 간선을 찾으면 수행
		if (p->vertex == b) {
			if (tmp == NULL) {
				p = p->next;
				startpoint = p;
			}
			else {
				tmp->next = p->next;
			}
			break;
		}
		tmp = p;
		p = p->next;
	}
	G->adjList[a] = startpoint;
}

Inode* resetWeight(Graph* G, int a, int b, int weight) {
	Inode* p = G->adjList[a];
	while (p != NULL) {
		if (p->vertex == b) {
			p->weight = weight;
			break;
		}
		p = p->next;
	}
	p = G->adjList[b];
	while (p != NULL) {
		if (p->vertex == a) {
			p->weight = weight;
			break;
		}
		p = p->next;
	}
	return p;
}

void modifyWeight(Graph* G, int a, int b, int weight) {

	// 가중치가 0이면 해당 간선 삭제
	if (weight == 0) {
		removeEdge(G, a, b);
		removeEdge(G, b, a);
		numOfEdge--;
		return;
	}

	// 가중치가 0이 아닌 경우 해당 간선의 가중치를 수정
	Inode* p = resetWeight(G, a, b, weight);
		
	// 간선이 없는 경우
	if (p == NULL) { 
		insertEdge(G, a, b, weight);
		numOfEdge++;
	}

	return;
}



void freememory(Graph* G) {
	for (int i = 1; i <= 6; i++) {
		Inode* p = G->adjList[i];
		if (p == NULL) continue;
		
		Inode* pnext = p->next;
		while (pnext != NULL) {
			free(p);
			p = pnext;
			pnext = pnext->next;
		}
	}
	free(G);
}