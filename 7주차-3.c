#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int height;
	int key;
} Node;
// 트리를 구성하는 노드

Node* tree;
// AVL 트리


/**********이진탐색트리 구현 함수들****************/
int findElement(int);
void insertItem(int);
int removeElement(int);
Node* treeSearch(int);
int isExternal(Node*);
int isInternal(Node*);
Node* inOrderSucc(Node*);
Node* find(Node* w, int k);
void prePrint(Node* p);
Node* sibling(Node*);
Node* reduceExternal(Node*);
void expandExternal(Node*);
/***************************************************/


/**************AVL트리 구현 추가 함수들*************/
void searchAndFixAfterInsertion(Node*);
int updateHeight(Node*);
int isBalanced(Node*);
Node* restructure(Node*, Node*, Node*);
int isRoot(Node*);
int height(Node*);
int MAX(int, int);
void freememory(Node*);
/***************************************************/

/***************AVL트리 삭제 구현 함수**************/
void searchAndFixAfterRemoval(Node*);
/***************************************************/



void main() {

	tree = (Node*)malloc(sizeof(Node));
	tree->parent = NULL;
	tree->height = 0;
	tree->lChild = NULL;
	tree->rChild = NULL;
	// AVL트리 동적할당 및 외부노드로 초기화

	char input;
	int k, tmp;

	while (1) {
		scanf("%c", &input);
		getchar();

		if (input == 'q') {
			break;
		}
		else if (input == 'i') {
			scanf("%d", &k);
			getchar();
			insertItem(k);
		}
		else if (input == 'd') {
			scanf("%d", &k);
			getchar();
			if (isExternal(treeSearch(k))) printf("X\n");
			else printf("%d\n", removeElement(k));
		}
		else if (input == 's') {
			scanf("%d", &k);
			getchar();
			tmp = findElement(k);
			if (tmp == 0) printf("X\n");
			// 키 값이 k인 노드가 없을 때 X 출력
			else printf("%d\n", tmp);
			// 키 값이 K인 노드가 있을 때 해당 키 값 출력
		}
		else if (input == 'p') {
			prePrint(tree);
			printf("\n");
			// 트리 전위순회 출력
		}
	}

	freememory(tree);
	// AVL트리 메모리 해제

	return;
}


int findElement(int k) {
	Node* p = treeSearch(k);
	if (isExternal(p)) return 0;
	return p->key;
}
// 키 값이 k인 노드를 AVL트리에서 탐색한 후 해당 키 값 반환 함수


void insertItem(int k) {

	Node* p = treeSearch(k);
	// 키 값이 k인 노드를 삽입할 외부노드 위치 탐색
	Node* tmp = p;

	if (isExternal(p)) {
		p->key = k;
		p->height = 1;
		expandExternal(p);
		// 삽입 및 외부노드 확장


		searchAndFixAfterInsertion(p);
		// AVL트리 개조
	}

	return;
}
// 키 값이 k인 노드 삽입 함수

int removeElement(int k) {
	Node* w = treeSearch(k);
	int e;

	if (isExternal(w)) return 0;
	// 키 값이 k에 해당하는 노드가 트리에 없는 경우

	else {
		e = w->key;

		Node* z = w->lChild;
		if (!isExternal(z)) z = w->rChild;

		Node* zs;
		if (isExternal(z)) {
			zs = reduceExternal(z);
			// 삭제한 노드 위치에 존재하는 노드를 zs로 받음
		}
		else {
			Node* y = inOrderSucc(w);

			z = y->lChild;
			w->key = y->key;
			zs = reduceExternal(z);
			// 삭제한 노드 위치에 존재하는 노드를 zs로 받음
		}
		
		searchAndFixAfterRemoval(zs->parent);
		// 불균형 노드를 찾아 개조작업

		return e;
	}

}
// 키 값이 k인 노드 삭제 및 해당 키 반환 함수


Node* treeSearch(int k) {
	Node* w = tree;
	w = find(w, k);
	return w;
}
// 키 값이 k인 노드 탐색 및 반환 함수

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}
// 외부노드 판별 함수

int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}
// 내부노드 판별 함수

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	// 오른쪽 자식 노드로 이동
	if (isExternal(w)) return w;
	// 오른쪽 자식 노드가 외부노드이면 후계자 없음

	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	// 중위순회 후계자 탐색

	return w;
}
// 중위순회 후계자 노드 반환 함수

Node* find(Node* w, int k) {
	if (isExternal(w)) return w;
	// 키 값이 k인 노드가 AVL트리에 없는 경우 (베이스 케이스)

	if (k == w->key) return w;
	else if (k < w->key) return find(w->lChild, k);
	else return find(w->rChild, k);
	// 재귀적 탐색
}
// 키 값이 k인 노드 탐색 및 반환 함수

void prePrint(Node* p) {

	if (isExternal(p)) return;

	printf(" %d", p->key);
	prePrint(p->lChild);
	prePrint(p->rChild);
}
// 트리 전위순회 출력 함수

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;
	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}
// 형제 노드 반환 함수

