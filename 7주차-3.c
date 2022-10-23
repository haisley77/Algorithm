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
// Ʈ���� �����ϴ� ���

Node* tree;
// AVL Ʈ��


/**********����Ž��Ʈ�� ���� �Լ���****************/
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


/**************AVLƮ�� ���� �߰� �Լ���*************/
void searchAndFixAfterInsertion(Node*);
int updateHeight(Node*);
int isBalanced(Node*);
Node* restructure(Node*, Node*, Node*);
int isRoot(Node*);
int height(Node*);
int MAX(int, int);
void freememory(Node*);
/***************************************************/

/***************AVLƮ�� ���� ���� �Լ�**************/
void searchAndFixAfterRemoval(Node*);
/***************************************************/



void main() {

	tree = (Node*)malloc(sizeof(Node));
	tree->parent = NULL;
	tree->height = 0;
	tree->lChild = NULL;
	tree->rChild = NULL;
	// AVLƮ�� �����Ҵ� �� �ܺγ��� �ʱ�ȭ

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
			// Ű ���� k�� ��尡 ���� �� X ���
			else printf("%d\n", tmp);
			// Ű ���� K�� ��尡 ���� �� �ش� Ű �� ���
		}
		else if (input == 'p') {
			prePrint(tree);
			printf("\n");
			// Ʈ�� ������ȸ ���
		}
	}

	freememory(tree);
	// AVLƮ�� �޸� ����

	return;
}


int findElement(int k) {
	Node* p = treeSearch(k);
	if (isExternal(p)) return 0;
	return p->key;
}
// Ű ���� k�� ��带 AVLƮ������ Ž���� �� �ش� Ű �� ��ȯ �Լ�


void insertItem(int k) {

	Node* p = treeSearch(k);
	// Ű ���� k�� ��带 ������ �ܺγ�� ��ġ Ž��
	Node* tmp = p;

	if (isExternal(p)) {
		p->key = k;
		p->height = 1;
		expandExternal(p);
		// ���� �� �ܺγ�� Ȯ��


		searchAndFixAfterInsertion(p);
		// AVLƮ�� ����
	}

	return;
}
// Ű ���� k�� ��� ���� �Լ�

int removeElement(int k) {
	Node* w = treeSearch(k);
	int e;

	if (isExternal(w)) return 0;
	// Ű ���� k�� �ش��ϴ� ��尡 Ʈ���� ���� ���

	else {
		e = w->key;

		Node* z = w->lChild;
		if (!isExternal(z)) z = w->rChild;

		Node* zs;
		if (isExternal(z)) {
			zs = reduceExternal(z);
			// ������ ��� ��ġ�� �����ϴ� ��带 zs�� ����
		}
		else {
			Node* y = inOrderSucc(w);

			z = y->lChild;
			w->key = y->key;
			zs = reduceExternal(z);
			// ������ ��� ��ġ�� �����ϴ� ��带 zs�� ����
		}
		
		searchAndFixAfterRemoval(zs->parent);
		// �ұ��� ��带 ã�� �����۾�

		return e;
	}

}
// Ű ���� k�� ��� ���� �� �ش� Ű ��ȯ �Լ�


Node* treeSearch(int k) {
	Node* w = tree;
	w = find(w, k);
	return w;
}
// Ű ���� k�� ��� Ž�� �� ��ȯ �Լ�

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}
// �ܺγ�� �Ǻ� �Լ�

int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}
// ���γ�� �Ǻ� �Լ�

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	// ������ �ڽ� ���� �̵�
	if (isExternal(w)) return w;
	// ������ �ڽ� ��尡 �ܺγ���̸� �İ��� ����

	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	// ������ȸ �İ��� Ž��

	return w;
}
// ������ȸ �İ��� ��� ��ȯ �Լ�

Node* find(Node* w, int k) {
	if (isExternal(w)) return w;
	// Ű ���� k�� ��尡 AVLƮ���� ���� ��� (���̽� ���̽�)

	if (k == w->key) return w;
	else if (k < w->key) return find(w->lChild, k);
	else return find(w->rChild, k);
	// ����� Ž��
}
// Ű ���� k�� ��� Ž�� �� ��ȯ �Լ�

void prePrint(Node* p) {

	if (isExternal(p)) return;

	printf(" %d", p->key);
	prePrint(p->lChild);
	prePrint(p->rChild);
}
// Ʈ�� ������ȸ ��� �Լ�

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
// �ܺγ�� Ȯ�� �Լ�

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
	// �ұ��� ��� z

	if (height(z->lChild) > height(z->rChild)) y = z->lChild;
	else y = z->rChild;
	// z�� �ڽ� �� ���� �ڽ�: y

	if (height(y->lChild) > height(y->rChild)) x = y->lChild;
	else x = y->rChild;
	// y�� �ڽ� �� ���� �ڽ�: x

	restructure(x, y, z);
	// ����

	return;

}


int updateHeight(Node* w) {
	int h = MAX(height(w->rChild), height(w->lChild)) + 1;

	if (w->height == h) return 0;
	// ���� ����X

	w->height = h;
	return 1;
	// ���� ����O
}

int isBalanced(Node* w) {
	if (isExternal(w)) return 1;

	int diff = height(w->lChild) - height(w->rChild);
	return ((diff >= -1) && (diff <= 1));
}
// ���� �ұ��� ���� �Լ�


Node* restructure(Node* x, Node* y, Node* z) {

	Node* a, * b, * c;
	// �湮 ����
	Node* T0, * T1, * T2, * T3;
	// ��Ʈ�� ������ȸ ����

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
	}	// ���� �ұ��� ��尡 ��Ʈ ����� ��
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}	// ���� �ұ��� ��尡 lChild �� ��
	else if (z->parent->rChild == z) {
		z->parent->rChild = b;
		b->parent = z->parent;
	}	// ���� �ұ��� ��尡 rChild �� ��

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

	// ���� �� ���� ������Ʈ

	return b;
}

int isRoot(Node* w) {
	if (w->parent == NULL) return 1;
	return 0;
}
// ��Ʈ ���� ��ȯ �Լ�

int height(Node* w) {
	return w->height;
}
// ���� ��ȯ �Լ�

int MAX(int a, int b) {
	if (a > b)return a;
	return b;
}
// �ִ� ��ȯ �Լ�

void freememory(Node* w) {
	if (isExternal(w)) return;

	freememory(w->lChild);
	freememory(w->rChild);
	free(w);
	return;
}
// �޸� ����





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
	// ��� ��尡 �������� ��� �״�� ����


	z = p;
	// �ұ��� ��� z ����

	if (z->lChild->height > z->rChild->height) y = z->lChild;
	else y = z->rChild;
	// z�� ���� �ڽ�: y

	if (y->lChild->height > y->rChild->height) x = y->lChild;
	else if (y->lChild->height < y->rChild->height) x = y->rChild;
	// y�� �ڽ� ���̰� �ٸ� ���
	else {
		if (z->lChild == y) x = y->lChild;
		else x = y->rChild;
	}
	// y�� �ڽ� ���̰� ���� ���



	p = restructure(x, y, z);
	// ������ ��Ʈ���� ��Ʈ��带 p�� ����
	searchAndFixAfterRemoval(p->parent);
	// p�� �θ�, ���� �� �ұ����� �ʷ��� ��� �ݺ� ����
}