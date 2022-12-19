#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)

int n, M;
int* hashtable;

// �ʿ� �Լ� ���
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

			// key�� �������� ������ -1 ���
			if (searchKey(x) == -1) printf("%d\n", searchKey(x));
			// key�� �����ϸ� key ��ġ�� key ���
			else printf("%d %d\n", searchKey(x), hashtable[searchKey(x)]);
	
		}
		if (type == 'e') {
			break;
		}
	}

	freeMemory();

	return 0;
}



// �ؽ����̺� ���� �� �ʱ�ȭ �Լ�
void initHashtable() {
	hashtable = (int*)malloc(sizeof(int) * M);
	// �ؽ����̺� �迭 �����Ҵ�
	for (int i = 0; i < M; i++) {
		hashtable[i] = 0;
	}
}


// key ���� �Լ�
int insertKey(int x) {
	int i = hashFunction(x);
	int count = 0;

	while (1) {

		// ���� ������ ��� key ���� & �浹 Ƚ����ŭ C ���
		if (hashtable[i]==0) {
			hashtable[i] = x;
			for (int j = 0; j < count; j++) {
				printf("C");
			}
			return i;
		}

		i++;
		if (i == M) i = 0;
		// �浹 Ƚ�� ī��Ʈ
		count++;

	}
}

// key Ž�� �Լ�
int searchKey(int x) {
	int i = hashFunction(x);
	
	while (1) {
		// key ��ġ ��ȯ
		if (hashtable[i] == x) return i;
		else {
			// key�� �������� ������ -1 ��ȯ
			if (hashtable[i] == 0) return -1;

			// �浹 �� �ٷ� �� Ž��
			i++;
			// �ؽ����̺� �ε��� �ʰ� �� �� ������ �̵��� Ž��
			if (i == M) i = 0;
		}
	}

	return -1;
}

// �ؽ� �Լ�
int hashFunction(int x) {
	return x % M;
}

// �ؽ����̺� �޸� ����
void freeMemory() {
	free(hashtable);
}