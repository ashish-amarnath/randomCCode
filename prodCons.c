#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

const int QUEUE_SIZE = 1000000;
struct item {
	int id;
	char *name;
	struct item *next;
};

struct item *item_q_head = NULL;
struct item *item_q_tail = NULL;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_buffer_count, full_buffer_count;


void init() {
	int rc = -1;
	item_q_head = NULL;
	item_q_tail = NULL;
	rc = sem_init(&empty_buffer_count, 0, QUEUE_SIZE);
	assert(rc == 0);
	rc = sem_init(&full_buffer_count, 0, 0);
	assert(rc == 0);
}

struct item* get_new_item(const int id, const char *name) {
	struct item *new_item = (struct item*) malloc(sizeof(struct item));
	new_item->id = id;
	new_item->name = strdup(name);
	return new_item;
}

struct item* enqueue(const int id, const char *name) {
	struct item *new_item = get_new_item(id, name);
	if (item_q_tail == NULL) {
		assert(item_q_head == NULL);
		item_q_head = new_item;
		item_q_tail = new_item;
	} else {
		item_q_tail->next = new_item;
		item_q_tail = new_item;
		item_q_tail->next = NULL;
	}
	return new_item;
}

struct item* dequeue() {
	struct item *dqd = NULL;
	assert(item_q_head != NULL);
	assert(item_q_tail != NULL);
	dqd = item_q_head;
	if (item_q_head->next == NULL) {
		item_q_head = NULL;
		item_q_tail = NULL;
	} else {
		item_q_head = dqd->next;
	}
	return dqd;
}

void print_queue(const char *caller) {
	struct item *cur = item_q_head;
	printf ("%s:", caller);
	while (cur != NULL) {
		printf ("{id:%d, name=%s}->", cur->id, cur->name);
		cur = cur->next;
	}
	printf ("NULL\n");
}

void* producer(void *arg) {
	int rc = -1;
	int i = 1;
	struct item *prd = NULL;
	const char *it1 = "abc", *it2 = "def", *it3 = "ghi";
	while(1) {
		//printf("waiting to decrement empty_buffer_count\n");
		rc = sem_wait(&empty_buffer_count);
		assert (rc == 0);
		//printf("waiting to acquire queue_lock\n");
		pthread_mutex_lock(&queue_lock);
		switch(i % 3) {
			case 0:
				prd = enqueue(i * 10 % 4096, it1);
				break;
			case 1:
				prd = enqueue(i * 10 % 4096, it2);
				break;
			case 2:
				prd = enqueue(i * 10 % 4096, it3);
				break;
		}

		printf ("Producer produced item {id:%d, name=%s}\n", prd->id, prd->name);
		//print_queue(__FUNCTION__);
		pthread_mutex_unlock(&queue_lock);
		//printf("incremented full_buffer_count\n");
		rc = sem_post(&full_buffer_count);
		assert(rc == 0);
		//sleep(1);
  		i++;
	}
}

void* consumer(void *arg) {
	int rc = -1;
	struct item *consd = NULL;
	while(1) {
		//printf ("Consumer waiting to decrement full buffers\n");
		rc = sem_wait(&full_buffer_count);
		assert(rc == 0);
		//printf ("Consumer waiting to acquire queue lock\n");
		pthread_mutex_lock(&queue_lock);
		consd = dequeue();
		printf ("Consuming item {id:%d, name:%s}\n", consd->id, consd->name);
		free(consd->name);
		free(consd);
		//print_queue(__FUNCTION__);
		pthread_mutex_unlock(&queue_lock);
		//printf ("Consumer incrementing number of empty buffers\n");
		rc = sem_post(&empty_buffer_count);
		assert(rc == 0);
		//sleep(1);
	}
}

void test_queue() {
	int i = 0;
	struct item *dqd = NULL;
	for (i = 0; i < 10; i++) {
		enqueue(i, "abc");
	}
	print_queue(__FUNCTION__);
	while(item_q_head != NULL) {
		dqd = dequeue();
		printf ("dqd: {id: %d, name:%s}\n", dqd->id, dqd->name);
		print_queue(__FUNCTION__);
	}
	assert(item_q_tail == NULL);
	for (i = 0; i < 10; i++) {
		enqueue(i*10, "abc");
	}
	print_queue(__FUNCTION__);
	while(item_q_head != NULL) {
		dqd = dequeue();
		printf ("dqd: {id: %d, name:%s}\n", dqd->id, dqd->name);
		print_queue(__FUNCTION__);
	}
	assert(item_q_tail == NULL);
	for (i = 0; i < 10; i++) {
		enqueue(i*20, "abc");
	}
	print_queue(__FUNCTION__);
	while(item_q_head != NULL) {
		dqd = dequeue();
		printf ("dqd: {id: %d, name:%s}\n", dqd->id, dqd->name);
		print_queue(__FUNCTION__);
	}
	assert(item_q_tail == NULL);
}

void run() {
	pthread_t prod, cons;
	pthread_create(&cons, NULL, consumer, NULL);
	//printf ("Press any key to start producer\n");
	//getchar();
	pthread_create(&prod, NULL, producer, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
}

void main() {
	init();
	//test_queue();
	run();
}


