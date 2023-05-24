#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>
#include <pthread.h>

/*
 ============================================================================
 Name        : 2023_ex2_part2.c
 Author      : Dar Levy
 Version     : 1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */


/*
 * this is a global variable as mentioned in recitation 5.
 * use in part 2 question 1
 */
int flag = 0;

/*
 * This is a global integer and the syntax for mutex.
 * use in part 2 question 2
 * static pthread_mutex_t my_lock = PTHREAD_MUTEX_INITIALIZER;
 * pthread_mutex_lock (&my_lock);
 * pthread_mutex_unlock (&my_lock);
 */

int k = 0;

static pthread_mutex_t my_lock1 = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t my_lock2 = PTHREAD_MUTEX_INITIALIZER;

void print_dark_vader_lines() {
    if (flag == 0 && k == 0){
        printf("Luke, I am your father!\n");
        k = 1;

        sleep(2);
        if (flag == 1 && k == 1) {
            printf("Search your feelings, you know it to be true.\n");
            k = 2;
        }

        sleep(4);
        if (flag == 2 && k == 2) {
            printf("luke, you can destroy the emperor, he has foreseen it.\n");
        }
    }
}

void print_luke_lines() {
    if (flag == 0 && k == 1) {
        printf("No! it's not true! it's impossible\n");
        flag = 1;
        sleep(3);
        if (flag == 1 && k == 2) {
            printf("Noooooooooooooo\n");
            flag = 2;
        }
    }
}

void *threadFunc(void *vargp){
    pthread_mutex_lock (&my_lock2);
    sleep(1);
    print_luke_lines();
    pthread_mutex_unlock(&my_lock2);


    pthread_mutex_lock (&my_lock1);
    print_dark_vader_lines();
    pthread_mutex_unlock(&my_lock1);

    return NULL;
}


int main(void) {
    pthread_t thread_id1;
    pthread_t thread_id2;


    pthread_create(&thread_id1, NULL, threadFunc, NULL);
    pthread_create(&thread_id2, NULL, threadFunc, NULL);

    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

    return 1;
}




