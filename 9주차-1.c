#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

// �ؽ����̺� ���� ���
typedef struct node {
	int key;
	struct node* next;
} Node;

// ��������
int M;
Node** hashtable;

// �Լ� ���
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
	// �ؽ����̺� ����


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
	// �ؽ����̺� �޸� ����

	return 0;
}

// �ؽ����̺� ���� �� �ʱ�ȭ
void initHashtable() {
	
	hashtable = (Node**)malloc(sizeof(Node*) * M);

	for (int i = 0; i < M; i++) {
		hashtable[i] = (Node*)malloc(sizeof(Node));
		hashtable[i]->key = 0;
		hashtable[i]->next = NULL;
	}

	return;
}


// key ���� �Լ�
void insertKey(int x) {
	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->key = x;
	newnode->next = hashtable[hashFunction(x)]->next;
	hashtable[hashFunction(x)]->next = newnode;
}


// key Ž�� �Լ�
int searchKey(int x) {
	Node* p = hashtable[hashFunction(x)];
	int rank = 0;
	while (p != NULL) {
		// �ؽ����̺� key�� �����ϸ� ���� ��ġ ��ȯ
		if (p->key == x) return rank;
		p = p->next;
		rank++;
	}

	// �ؽ����̺� key�� �������� ������ 0 ��ȯ
	return 0;
}

// key ���� �Լ�
int deleteKey(int x) {
	// �ؽ����̺� key�� �������� ������ 0 ��ȯ
	if (searchKey(x) == 0) return 0;

	int n = searchKey(x);

	Node* p = hashtable[hashFunction(x)];
	for (int i = 0; i < searchKey(x)-1; i++) {
		p = p->next;
	}
	Node* tmp = p->next;
	p->next = tmp->next;
	
	// key ��� ����
	free(tmp);

	// key ��ġ ��ȯ
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


// �ؽ� �Լ�
int hashFunction(int x) {
	return x % M;
}


// �ؽ����̺� �޸� ���� �Լ�
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