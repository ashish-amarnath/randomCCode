#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define MAX_NODES 10

struct sll_node {
	int data;
	struct sll_node *next;
};

void print_sll(const struct sll_node *head) {
	const struct sll_node *cur = head;
	while (cur != NULL) {
		printf("%d->", cur->data);
		cur = cur->next;
	}
	printf("NULL\n");
}

struct sll_node* get_new_node(int val) {
	struct sll_node *new_node = (struct sll_node*) malloc(sizeof(struct sll_node));
	assert(new_node != NULL);
	new_node->data = val;
	new_node->next = NULL;
	return new_node;
}

void enqueue(struct sll_node **head, int val) {
	struct sll_node *new_node = get_new_node(val);
	new_node->next = *head;
	*head = new_node;
}

void insert_end(struct sll_node **head, int val) {
	struct sll_node *new_node = get_new_node(val);
	struct sll_node *prev = NULL, *cur = *head;
	new_node->next = NULL;
	if (*head == NULL) {
		*head = new_node;
	} else {
		while (cur->next != NULL) {
			cur = cur->next;
		}
		cur->next = new_node;
	}
}

int dequeue(struct sll_node **head) {
	int dqd = -1;
	assert(*head != NULL);
	struct sll_node *prev = NULL, *cur = *head;
	if (cur->next == NULL) {
		*head = NULL;
	} 
	while(cur->next != NULL) {
		prev = cur;
		cur = cur->next;
	}
	dqd = cur->data;
	if (prev != NULL) {
		prev->next = NULL;
	}
	free(cur);
	return dqd;
}

void delete_value(struct sll_node **head, int val) {
	struct sll_node *prev = NULL, *cur = *head;
	assert(*head != NULL);
	if (cur->data == val) {
		*head = cur->next;
		free(cur);
	} else {
		while(cur != NULL && cur->data != val) {
			prev = cur;
			cur = cur->next;
		}
		if (cur != NULL) {
			prev->next = cur->next;
			free(cur);
		}
	}
}

void delete_all_values(struct sll_node **head, int val) {
	struct sll_node *prev = NULL, *cur = *head;
	assert(*head != NULL);
	while (cur != NULL && cur->data == val) {
		*head = cur->next;
		free(cur);
		cur = *head;
	}
	if (cur != NULL) {
		prev = cur;
		cur = cur->next;
		while (cur != NULL) {
			if (cur->data == val) {
				prev->next = cur->next;
				free(cur);
				cur = prev;
			}
			prev = cur;
			cur = cur->next;
		}
	}
}

void test_insert_end() {
	struct sll_node *head = NULL;
	int i = 0;
	printf("RUNNING %s\n", __FUNCTION__);

	for (i = 1; i <= MAX_NODES; i++) {
		insert_end(&head, i);
	}
	print_sll(head);
	printf("%s: PASSED\n", __FUNCTION__);
}

void test_delete_all_values() {
	struct sll_node *head = NULL;
	printf("RUNNING %s\n", __FUNCTION__);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	enqueue(&head, 1);
	print_sll(head);
	delete_all_values(&head, 1);
	print_sll(head);
	assert(head == NULL);

	enqueue(&head, 1);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	delete_all_values(&head, 2);
	delete_all_values(&head, 1);
	print_sll(head);

	enqueue(&head, 1);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 2);
	enqueue(&head, 4);
	enqueue(&head, 2);
	print_sll(head);
	delete_all_values(&head, 2);
	print_sll(head);

	enqueue(&head, 1);
	enqueue(&head, 2);
	enqueue(&head, 4);
	enqueue(&head, 2);
	enqueue(&head, 4);
	enqueue(&head, 3);
	enqueue(&head, 4);
	enqueue(&head, 2);
	enqueue(&head, 4);
	enqueue(&head, 2);
	delete_all_values(&head, 4);
	print_sll(head);

	delete_all_values(&head, 40);
	print_sll(head);
	printf("%s: PASSED\n", __FUNCTION__);
}

void test_delete_value() {
	struct sll_node *head = NULL;
	printf("RUNNING %s\n", __FUNCTION__);
	enqueue(&head, 1);
	print_sll(head);
	delete_value(&head, 1);
	assert(head == NULL);

	enqueue(&head, 1);
	enqueue(&head, 2);
	enqueue(&head, 3);
	enqueue(&head, 4);
	print_sll(head);
	delete_value(&head, 10);
	print_sll(head);
	delete_value(&head, 4);
	delete_value(&head, 4);
	print_sll(head);
	delete_value(&head, 2);
	delete_value(&head, 2);
	print_sll(head);
	delete_value(&head, 1);
	print_sll(head);
	delete_value(&head, 3);
	print_sll(head);
	printf("%s: PASSED\n", __FUNCTION__);
}

void test_enqueue() {
	struct sll_node *head = NULL;
	int i = 1;
	printf("RUNNING %s\n", __FUNCTION__);
	for(i = 1; i <= MAX_NODES; i++) {
		enqueue(&head, i);
	}
	// should print 10->9->8->...1->NULL
	print_sll(head);
	printf("%s: PASSED\n", __FUNCTION__);
}

void test_dequeue() {
	struct sll_node *head = NULL;
	int dqd = -1;
	int i = 1;

	printf("RUNNING %s\n", __FUNCTION__);
	printf("Case 1");
	enqueue(&head, 10);
	dqd = dequeue(&head);
	assert(dqd == 10);
	assert(head == NULL);
	printf (": PASSED\n");

	printf("\nCase 2\n");
	for(i = 1; i <= MAX_NODES; i++) {
		enqueue(&head, i);
	}
	print_sll(head);
	for(i = 1; i <= MAX_NODES; i++) {
		dqd = dequeue(&head);
		assert(dqd == i);
		print_sll(head);
	}
	printf (": PASSED\n");
	printf("%s: PASSED\n", __FUNCTION__);
}

void main() {
	test_enqueue();
	test_dequeue();
	test_delete_value();
	test_delete_all_values();
	test_insert_end();
}



