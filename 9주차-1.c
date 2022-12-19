#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// 해시테이블 구성 노드
typedef struct node {
	int key;
	struct node* next;
} Node;

// 전역변수
int M;
Node** hashtable;

// 함수 목록
void initHashtable();
void insertKey(int x);
int searchKey(int x);
int deleteKey(int x);
void print();
int hashFunction(int x);
void freeMemory();


int main() {

	char type;
	int x;

	scanf("%d", &M);
	getchar();

	initHashtable();
	// 해시테이블 생성


	while (1) {
		scanf("%c", &type);
		getchar();

		if (type == 'i') {
			scanf("%d", &x);
			getchar();
			insertKey(x);
		}
		if (type == 's') {
			scanf("%d", &x);
			getchar();
			printf("%d\n",searchKey(x));
		}
		if (type == 'd') {
			scanf("%d", &x);
			getchar();
			printf("%d\n",deleteKey(x));
		}
		if (type == 'p') {
			print();
		}
		if (type == 'e') {
			break;
		}
	}

	freeMemory();
	// 해시테이블 메모리 해제

	return 0;
}

// 해시테이블 생성 및 초기화
void initHashtable() {
	
	hashtable = (Node**)malloc(sizeof(Node*) * M);

	for (int i = 0; i < M; i++) {
		hashtable[i] = (Node*)malloc(sizeof(Node));
		hashtable[i]->key = 0;
		hashtable[i]->next = NULL;
	}

	return;
}


// key 삽입 함수
void insertKey(int x) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = x;
	newnode->next = hashtable[hashFunction(x)]->next;
	hashtable[hashFunction(x)]->next = newnode;
}


// key 탐색 함수
int searchKey(int x) {
	Node* p = hashtable[hashFunction(x)];
	int rank = 0;
	while (p != NULL) {
		// 해시테이블에 key가 존재하면 저장 위치 반환
		if (p->key == x) return rank;
		p = p->next;
		rank++;
	}

	// 해시테이블에 key가 존재하지 않으면 0 반환
	return 0;
}

// key 삭제 함수
int deleteKey(int x) {
	// 해시테이블에 key가 존재하지 않으면 0 반환
	if (searchKey(x) == 0) return 0;

	int n = searchKey(x);

	Node* p = hashtable[hashFunction(x)];
	for (int i = 0; i < searchKey(x)-1; i++) {
		p = p->next;
	}
	Node* tmp = p->next;
	p->next = tmp->next;
	
	// key 노드 삭제
	free(tmp);

	// key 위치 반환
	return n;
}
void print() {
	Node* p;
	for (int i = 0; i < M; i++) {
		p = hashtable[i]->next;
		while (p != NULL) {
			printf(" %d", p->key);
			p = p->next;
		}
	}
	printf("\n");
}


// 해시 함수
int hashFunction(int x) {
	return x % M;
}


// 해시테이블 메모리 해제 함수
void freeMemory() {
	Node* p, * tmp;
	for (int i = 0; i < M; i++) {
		tmp = hashtable[i];
		p = tmp->next;
		if (p == NULL) free(tmp);
		else {
			while (p != NULL) {
				free(tmp);
				tmp = p;
				p = p->next;
			}
		}
		
	}
	free(hashtable);
}