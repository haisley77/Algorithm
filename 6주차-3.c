#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable:4996)


int findk(int a, int b, int n) {
	char ch;

	for (int i = 0; i < n; i++) {
		scanf("%c", &ch);
		// ���� �ϳ� �о���̱�

		int mid = (a + b) / 2;
		// �߰� �ε��� mid ������ ����

		if (ch == 'Y') {
			a = mid + 1;
		}
		if (ch == 'N') {
			b = mid;
		}
	}

	// k�� ã�� ���� ��Ȯ�� ���� ���� �־����ٰ� ���������Ƿ� a != b �� �Ǵ� ���� ������� �ʾƵ� ��

	return a;
}

int main() {
	int a, b, n;

	scanf("%d %d %d", &a, &b, &n);
	getchar();

	printf("%d", findk(a, b, n));
	
	return 0;
}