#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
} Node;
// Ʈ�� ���

Node* tree;
// ����Ž��Ʈ��

/*******************�����Լ�*******************/
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
	// Ʈ�� �Ҵ� �� �ܺγ��ȭ

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
			// Ű ���� k�� ��尡 Ʈ���� ������ X ���
			// Ű ���� k�� ��尡 Ʈ���� ������ ������ ��� Ű �� ���
		}
		else if (input == 's') {
			scanf("%d", &k);
			getchar();
			tmp = findElement(k);
			if (tmp == 0) printf("X\n");
			else printf("%d\n", tmp);
			// Ű ���� k�� ��尡 Ʈ���� ������ X ���
			// Ű ���� k�� ��尡 Ʈ���� ������ �ش� ��� Ű �� ���
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
// Ű ���� k�� ��带 Ž���Ͽ� �ش� ����� Ű ���� ��ȯ�ϴ� �Լ�


void insertItem(int k) {
	Node* p = treeSearch(k);
	if (isExternal(p)) {
		p->key = k;
		expandExternal(p);
	}
	return;
}
// ���� �Լ�


Node* treeSearch(int k) {
	Node* w = tree;
	w = find(w, k);
	return w;
}
// Ű ���� k�� ��带 Ʈ������ Ž��&��ȯ�ϴ� �Լ�

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
			// �ܺγ��&�θ����
		}
		else {
			Node* y = inOrderSucc(w);
			// ������ȸ �İ��� y
			z = y->lChild;
			w->key = y->key;
			reduceExternal(z);
			// �ܺγ��&�θ������
		}

		return e;
	}
}
// ���� �Լ�

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}
// �ܺ� ��� �Ǻ� �Լ�
int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}
// ���� ��� �Ǻ� �Լ�

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	if (isExternal(w)) return w;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}
// ������ȸ �İ��� ��ȯ �Լ�

Node* find(Node* w, int k) {
	if (isExternal(w)) return w;
	if (k == w->key) return w;
	// Ű ���� k�̸� �ش� ��� ��� ��ȯ
	else if (k < w->key) return find(w->lChild, k);
	else return find(w->rChild, k);
}
// Ű ���� k�� ��带 Ʈ������ Ž���Ͽ� ��ȯ�ϴ� �Լ�

void prePrint(Node* p) {
	if (isExternal(p)) return;
	printf(" %d", p->key);
	prePrint(p->lChild);
	prePrint(p->rChild);
}
// ������ȸ ���� Ʈ�� ����Լ�

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;
	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}
// ���� ��� ��ȯ �Լ�

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
// �ܺγ�� Ȯ�� �Լ�

void freememory(Node* w) {
	if (isExternal(w)) return;
	freememory(w->lChild);
	freememory(w->rChild);
	free(w);
	return;
}
// Ʈ�� �޸� ����