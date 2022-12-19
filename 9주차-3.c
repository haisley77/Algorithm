#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n, q, M;
int* hashtable;

// �ʿ� �Լ� ���
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
			// �ִ� �Է� Ƚ�� �ʰ� �� ���� X
			if (insertnum == n) continue;

			scanf("%d", &x);
			getchar();
			printf("%d\n", insertKey(x));
			// ���� Ƚ�� ī��Ʈ
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



// �ؽ����̺� ���� �� �ʱ�ȭ
void initHashtable() {
	hashtable = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < M; i++) {
		hashtable[i] = 0;
	}
}

// key ���� �Լ�
int insertKey(int x) {
	int i = hashFunction1(x);
	int k = 0;
	int count = 0;


	while (k<M) {
		// ���� �ؽ��� �̿��� �ε��� ����
		i = (hashFunction1(x) + hashFunction2(x) * k % M) % M;

		// key ���� ���� �� key ���� & �浹 Ƚ����ŭ C ���
		if (hashtable[i] == 0) {
			hashtable[i] = x;
			for (int j = 0; j < count; j++) {
				printf("C");
			}
			return i;
		}

		// ���� �ؽ��� ���� ���� k ����
		k++;
		// �浹 Ƚ�� ī��Ʈ
		count++;
		
	}
	return -2;
}


// key Ž�� �Լ�
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

// h1 �Լ�
int hashFunction1(int x) {
	return x % M;
}

// h2 �Լ�
int hashFunction2(int x) {
	return q - (x % q);
}

// �ؽ����̺� �޸� ���� �Լ�
void freeMemory() {
	free(hashtable);
}