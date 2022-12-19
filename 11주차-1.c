#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)
// �迭�� ����

// ��������Ʈ ���
typedef struct enode {
	struct vnode* v1;				// ����1 ���
	struct vnode* v2;				// ����2 ���
	int label;						// �湮 ����
} Enode;

// ��������Ʈ ���
typedef struct inode {
	struct enode* edge;				// ����
	struct inode* next;				// ��������Ʈ ���� ���
} Inode;

// ��������Ʈ ���
typedef struct vnode {
	int num;						// ���� ��ȣ
	struct inode* header;			// ��������Ʈ ��� ���
	int label;						// �湮 ����
} Vnode;

// ���� ����
Vnode** vlist;
Enode** elist;
int current_edge_index = 0;
int n, m, s;

// �Լ� ���
void init_vlist();
void init_elist();
void createEdgeToList();
Vnode* opposite(Enode* edge, int v);
void sortIncidenceList(int i);
void DFS(Vnode* u);
void freememory();

int main() {

	// n, m, s �Է�
	scanf("%d%d%d", &n, &m, &s);
	getchar();


	// ��������Ʈ �޸� �Ҵ�
	init_vlist();
	// ��������Ʈ �޸� �Ҵ�
	init_elist();

	// m���� ������ ��������Ʈ�� �߰�
	// m���� ������ ��������Ʈ�� �߰�
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
		vlist[i]->num = i + 1;								// ���� ��ȣ ����
		vlist[i]->label = 0;								// �湮���� ���� ����
		vlist[i]->header = (Inode*)malloc(sizeof(Inode));
		vlist[i]->header->next = NULL;						// ���� ��������Ʈ ���
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
	// ���� �Է�
	scanf("%d%d", &v1, &v2);
	getchar();


	// ���� ����
	Enode* newEnode = (Enode*)malloc(sizeof(Enode));
	newEnode->v1 = vlist[v1-1];
	newEnode->v2 = vlist[v2-1];
	newEnode->label = 0;

	// ��������Ʈ�� ���� �߰�
	elist[current_edge_index++] = newEnode;

	// v1, v2 ���� ��������Ʈ�� ���� �߰�
	Inode* p = vlist[v1 - 1]->header->next;				// v1 ��������Ʈ ��� ���
	
	Inode* newInode1 = (Inode*)malloc(sizeof(Inode));	// ��������Ʈ ��� ����
	newInode1->edge = newEnode;
	newInode1->next = p;

	vlist[v1 - 1]->header->next = newInode1;

	p = vlist[v2 - 1]->header->next;				// v1 ��������Ʈ ��� ���

	Inode* newInode2 = (Inode*)malloc(sizeof(Inode));	// ��������Ʈ ��� ����
	newInode2->edge = newEnode;
	newInode2->next = p;

	vlist[v2 - 1]->header->next = newInode2;
	


	for (int i = 0; i < n; i++) {
		sortIncidenceList(i);
	}
	
}

// ���� ���� ���� ��ȯ
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
	int v = vlist[i]->num;				// ���� ��ȣ
	Vnode* currentInode_opposite = NULL;
	Vnode* nextInode_opposite = NULL;

	// ���� i�� ��������Ʈ ù ��� p�� ����
	Inode* p = vlist[i]->header->next;
	while (p != NULL) {
		// p ��尡 ��������Ʈ ������ ��� ���� �� ����
		if (p->next == NULL) {
			break;
		}
		// p ����� ���� ��带 p1���� ����
		Inode* p1 = p->next;


		// ���� �������� ����
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
	// ��������Ʈ, ��������Ʈ �޸� ����
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