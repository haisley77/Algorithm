#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
// 배열로 구현

// 간선리스트 노드
typedef struct enode {
	struct vnode* v1;				// 정점1 노드
	struct vnode* v2;				// 정점2 노드
	int label;						// 방문 여부
} Enode;

// 인접리스트 노드
typedef struct inode {
	struct enode* edge;				// 간선
	struct inode* next;				// 인접리스트 다음 노드
} Inode;

// 정점리스트 노드
typedef struct vnode {
	int num;						// 정점 번호
	struct inode* header;			// 인접리스트 헤더 노드
	int label;						// 방문 여부
} Vnode;

// 전역 변수
Vnode** vlist;
Enode** elist;
int current_edge_index = 0;
int n, m, s;

// 함수 목록
void init_vlist();
void init_elist();
void createEdgeToList();
Vnode* opposite(Enode* edge, int v);
void sortIncidenceList(int i);
void DFS(Vnode* u);
void freememory();

int main() {

	// n, m, s 입력
	scanf("%d%d%d", &n, &m, &s);
	getchar();


	// 정점리스트 메모리 할당
	init_vlist();
	// 간선리스트 메모리 할당
	init_elist();

	// m개의 간선을 간선리스트에 추가
	// m개의 간선을 인접리스트에 추가
	for (int i = 0; i < m; i++) {
		createEdgeToList();
	}

	DFS(vlist[s-1]);

	freememory();

	return 0;
}

void init_vlist() {
	vlist = (Vnode**)malloc(sizeof(Vnode*) * n);
	for (int i = 0; i < n; i++) {
		vlist[i] = (Vnode*)malloc(sizeof(Vnode));
		vlist[i]->num = i + 1;								// 정점 번호 저장
		vlist[i]->label = 0;								// 방문하지 않은 정점
		vlist[i]->header = (Inode*)malloc(sizeof(Inode));
		vlist[i]->header->next = NULL;						// 정점 인접리스트 헤더
	}
}

void init_elist() {
	elist = (Enode**)malloc(sizeof(Enode*) * m);
	for (int i = 0; i < m; i++) {
		elist[i] = (Enode*)malloc(sizeof(Enode));
	}
}

void createEdgeToList() {
	int v1, v2;
	// 간선 입력
	scanf("%d%d", &v1, &v2);
	getchar();


	// 간선 생성
	Enode* newEnode = (Enode*)malloc(sizeof(Enode));
	newEnode->v1 = vlist[v1-1];
	newEnode->v2 = vlist[v2-1];
	newEnode->label = 0;

	// 간선리스트에 간선 추가
	elist[current_edge_index++] = newEnode;

	// v1, v2 정점 인접리스트에 간선 추가
	Inode* p = vlist[v1 - 1]->header->next;				// v1 인접리스트 헤드 노드
	
	Inode* newInode1 = (Inode*)malloc(sizeof(Inode));	// 인접리스트 노드 생성
	newInode1->edge = newEnode;
	newInode1->next = p;

	vlist[v1 - 1]->header->next = newInode1;

	p = vlist[v2 - 1]->header->next;				// v1 인접리스트 헤드 노드

	Inode* newInode2 = (Inode*)malloc(sizeof(Inode));	// 인접리스트 노드 생성
	newInode2->edge = newEnode;
	newInode2->next = p;

	vlist[v2 - 1]->header->next = newInode2;
	


	for (int i = 0; i < n; i++) {
		sortIncidenceList(i);
	}
	
}

// 간선 도착 정점 반환
Vnode* opposite(Enode* edge, int v) {
	if (edge->v1 == vlist[v-1]) {
		return edge->v2;
	}
	if (edge->v2 == vlist[v-1]) {
		return edge->v1;
	}
	return NULL;
}

void sortIncidenceList(int i) {
	int v = vlist[i]->num;				// 정점 번호
	Vnode* currentInode_opposite = NULL;
	Vnode* nextInode_opposite = NULL;

	// 정점 i의 인접리스트 첫 노드 p로 설정
	Inode* p = vlist[i]->header->next;
	while (p != NULL) {
		// p 노드가 인접리스트 마지막 노드 접근 시 종료
		if (p->next == NULL) {
			break;
		}
		// p 노드의 다음 노드를 p1으로 설정
		Inode* p1 = p->next;


		// 정점 오름차순 정렬
		while (p1 != NULL) {
			if (opposite(p->edge, v) == p->edge->v1) {
				currentInode_opposite = p->edge->v1;
			}
			if (opposite(p->edge, v) == p->edge->v2) {
				currentInode_opposite = p->edge->v2;
			}
			if (opposite(p1->edge, v) == p1->edge->v1) {
				nextInode_opposite = p1->edge->v1;
			}
			if (opposite(p1->edge, v) == p1->edge->v2) {
				nextInode_opposite = p1->edge->v2;
			}

			if (currentInode_opposite->num > nextInode_opposite->num) {
				Enode* tmp;
				tmp = p->edge;
				p->edge = p1->edge;
				p1->edge = tmp;
			}
			p1 = p1->next;
		}
		p = p->next;
	}
}


void DFS(Vnode* u) {

	if (u->label == 0) {														// FRESH
		printf("%d\n", u->num);
		u->label = 1;															// VISITED
	}

	Inode* p = u->header->next;
	while (p != NULL) {
		if (opposite(p->edge, u->num)->label == 1) {							// VISITED
			p->edge->label = 2;													// BACK
		}
		if (opposite(p->edge, u->num)->label == 0) {							// FRESH
			p->edge->label = 1;													// VISITED
			DFS(opposite(p->edge, u->num));
		}
		p = p->next;
	}
}

void freememory() {
	// 인접리스트, 정점리스트 메모리 해제
	for (int i = 0; i < n; i++) {
		Inode* beforetmp = vlist[i]->header;
		Inode* tmp = beforetmp->next;
		while (tmp != NULL) {
			free(beforetmp);
			beforetmp = beforetmp->next;
			tmp = tmp->next;
		}
		free(vlist[i]);
	}
	free(vlist);

	for (int i = 0; i < m; i++) {
		free(elist[i]);
	}
	free(elist);
}