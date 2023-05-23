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
#include <semaphore.h>

/*
 ============================================================================
 Name        : 2023_ex2_part1.c
 Author      : Dar Levy
 Version     : 1
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#define SNAME "MySem"

/*
 * This is a syntax assistance for part 1 question 3
 open semaphore
 sem_t *sem = sem_open(SNAME, O_CREAT, 0777, 0);

 increment semaphore
sem_post(sem);

 decrement semaphore
sem_wait(sem);
*/

void write_to_fd(int fd[2]) {
    close(fd[0]);
    write(fd[1],"true", sizeof(char[50]));
    close(fd[1]);
}

void read_from_fd(int fd[2]) {
    close(fd[1]);
    int x;
    read(fd[0], &x, sizeof(int));
    close(fd[0]);
}

int main(void) {
    int status;
    int fd1[2];
    int fd2[2];
    int fd3[2];
    int fd4[2];
    pipe(fd1);
    pipe(fd2);
    pipe(fd3);
    pipe(fd4);

    status = fork();
    if (status == 0){
        printf("No! it's not true! it's impossible\n");
        write_to_fd(fd2);
        read_from_fd(fd3);
        printf("Noooooooooooooo\n");
        write_to_fd(fd4);
    }
    else{
        printf("Luke, I am your father!\n");
        write_to_fd(fd1);
        read_from_fd(fd2);
        printf("Search your feelings, you know it to be true.\n");
        write_to_fd(fd3);
        read_from_fd(fd4);
        printf("luke, you can destroy the emperor, he has foreseen it.\n");
    }
    return 1;
}

