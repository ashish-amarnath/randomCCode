#include <stdio.h>
#include <assert.h>

int bin_srch(const int *a, const int len, const int key) {
	int l = 0, r = len - 1, mid = -1;

	while(l <= r) {
		mid = l + (r - l) / 2;
		if (a[mid] == key) {
			return mid;
		} else if (a[mid] < key) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return -1;
}

void test1_bin_srch() {
	int a1[] = { 5, 6, 12, 15, 66, 98};
	int l1 = 5;
	int i = 0;
	int res = -1;
	for (i = 0; i < 5; i++) {
		res = bin_srch(a1, l1, a1[i]);
		assert(res == i);
	}
	res = bin_srch(a1, l1, -1);
	assert(res == -1);

	res = bin_srch(a1, l1, 101);
	assert(res == -1);
}

void test2_bin_srch() {
	int a[] = { 5, 7, 57, 63, 72, 89};
	int len = 6;
	int i = 0, res = -1;

	for (i = 0; i < len; i++) {
		res = bin_srch(a, len, a[i]);
		assert(res == i);
	}

	res = bin_srch(a, len, -1);
	assert(res == -1);

	res = bin_srch(a, len, 101);
	assert(res == -1);
}

int bin_srch_get_first_or_last(const int *a, const int len, const int key, int get_first) {
	int l = 0, r = len, mid = -1;
	int res = -1;

	while (l <= r) {
		mid = l + (r - l) / 2;
		if (a[mid] == key) {
			res = mid;
			if (get_first) {
				r = mid - 1;
			} else {
				l = mid + 1;
			}
		} else if (a[mid] < key) {
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}

int bin_srch_get_first(const int *a, const int len, const int key) {
	return bin_srch_get_first_or_last(a, len, key, 1);
}

int bin_srch_get_last(const int *a, const int len, const int key) {
	return bin_srch_get_first_or_last(a, len, key, 0);
}

void test1_bin_srch_get_first_or_last() {
	int a[] = {1, 1, 1, 1, 2, 3, 3, 4, 4};
	const int len = 9;
	int res = -1;
	res = bin_srch_get_first(a, len, 1);
	assert(res == 0);
	res = bin_srch_get_last(a, len, 1);
	assert(res == 3);
	res = bin_srch_get_first(a, len, 10);
	assert(res == -1);
	res = bin_srch_get_last(a, len, 10);
	assert(res == -1);
}

void main() {
	test1_bin_srch();
	test2_bin_srch();
	test1_bin_srch_get_first_or_last();
}

