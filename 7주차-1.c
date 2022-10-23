#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
} Node;
// 트리 노드

Node* tree;
// 이진탐색트리

/*******************구현함수*******************/
int findElement(int);
void insertItem(int);
Node* treeSearch(int);
int removeElement(int);
int isExternal(Node*);
int isInternal(Node*);
Node* inOrderSucc(Node*);
Node* find(Node* w, int k);
void prePrint(Node* p);
Node* sibling(Node*);
Node* reduceExternal(Node*);
void expandExternal(Node*);
void freememory(Node*);
/**********************************************/


void main() {

	tree = (Node*)malloc(sizeof(Node));
	tree->parent = NULL;
	tree->lChild = NULL;
	tree->rChild = NULL;
	// 트리 할당 및 외부노드화

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
			// 키 값이 k인 노드가 트리에 없으면 X 출력
			// 키 값이 k인 노드가 트리에 있으면 삭제한 노드 키 값 출력
		}
		else if (input == 's') {
			scanf("%d", &k);
			getchar();
			tmp = findElement(k);
			if (tmp == 0) printf("X\n");
			else printf("%d\n", tmp);
			// 키 값이 k인 노드가 트리에 없으면 X 출력
			// 키 값이 k인 노드가 트리에 있으면 해당 노드 키 값 출력
		}
		else if (input == 'p') {
			prePrint(tree);
			printf("\n");
		}
	}

	free(tree);

	return;
}


int findElement(int k) {
	Node* p = treeSearch(k);
	if (isExternal(p)) return 0;
	return p->key;
}
// 키 값이 k인 노드를 탐색하여 해당 노드의 키 값을 반환하는 함수


void insertItem(int k) {
	Node* p = treeSearch(k);
	if (isExternal(p)) {
		p->key = k;
		expandExternal(p);
	}
	return;
}
// 삽입 함수


Node* treeSearch(int k) {
	Node* w = tree;
	w = find(w, k);
	return w;
}
// 키 값이 k인 노드를 트리에서 탐색&반환하는 함수

int removeElement(int k) {
	Node* w = treeSearch(k);
	int e;

	if (isExternal(w)) return 0;
	else {
		e = w->key;

		Node* z = w->lChild;
		if (!isExternal(z)) z = w->rChild;

		if (isExternal(z)) {
			reduceExternal(z);
			// 외부노드&부모삭제
		}
		else {
			Node* y = inOrderSucc(w);
			// 중위순회 후계자 y
			z = y->lChild;
			w->key = y->key;
			reduceExternal(z);
			// 외부노드&부모노드삭제
		}

		return e;
	}
}
// 삭제 함수

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}
// 외부 노드 판별 함수
int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}
// 내부 노드 판별 함수

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	if (isExternal(w)) return w;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}
// 중위순회 후계자 반환 함수

Node* find(Node* w, int k) {
	if (isExternal(w)) return w;
	if (k == w->key) return w;
	// 키 값이 k이면 해당 노드 즉시 반환
	else if (k < w->key) return find(w->lChild, k);
	else return find(w->rChild, k);
}
// 키 값이 k인 노드를 트리에서 탐색하여 반환하는 함수

void prePrint(Node* p) {
	if (isExternal(p)) return;
	printf(" %d", p->key);
	prePrint(p->lChild);
	prePrint(p->rChild);
}
// 전위순회 순서 트리 출력함수

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
// reduceExternal

void expandExternal(Node* w) {
	Node* left = (Node*)malloc(sizeof(Node));
	Node* right = (Node*)malloc(sizeof(Node));

	left->parent = w;
	left->lChild = NULL;
	left->rChild = NULL;

	right->parent = w;
	right->lChild = NULL;
	right->rChild = NULL;

	w->lChild = left;
	w->rChild = right;
}
// 외부노드 확장 함수

void freememory(Node* w) {
	if (isExternal(w)) return;
	freememory(w->lChild);
	freememory(w->rChild);
	free(w);
	return;
}
// 트리 메모리 해제