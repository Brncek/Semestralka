#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <string.h>
#include "klientIPC.h"

#include "symulator.h"
#include "serverIPC.h"

sym spust(char* popisovac) {
    int shm_fd;
    server* serverSHM;

    //PRIPOJENIE
    shm_fd = shm_open(popisovac, O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    //MAPOVANIE
    serverSHM = mmap(NULL, sizeof(server), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (serverSHM == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    symuluj(&serverSHM->sym);

    pthread_mutex_lock(&serverSHM->serverMutex);
    serverSHM->koniec_info = true;
    pthread_mutex_unlock(&serverSHM->serverMutex);

    //zaistenie pripravenia klintov pre ukoncenie
    sleep(2);
    pthread_cond_signal(&(serverSHM->koniec));
    //zaistenie ze zmena bol spravena
    sleep(1);
    pthread_cond_signal(&(serverSHM->sym.posunCond));    
    //zaistenie ze klient sa stihol odpojit
    sleep(5);
    //uzavretie pamate
    munmap(serverSHM, sizeof(server));
    close(shm_fd);
    shm_unlink(popisovac);

    sym symData = serverSHM->sym;
    return symData;
}

