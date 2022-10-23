#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#pragma warning(disable:4996)

typedef struct node {
	struct node* prev;
	char elem;
	struct node* next;
} Node;

typedef struct list {
	Node* header;
	Node* trailer;
	int size;
} List;


void add(List* L, int r, char c) {
	Node* tmp;
	tmp = L->header;

	for (int i = 0; i < r; i++) {
		tmp = tmp->next;
	}

	Node* new = (Node*)malloc(sizeof(Node));
	new->elem = c;

	new->next = tmp;
	new->prev = tmp->prev;
	tmp->prev->next = new;
	tmp->prev = tmp;

	L->size++;

	return;
}

void delete(List* L, int r) {
	Node* tmp;
	tmp = L->header;
	for (int i = 0; i < r; i++) {
		tmp = tmp->next;
	}

	tmp->prev->next = tmp->next;
	tmp->next->prev = tmp->prev;

	free(tmp);

	L->size--;
	return;
}

char get(List* L, int r) {
	Node* tmp;
	tmp = L->header;
	for (int i = 0; i < r; i++) {
		tmp = tmp->next;
	}

	return tmp->elem;
}

void print(List* L) {
	Node* tmp;
	tmp = L->header->next;
	while (tmp != L->trailer) {
		printf("%c", tmp->elem);
		tmp = tmp->next;
	}
	printf("\n");
	return;
}


int main() {
	int n, r;
	char sys, c;
	Node* h = (Node*)malloc(sizeof(Node));
	Node* t = (Node*)malloc(sizeof(Node));
	List* L = (List*)malloc(sizeof(List));
	L->header = h;
	L->trailer = t;

	h->prev = NULL;
	t->next = NULL;
	h->next = t;
	t->prev = h;

	
	L->size = 0;

	// 리스트 선언 및 초기화


	scanf("%d", &n);
	getchar();

	for (int i = 0; i < n; i++) {
		scanf("%c", &sys);
		getchar();

		if (sys == 'A') {
			scanf("%d %c", &r, &c);
			getchar();
			if (r > (L->size + 1)) {
				printf("invalid position\n");
			}
			//add operation
			else {
				add(L, r, c);
			}
		}
		else if (sys == 'D') {
			scanf("%d", &r);
			getchar();
			if (r > L->size) {
				printf("invalid position\n");
			}
			//deletion operation
			else {
				delete(L, r);
			}
		}
		else if (sys == 'G') {
			scanf("%d", &r);
			getchar();
			if (r > L->size) {
				printf("invalid position\n");
			}
			//get operation
			else {
				printf("%c\n", get(L, r));
			}
			

		}
		else if (sys == 'P') {
			//print operation
			print(L);
		}
	}
	return 0;
}
