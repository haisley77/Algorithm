#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// 간선리스트 노드
typedef struct enode {
	int w;
	struct enode* next;
} Enode;

// 인접행렬 노드
typedef struct inode {
	struct enode* edge;
} Inode;

typedef struct eList {
	struct enode* header;
	struct enode* tmp;
} eList;

int* vlist;
eList* elist;

void insertEdge(Inode***, int i, int j, int w);
void printAdjNode(Inode***, int v);
void modifyWeight(Inode*** matrix, int a, int b, int w);
void freememory(Inode***);

int main() {

	// 정점리스트, 간선리스트 헤더노드 초기화
	vlist = (int*)malloc(sizeof(int)*6);
	for (int i = 0; i < 6; i++) {
		// 정점 번호 저장
		vlist[i] = i + 1;
	}

	// 간선리스트 헤더노드
	elist = (eList*)malloc(sizeof(eList));
	Enode* header = (Enode*)malloc(sizeof(Enode));
	header->next = NULL;
	elist->header = header;
	elist->tmp = header;
	


	// 인접행렬 초기화
	Inode*** matrix = NULL;
	matrix = (Inode***)malloc(sizeof(Inode*) * 6);
	for (int i = 0; i < 6; i++) {
		matrix[i] = (Inode**)malloc(sizeof(Inode*) * 6);
		for (int j = 0; j < 6; j++) {
			matrix[i][j] = (Inode*)malloc(sizeof(Inode));
			matrix[i][j]->edge = NULL;
		}
	}


	// 인접행렬 생성
	insertEdge(matrix, 0, 1, 1);
	insertEdge(matrix, 0, 2, 1);
	insertEdge(matrix, 0, 3, 1);
	insertEdge(matrix, 0, 5, 2);
	insertEdge(matrix, 1, 2, 1);
	insertEdge(matrix, 2, 4, 4);
	insertEdge(matrix, 4, 4, 4);
	insertEdge(matrix, 4, 5, 3);


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
			printAdjNode(matrix, v - 1);
		}
		if (type == 'm') {
			scanf("%d %d %d", &a, &b, &w);
			getchar();
			if (a < 1 || a > 6 || b < 1 || b > 6) {
				printf("-1\n");
				continue;
			}
			modifyWeight(matrix, a-1, b-1, w);
		}
		if (type == 'q') {
			break;
		}
	}

	free(vlist);
	free(elist);
	freememory(matrix);
	

	return 0;
}

void insertEdge(Inode*** matrix, int i, int j, int w) {
	Enode* node = (Enode*)malloc(sizeof(Enode));
	node->w = w;
	node->next = NULL;
	matrix[i][j]->edge = node;
	// 싸이클 처리
	if (i == j) return;

	matrix[j][i]->edge = node;

	// 간선리스트에 삽입
	elist->tmp->next = node;
	elist->tmp = elist->tmp->next;
}

void printAdjNode(Inode*** matrix, int v) {

	// 정점 v의 인접 정점 번호 & 간선 가중치 출력
	for (int i = 0; i < 6; i++) {
		if (matrix[v][i]->edge != NULL) {
			printf(" %d %d", vlist[i], matrix[v][i]->edge->w);
		}
	}
	printf("\n");

}


void modifyWeight(Inode*** matrix, int a, int b, int w) {

	// 가중치가 0이면 해당 간선 삭제
	if (w == 0) {
		// 간선리스트에서 간선 삭제
		Enode* p = elist->header;
		while (p->next != NULL) {
			if (p->next == matrix[a][b]->edge) {
				p->next = matrix[a][b]->edge->next;
				free(matrix[a][b]->edge);
				break;
			}
			p = p->next;
		}
		// 인접행렬 재정의
		matrix[a][b]->edge = NULL;
		matrix[b][a]->edge = NULL;
	}
	// 간선이 없는 경우 간선 추가
	else if (matrix[a][b]->edge == NULL) {
		insertEdge(matrix, a, b, w);
	}
	// 가중치가 0이 아닌 경우 해당 간선의 가중치 수정
	else {
		matrix[a][b]->edge->w = w;
	}


	return;
}

void freememory(Inode*** matrix) {
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			free(matrix[i][j]);
		}
		free(matrix[i]);
	}
	free(matrix);
}

