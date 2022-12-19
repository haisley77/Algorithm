#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n, q, M;
int* hashtable;

// 필요 함수 목록
void initHashtable();
int insertKey(int x);
int searchKey(int x);
void print();
int hashFunction1(int x);
int hashFunction2(int x);
void freeMemory();

int main() {
	char type;
	int x;
	int insertnum = 0;
	scanf("%d %d %d", &M, &n, &q);
	getchar();


	initHashtable();

	while (1) {
		scanf("%c", &type);
		getchar();

		if (type == 'i') {
			// 최대 입력 횟수 초과 시 삽입 X
			if (insertnum == n) continue;

			scanf("%d", &x);
			getchar();
			printf("%d\n", insertKey(x));
			// 삽입 횟수 카운트
			insertnum++;
		}
		if (type == 's') {
			scanf("%d", &x);
			getchar();
			
			if (searchKey(x) == -1) printf("%d\n", searchKey(x));
			else printf("%d %d\n", searchKey(x), hashtable[searchKey(x)]);

		}
		if (type == 'p') {
			print();
		}
		if (type == 'e') {
			print();
			break;
		}
	}

	freeMemory();

	return 0;
}



// 해시테이블 생성 및 초기화
void initHashtable() {
	hashtable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) {
		hashtable[i] = 0;
	}
}

// key 삽입 함수
int insertKey(int x) {
	int i = hashFunction1(x);
	int k = 0;
	int count = 0;


	while (k<M) {
		// 이중 해싱을 이용한 인덱스 저장
		i = (hashFunction1(x) + hashFunction2(x) * k % M) % M;

		// key 삽입 가능 시 key 삽입 & 충돌 횟수만큼 C 출력
		if (hashtable[i] == 0) {
			hashtable[i] = x;
			for (int j = 0; j < count; j++) {
				printf("C");
			}
			return i;
		}

		// 이중 해싱을 위한 인자 k 관리
		k++;
		// 충돌 횟수 카운트
		count++;
		
	}
	return -2;
}


// key 탐색 함수
int searchKey(int x) {
	int i = hashFunction1(x);
	int k = 0;
	while (k<M) {
		i = (hashFunction1(x) + hashFunction2(x) * k % M) % M;
		if (hashtable[i] == 0) return -1;
		if (hashtable[i] == x) return i;
		
		k++;
	}
	return -1;
}

void print() {
	for (int i = 0; i < M; i++) {
		printf(" %d", hashtable[i]);
	}
	printf("\n");
}

// h1 함수
int hashFunction1(int x) {
	return x % M;
}

// h2 함수
int hashFunction2(int x) {
	return q - (x % q);
}

// 해시테이블 메모리 해제 함수
void freeMemory() {
	free(hashtable);
}