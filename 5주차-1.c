/*
#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


typedef struct node {
	int elem;
	struct node* next;
} Node;
// 리스트를 구성하는 노드 구조체


typedef struct part {
	Node* L1;
	Node* L2;
} Part;
// 리스트 L1, L2를 동시에 반환하기 위해 선언한 구조체

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
	// L1, L2 분리

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
	// 합병 리스트 L의 헤드노드 설정

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
	// 더 작은 원소를 가진 노드를 리스트 L에 차례로 추가

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
	// 원소가 남은 리스트의 모든 노드를 리스트 L에 차례로 추가

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
	// 리스트 L의 크기

	if (n > 1) {

		tmp = partition(*L, n/2);
		L1 = tmp.L1;
		L2 = tmp.L2;
		// 리스트 L을 L1, L2로 분할

		mergeSort(&L1);
		mergeSort(&L2);
		// 리스트 L1, L2 오름차순 정렬


		*L = merge(&L1, &L2);
		// 리스트 L1, L2 합치기
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
// 리스트에 노드를 추가하는 함수



void print(Node* L) {
	Node* p = L;
	while (p != NULL) {
		printf(" %d", p->elem);
		p = p->next;
	}
}



int main() {

	Node* L = NULL;
	// 리스트 헤드 선언
	int n, e;


	scanf("%d", &n);

	for (int i = 0; i < n; i++) {
		scanf("%d", &e);
		addNode(&L, e);
	}
	// 리스트 L 원소 입력 & 생성

	mergeSort(&L);
	// 합병정렬

	print(L);
	// 리스트 L 출력


	Node* p = L;
	while (p != NULL) {
		L = L->next;
		free(p);
		p = L;
	}
	// 리스트 L의 모든 노드 메모리 해제

	return 0;
}

*/