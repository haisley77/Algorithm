
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

Node* tree;

int findElement(int);
void insertItem(int);
Node* treeSearch(int);
int isExternal(Node*);
int isInternal(Node*);
Node* inOrderSucc(Node*);
Node* find(Node* w, int k);
void prePrint(Node* p);
Node* sibling(Node*);
Node* reduceExternal(Node*);
void expandExternal(Node*);

void searchAndFixAfterInsertion(Node*);
int updateHeight(Node*);
int isBalanced(Node*);
Node* restructure(Node*, Node*, Node*);
int height(Node*);
int MAX(int, int);
void rotate(Node*,Node*,Node*, Node*, Node*, Node*, Node*,Node*);



void main() {

	tree = (Node*)malloc(sizeof(Node));
	tree->parent = NULL;
	tree->height = 0;
	tree->lChild = NULL;
	tree->rChild = NULL;

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
		else if (input == 's') {
			scanf("%d", &k);
			getchar();
			tmp = findElement(k);
			if (tmp == 0) printf("X\n");
			else printf("%d\n", tmp);
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

void insertItem(int k) {

	Node* p = treeSearch(k);

	if (isExternal(p)) {
		p->key = k;
		expandExternal(p);

		Node* tmp = p;
		while (tmp->parent != NULL) {
			updateHeight(tmp);
			tmp = tmp->parent;
		}
		

	
		searchAndFixAfterInsertion(p);

		prePrint(tree);
		printf("\n");
	}

	return;
}

Node* treeSearch(int k) {
	Node* w = tree;
	w = find(w, k);
	return w;
}

int isExternal(Node* w) {
	if (w->lChild == NULL && w->rChild == NULL) return 1;
	else return 0;
}

int isInternal(Node* w) {
	if (w->lChild != NULL || w->rChild != NULL) return 1;
	else return 0;
}

Node* inOrderSucc(Node* w) {
	w = w->rChild;
	if (isExternal(w)) return w;
	while (isInternal(w->lChild)) {
		w = w->lChild;
	}
	return w;
}

Node* find(Node* w, int k) {
	if (isExternal(w)) return w;
	if (k == w->key) return w;
	else if (k < w->key) return find(w->lChild, k);
	else return find(w->rChild, k);
}

void prePrint(Node* p) {


	if (isExternal(p)) return;

	printf(" %d", p->key);
	prePrint(p->lChild);
	prePrint(p->rChild);


}

Node* sibling(Node* w) {
	if (w->parent == NULL) return NULL;
	if (w->parent->lChild == w) return w->parent->rChild;
	else return w->parent->lChild;
}

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

	return;
}



void searchAndFixAfterInsertion(Node* w) {
	Node* z;
	Node* y;
	Node* x;
	Node* p = w;

	while (p != NULL && isBalanced(p)) {
		p = p->parent;
	}

	if (p==NULL) return;
	// 불균형 노드 없는 경우 리턴
	
	z = p;

	if (height(z->lChild) > height(z->rChild)) y = z->lChild;
	else y = z->rChild;

	if (height(y->lChild) > height(y->rChild)) x = y->lChild;
	else x = y->rChild;

	restructure(x, y, z);

	
	return;

}


int updateHeight(Node* w) {
	
	if (isExternal(w)) return 0;
	else {
		w->height = MAX(height(w->rChild), height(w->lChild)) + 1;
		return 1;
	}
	
}


int isBalanced(Node* w) {
	int a, b, diff;
	a = w->lChild->height;
	b = w->rChild->height;
	if (a > b) diff = a - b;
	else diff = b - a;

	if (diff > 1) return 0;
	else return 1;
}


Node* restructure(Node* x, Node* y, Node* z) {




	if (z->lChild == y && y->lChild == x) {
		Node* a = x;
		Node* b = y;
		Node* c = z;

		Node* T0 = x->lChild;
		Node* T1 = x->rChild;
		Node* T2 = y->rChild;
		Node* T3 = z->rChild;

		rotate(a, b, c, z, T0, T1, T2, T3);

		updateHeight(a);
		updateHeight(b);
		updateHeight(c);

		return b;
	}
	else if (z->rChild == y && z->rChild == x) {
		Node* a = z;
		Node* b = y;
		Node* c = x;

		Node* T0 = z->lChild;
		Node* T1 = y->lChild;
		Node* T2 = x->lChild;
		Node* T3 = x->rChild;

		rotate(a, b, c, z, T0, T1, T2, T3);

		updateHeight(a);
		updateHeight(b);
		updateHeight(c);

		return b;
	}
	else if (z->lChild == y && y->rChild == x) {
		Node* a = y;
		Node* b = x;
		Node* c = z;

		Node* T0 = y->lChild;
		Node* T1 = x->lChild;
		Node* T2 = x->rChild;
		Node* T3 = z->rChild;

		rotate(a, b, c, z, T0, T1, T2, T3);

		updateHeight(a);
		updateHeight(b);
		updateHeight(c);

		return b;
	}
	else if (z->rChild == y && y->lChild == x) {
		Node* a = z;
		Node* b = x;
		Node* c = y;

		Node* T0 = z->lChild;
		Node* T1 = x->lChild;
		Node* T2 = x->rChild;
		Node* T3 = y->rChild;

		rotate(a, b, c, z, T0, T1, T2, T3);

		updateHeight(a);
		updateHeight(b);
		updateHeight(c);

		return b;
	}
	else return NULL;


}


int height(Node* w) {
	if (isExternal(w)) return 0;
	else return w->height;
}


int MAX(int a, int b) {
	if (a > b)return a;
	return b;
}

void rotate(Node* a, Node* b, Node* c, Node*z, Node*T0, Node*T1, Node*T2,Node*T3) {

	b->parent = z->parent;
	if (z->parent != NULL) {
		if (z->parent->lChild == z) z->parent->lChild = b;
		else z->parent->rChild = b;
	}

	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;

	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;

	b->lChild = a;
	a->parent = b;
	b->rChild = c;
	c->parent = b;
}
