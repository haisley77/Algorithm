#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* left;
	int id;
	struct node* right;
} Node;

Node* find_id(Node* root, int id) {
	if (root == NULL) return NULL;
	if (root->id == id) return root;

	Node* tmp = root;
	tmp = find_id(tmp->left, id);
	if (tmp) return tmp;
	else return find_id(root->right, id);
}

void insert(Node* root, int y, int z) {
	if (y == 0) {
		root->left = NULL;
	}
	else {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->id = y;
		newnode->left = NULL;
		newnode->right = NULL;
		
		root->left = newnode;
	}
	if (z == 0) {
		root->right = NULL;
	}
	else {
		Node* newnode = (Node*)malloc(sizeof(Node));
		newnode->id = z;
		newnode->left = NULL;
		newnode->right = NULL;

		root->right = newnode;
	}
}

void print(Node* root, char ch[]) {
	printf(" %d", root->id);

	for (int i = 0; i < strlen(ch); i++) {
		if (ch[i] == 'R') {
			root = root->right;
			printf(" %d", root->id);
		}
		if (ch[i] == 'L') {
			root = root->left;
			printf(" %d", root->id);
		}
	}
	printf("\n");
	return;
}

int main() {

	int n, s;
	char ch[101];
	scanf("%d", &n);
	getchar();

	Node* root = (Node*)malloc(sizeof(Node));
	Node* p = root;

	int x, y, z;
	

	for (int i = 0; i < n; i++) {
		scanf("%d %d %d", &x, &y, &z);
		getchar();
		if (i == 0) {
			root->id = x;
			insert(root, y, z);
		}
		else {
			p = find_id(p, x);
			if (p == NULL) {
				p = root;
				p = find_id(p, x);
			}

			insert(p, y, z);
		}

	}



	scanf("%d", &s);
	getchar();
	

	for (int i = 0; i < s; i++) {
		scanf("%s", ch);
		getchar();

		p = root;
		print(p, ch);
	}

	return 0;
}