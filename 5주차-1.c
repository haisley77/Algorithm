/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


typedef struct node {
	int elem;
	struct node* next;
} Node;
// ����Ʈ�� �����ϴ� ��� ����ü


typedef struct part {
	Node* L1;
	Node* L2;
} Part;
// ����Ʈ L1, L2�� ���ÿ� ��ȯ�ϱ� ���� ������ ����ü

Part partition(Node* L, int k) {

	Node* p = L;
	Node* L1, * L2;
	Part tmp;
	
	L1 = L;
	for (int i = 0; i < k-1; i++) {
		p = p->next;
	}
	L2 = p->next;
	p->next = NULL;
	// L1, L2 �и�

	tmp.L1 = L1;
	tmp.L2 = L2;

	return tmp;
}



Node* merge(Node** L1, Node** L2) {

	Node* p, * L;

	if ((*L1)->elem < (*L2)->elem) {
		L = *L1;
		(*L1) = (*L1)->next;
	}

	else {
		L = *L2;
		(*L2) = (*L2)->next;
	}
	// �պ� ����Ʈ L�� ����� ����

	p = L;
	while ((*L1) != NULL && (*L2) != NULL) {

		if ((*L1)->elem < (*L2)->elem) {
			p->next = *L1;
			(*L1) = (*L1)->next;
			p = p->next;
		}
		else {
			p->next = *L2;
			(*L2) = (*L2)->next;
			p = p->next;
		}
	}
	// �� ���� ���Ҹ� ���� ��带 ����Ʈ L�� ���ʷ� �߰�

	while ((*L1) != NULL) {
		p->next = (*L1);
		p = p->next;
		(*L1) = (*L1)->next;
	}

	while ((*L2) != NULL) {
		p->next = (*L2);
		p = p->next;
		(*L2) = (*L2)->next;
	}
	// ���Ұ� ���� ����Ʈ�� ��� ��带 ����Ʈ L�� ���ʷ� �߰�

	return L;
}

int size(Node* p) {

	int size = 0;
	while (p != NULL){
		size++;
		p = p->next;
	}
	return size;
}



void mergeSort(Node** L) {

	Node* L1, * L2;
	Part tmp;

	int n = size(*L);
	// ����Ʈ L�� ũ��

	if (n > 1) {

		tmp = partition(*L, n/2);
		L1 = tmp.L1;
		L2 = tmp.L2;
		// ����Ʈ L�� L1, L2�� ����

		mergeSort(&L1);
		mergeSort(&L2);
		// ����Ʈ L1, L2 �������� ����


		*L = merge(&L1, &L2);
		// ����Ʈ L1, L2 ��ġ��
	}

}



void addNode(Node** L, int e) {

	Node* newnode = (Node*)malloc(sizeof(Node));
	newnode->elem = e;
	newnode->next = NULL;

	if (*L == NULL) *L = newnode;
	else {
		struct node* p = *L;
		while (p->next != NULL) p = p->next;

		p->next = newnode;
	}
}
// ����Ʈ�� ��带 �߰��ϴ� �Լ�



void print(Node* L) {
	Node* p = L;
	while (p != NULL) {
		printf(" %d", p->elem);
		p = p->next;
	}
}



int main() {

	Node* L = NULL;
	// ����Ʈ ��� ����
	int n, e;


	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &e);
		addNode(&L, e);
	}
	// ����Ʈ L ���� �Է� & ����

	mergeSort(&L);
	// �պ�����

	print(L);
	// ����Ʈ L ���


	Node* p = L;
	while (p != NULL) {
		L = L->next;
		free(p);
		p = L;
	}
	// ����Ʈ L�� ��� ��� �޸� ����

	return 0;
}

*/