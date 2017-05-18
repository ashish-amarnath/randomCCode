#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void seive(int n) {
	int *arr = (int*) malloc(sizeof(int) * n);
	int i = 0;
	int mult = 2;
	for(i = 0; i < n; i++) {
		arr[i] = 1;
	}
	arr[0] = 0;
	arr[0] = 0;
	for (i = 2; i < sqrt(n); i++) {
		if (arr[i]) {
			for(mult = 2; i*mult < n ; mult++) {
				arr[i * mult] = 0;
			}
		}
	}

	for (i = 2; i < n; i++) {
		if (arr[i]) {
			printf ("%d ", i);
		}
	}
	printf("\n");

	free(arr);
}

void test_seive() {
	seive(500);
}

void main() {
	test_seive();
}

