#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int max_stack_size = 10;

void push(int *stk, int *top, int val) {
	assert(stk != NULL);
	assert(*top < max_stack_size);
	assert(top > 0);
	stk[*top] = val;
	*top = *top + 1;
}

int pop(int *stk, int *top) {
	int popd = -1;
	assert(stk != NULL);
	assert(*top <= max_stack_size);
	*top = *top -1;
	popd = stk[*top];
}

void print_stack(const int *stk, const int top) {
	int i = top - 1;
	printf("tos: ");
	while(i >= 0) {
		printf("%d, ", stk[i]);
		i--;
	}
	printf("eos\n");
}

void test_stack() {
	int *stack = (int *) malloc(sizeof(int) * max_stack_size);
	int stack_top = 0;
	int popd;
	int i = 0;
	for (i = 0; i < 10; i++) {
		push(stack, &stack_top, i * 10);
	}
	print_stack(stack, stack_top);
	for(i = 9; i >=0; i--) {
		popd = pop(stack, &stack_top);
		assert(popd == i * 10);
	}
	assert(stack_top == 0);

	push(stack, &stack_top, 10);
	assert(stack_top == 1);
	push(stack, &stack_top, 20);
	assert(stack_top == 2);
	popd = pop(stack, &stack_top);
	assert(popd == 20);

}

void main() {
	test_stack();
}