Node* reduceExternal(Node* z) {
	Node* y = z->parent;
	Node* zs = sibling(z);
	if (y->parent == NULL) {
		tree = zs;
		zs->parent = NULL;
	}
	else {
		Node* p = y->parent;
		zs->parent = p;
		if (p->lChild == y) {
			p->lChild = zs;
		}
		else {
			p->rChild = zs;
		}
	}

	free(z);
	free(y);

	return zs;
}


void expandExternal(Node* w) {
	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));

	left->parent = w;
	left->lChild = NULL;
	left->rChild = NULL;
	left->height = 0;

	right->parent = w;
	right->lChild = NULL;
	right->rChild = NULL;
	right->height = 0;

	w->lChild = left;
	w->rChild = right;
	w->height = 1;
}
// 외부노드 확장 함수

void searchAndFixAfterInsertion(Node* w) {
	Node* z;
	Node* y;
	Node* x;
	Node* p = w;

	if (w->parent == NULL) return;
	
	p = w->parent;
	while (updateHeight(p) && isBalanced(p)) {
		if (p->parent == NULL) return;
		p = p->parent;
	}
	if (isBalanced(p)) return;
	z = p;
	// 불균형 노드 z

	if (height(z->lChild) > height(z->rChild)) y = z->lChild;
	else y = z->rChild;
	// z의 자식 중 높은 자식: y

	if (height(y->lChild) > height(y->rChild)) x = y->lChild;
	else x = y->rChild;
	// y의 자식 중 높은 자식: x

	restructure(x, y, z);
	// 개조

	return;

}


int updateHeight(Node* w) {
	int h = MAX(height(w->rChild), height(w->lChild)) + 1;

	if (w->height == h) return 0;
	// 높이 수정X

	w->height = h;
	return 1;
	// 높이 수정O
}

int isBalanced(Node* w) {
	if (isExternal(w)) return 1;

	int diff = height(w->lChild) - height(w->rChild);
	return ((diff >= -1) && (diff <= 1));
}
// 높이 불균형 측정 함수


Node* restructure(Node* x, Node* y, Node* z) {

	Node* a, * b, * c;
	// 방문 순서
	Node* T0, * T1, * T2, * T3;
	// 부트리 중위순회 순서

	if (z->lChild == y && y->lChild == x) {

		a = x;
		b = y;
		c = z;

		T0 = a->lChild;
		T1 = a->rChild;
		T2 = b->rChild;
		T3 = c->rChild;

	}
	// x->y->z

	else if (z->rChild == y && y->rChild == x) {
		a = z;
		b = y;
		c = x;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = c->lChild;
		T3 = c->rChild;

	}
	// z->y->x

	else if (z->rChild == y && y->lChild == x) {

		a = z;
		b = x;
		c = y;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	// z->x->y

	else {
		a = y;
		b = x;
		c = z;

		T0 = a->lChild;
		T1 = b->lChild;
		T2 = b->rChild;
		T3 = c->rChild;
	}
	// y->x->z


	if (isRoot(z)) {
		tree = b;
		b->parent = NULL;
	}	// 최초 불균형 노드가 루트 노드일 때
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}	// 최초 불균형 노드가 lChild 일 때
	else if (z->parent->rChild == z) {
		z->parent->rChild = b;
		b->parent = z->parent;
	}	// 최초 불균형 노드가 rChild 일 때

	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);

	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
	updateHeight(b);

	// 개조 및 높이 업데이트

	return b;
}

int isRoot(Node* w) {
	if (w->parent == NULL) return 1;
	return 0;
}
// 루트 여부 반환 함수

int height(Node* w) {
	return w->height;
}
// 높이 반환 함수

int MAX(int a, int b) {
	if (a > b)return a;
	return b;
}
// 최댓값 반환 함수

void freememory(Node* w) {
	if (isExternal(w)) return;

	freememory(w->lChild);
	freememory(w->rChild);
	free(w);
	return;
}
// 메모리 해제





void searchAndFixAfterRemoval(Node* w) {
	Node* z;
	Node* y;
	Node* x;
	Node* p = w;

	if (w==NULL) return;

	while (updateHeight(p) && isBalanced(p)) {
		if (isRoot(p)) return;
		p = p->parent;
	}

	if (isBalanced(p)) return;
	// 모든 노드가 균형적인 경우 그대로 리턴


	z = p;
	// 불균형 노드 z 설정

	if (z->lChild->height > z->rChild->height) y = z->lChild;
	else y = z->rChild;
	// z의 높은 자식: y

	if (y->lChild->height > y->rChild->height) x = y->lChild;
	else if (y->lChild->height < y->rChild->height) x = y->rChild;
	// y의 자식 높이가 다른 경우
	else {
		if (z->lChild == y) x = y->lChild;
		else x = y->rChild;
	}
	// y의 자식 높이가 같은 경우



	p = restructure(x, y, z);
	// 개조한 부트리의 루트노드를 p로 받음
	searchAndFixAfterRemoval(p->parent);
	// p의 부모, 조상 중 불균형이 초래된 노드 반복 개조
}