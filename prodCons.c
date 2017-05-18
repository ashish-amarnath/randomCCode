#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>
#include <assert.h>

const int QUEUE_SIZE = 10;
struct item {
	int id;
	char *name;
	char *info;
};

struct item *item_q= NULL;
int item_q_size = 0;
pthread_mutex_t queue_lock = PTHREAD_MUTEX_INITIALIZER;
sem_t empty_buffer_count, full_buffer_count;


void init() {
	int rc = -1;
	item_q = (struct item*) malloc(sizeof(struct item) * QUEUE_SIZE);
	assert(item_q != NULL); // catch bad alloc with assert
	item_q_size = 0;
	rc = sem_init(&empty_buffer_count, 0, QUEUE_SIZE);
	assert(rc == 0);
	rc = sem_init(&full_buffer_count, 0, 0);
	assert(rc == 0);
}

void* producer(void *arg) {
	int rc = -1;
	while(1) {
		//printf("waiting to decrement empty_buffer_count\n");
		rc = sem_wait(&empty_buffer_count);
		assert (rc == 0);
		//printf("waiting to acquire queue_lock\n");
		pthread_mutex_lock(&queue_lock);
		item_q[item_q_size].id = item_q_size * 10;
		item_q[item_q_size].name = strdup("item1");
		item_q[item_q_size].info = strdup("item1info");
		printf ("Producer produced item @ %d {id:%d, name=%s, info=%s}\n", item_q_size,
				item_q[item_q_size].id, item_q[item_q_size].name, item_q[item_q_size].info);
		item_q_size++;
		pthread_mutex_unlock(&queue_lock);
		//printf("incremented full_buffer_count\n");
		rc = sem_post(&full_buffer_count);
		assert(rc == 0);
//		sleep(2);
	}
}

void* consumer(void *arg) {
	int rc = -1;
	while(1) {
		//printf ("Consumer waiting to decrement full buffers\n");
		rc = sem_wait(&full_buffer_count);
		assert(rc == 0);
		//printf ("Consumer waiting to acquire queue lock\n");
		pthread_mutex_lock(&queue_lock);
		printf ("Consuming item @%d {id:%d, name:%s, info:%s}\n", item_q_size - 1,
				item_q[item_q_size-1].id, item_q[item_q_size-1].name, item_q[item_q_size-1].info);
		item_q_size--;
		pthread_mutex_unlock(&queue_lock);
		//printf ("Consumer incrementing number of empty buffers\n");
		rc = sem_post(&empty_buffer_count);
		assert(rc == 0);
//		sleep(2);
	}
}

void main() {
	pthread_t prod, cons;
	init();
//	consumer(NULL);
	pthread_create(&cons, NULL, consumer, NULL);
	printf ("Press any key to start producer\n");
	getchar();
	pthread_create(&prod, NULL, producer, NULL);
	
	pthread_join(prod, NULL);
	pthread_join(cons, NULL);
}


