#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <errno.h>
#include <string.h>

void eee() {
    printf("Exit\n");
    shm_unlink("shared_memory");
    sem_unlink("semaphre_full");
    sem_unlink("semaphre_empty");
}

int main(int argc, char **argv) {
    atexit(eee);
    if (argc == 2) {
        return 0;
    }
    char role = 't';
    if (argc == 1) {
        int p = fork();
        if (p == 0) {
            role = 'p';
            printf("start producer process %d\n", getpid());
        } else {
            sleep(1);
            printf("start consumer process %d\n", getpid());
            role = 'c';
        }
    }

    int buf;
    sem_t *full, *empty;
    char * mem;


    buf = shm_open("shared_memory", O_RDWR|O_CREAT, 0666);
    if (buf < 0) {
        perror("shared memory");
        exit(-1);
    }
    printf("open shared file %d\n", buf);
    struct stat buf_stat;
    fstat(buf, &buf_stat);

    int creating = 0;
    if (buf_stat.st_size != 128) {
        printf("st_size: %d\n", buf_stat.st_size);
        ftruncate(buf, 128);
        creating = 1;
    }

    mem = mmap(NULL, 128, PROT_READ| PROT_WRITE, MAP_SHARED, buf, 0);
    if (mem == NULL) {
        perror("mmap");
        exit(-1);
    }
    close(buf);
    if (role == 'p') {
        memset(mem, 0, 128);
    }

    sleep(1);
    
    if (role == 'p') {
        full = sem_open("semaphre_full", O_CREAT, 0666, 0);
        empty = sem_open("semaphre_empty", O_CREAT, 0666, 10);
    } else if (role == 'c') {
        full = sem_open("semaphre_full", O_EXCL);
        empty = sem_open("semaphre_empty", O_EXCL);
    }
    if (full == SEM_FAILED || empty == SEM_FAILED) {
        perror("semaphore");
        exit(-1);
    }

    printf("full: %p, empty: %p, pid: %d\n", full, empty, getpid());

    if (role == 'p') {
        sem_post(empty);
        while (1) {
            //printf("waiting for empty ");
            //fflush(stdout);
            sem_wait(empty);
            //printf("Done\n");
            sleep(rand() % 5);
            for (int i = 0; i < 10; i++) {
                if (mem[i] == 0) {
                    mem[i] = 1;
                    break;
                }
            }
            printf("produced a product.  ");
            for (int i = 0; i < 10; i++) {
                printf("%d ", mem[i]);
            }
            printf("\n");
            sem_post(full);
        }
    } else if (role == 'c') {
        while (1) {
            //printf("waiting for full ");
            //fflush(stdout);
            sem_wait(full);
            //printf("Done!\n");
            sleep(rand() % 10);
            for (int i = 0; i < 10; i++) {
                if (mem[i] == 1) {
                    mem[i] = 0;
                    break;
                }
            }

            printf("consumed a product.  ");
            for (int i = 0; i < 10; i++) {
                printf("%d ", mem[i]);
            }
            printf("\n");
            sem_post(empty);
        }
    }
}