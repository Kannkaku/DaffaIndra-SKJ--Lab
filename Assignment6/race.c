#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void *increment();
void *decrement();

int shared = 1;

int main(){
	pthread_t thread1, thread2;
	pthread_create(&thread1, NULL, increment, NULL);
	pthread_create(&thread2, NULL, decrement, NULL);
	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	printf("Nilai akhir dari shared variable adalah %d\n", shared);
}

void *increment() {
	int x;
	x = shared;
	printf("Thread1 membaca nilai dari variabel bersama sebagai %d\n", x);
	x++;
	printf("Pembaruan lokal oleh Thread 1: %d\n", x);
	sleep(1);
	shared = x;
	printf("Nilai dari variabel bersama yang diperbarui oleh Thread 1 adalah: %d\n", shared);
}

void *decrement() {
	int y;
	y = shared;
	printf("Thread 2 membaca nilai dari variabel bersama sebagai %d\n", y);
	y--;
	printf("Pembaruan lokal oleh Thread 2: %d\n", y);
	sleep(1);
	shared = y;
	printf("Nilai dari variabel bersama yang diperbarui oleh Thread 2 adalah: %d\n", shared);
}
