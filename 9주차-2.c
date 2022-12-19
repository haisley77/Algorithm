#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n, M;
int* hashtable;

// 필요 함수 목록
void initHashtable();
int insertKey(int x);
int searchKey(int x);
int hashFunction(int x);
void freeMemory();

int main() {
	char type;
	int x;
	int insertnum = 0;
	scanf("%d %d", &M, &n);
	getchar();

	initHashtable();

	while (1) {
		scanf("%c", &type);
		getchar();

		if (type == 'i') {
			insertnum++;
			scanf("%d", &x);
			getchar();
			printf("%d\n",insertKey(x));
		}
		if (type == 's') {
			scanf("%d", &x);
			getchar();

			// key가 존재하지 않으면 -1 출력
			if (searchKey(x) == -1) printf("%d\n", searchKey(x));
			// key가 존재하면 key 위치와 key 출력
			else printf("%d %d\n", searchKey(x), hashtable[searchKey(x)]);
	
		}
		if (type == 'e') {
			break;
		}
	}

	freeMemory();

	return 0;
}



// 해시테이블 생성 및 초기화 함수
void initHashtable() {
	hashtable = (int*)malloc(sizeof(int) * M);
	// 해시테이블 배열 동적할당
	for (int i = 0; i < M; i++) {
		hashtable[i] = 0;
	}
}


// key 삽입 함수
int insertKey(int x) {
	int i = hashFunction(x);
	int count = 0;

	while (1) {

		// 삽입 가능한 경우 key 삽입 & 충돌 횟수만큼 C 출력
		if (hashtable[i]==0) {
			hashtable[i] = x;
			for (int j = 0; j < count; j++) {
				printf("C");
			}
			return i;
		}

		i++;
		if (i == M) i = 0;
		// 충돌 횟수 카운트
		count++;

	}
}

// key 탐색 함수
int searchKey(int x) {
	int i = hashFunction(x);
	
	while (1) {
		// key 위치 반환
		if (hashtable[i] == x) return i;
		else {
			// key가 존재하지 않으면 -1 반환
			if (hashtable[i] == 0) return -1;

			// 충돌 시 바로 옆 탐색
			i++;
			// 해시테이블 인덱스 초과 시 맨 앞으로 이동해 탐색
			if (i == M) i = 0;
		}
	}

	return -1;
}

// 해시 함수
int hashFunction(int x) {
	return x % M;
}

// 해시테이블 메모리 해제
void freeMemory() {
	free(hashtable);
}