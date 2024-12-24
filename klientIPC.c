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

void nahodmeMenoSHM(char *name) {
    srand(time(NULL));
    const char charset[] = "0123456789";
    name[0] = '/'; 
    for (size_t i = 1; i <= 5; i++) {
        int key = rand() % (sizeof(charset) - 1);
        name[i] = charset[key];
    }
    name[6] = '\0';
}

void initMedziProcMut(server *serverSHM) {
    pthread_mutexattr_t mutexAttr;
    pthread_condattr_t condAttr;

    pthread_mutexattr_init(&mutexAttr);
    pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED);

    pthread_condattr_init(&condAttr);
    pthread_condattr_setpshared(&condAttr, PTHREAD_PROCESS_SHARED);

    pthread_mutex_init(&serverSHM->serverMutex, &mutexAttr);
    pthread_cond_init(&serverSHM->koniec, &condAttr);

    pthread_mutex_init(&serverSHM->sym.symMutex, &mutexAttr);
    pthread_cond_init(&serverSHM->sym.posunCond, &condAttr);

    pthread_mutexattr_destroy(&mutexAttr);
    pthread_condattr_destroy(&condAttr);
}

void spustServer(char *shm_name, symInfo symInfo) {
    int shm_fd;
    server* serverSHM;
    nahodmeMenoSHM(shm_name);

    //TVORBA PAMATE
    shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        exit(EXIT_FAILURE);
    }

    //NASTAVENIE VELKOSTI
    if (ftruncate(shm_fd, sizeof(server)) == -1) {
        perror("ftruncate");
        exit(EXIT_FAILURE);
    }

    //NAMAPOVANIE
    serverSHM = mmap(NULL, sizeof(server), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (serverSHM == MAP_FAILED) {
        perror("mmap");
        close(shm_fd);
        exit(EXIT_FAILURE);
    }

    initMedziProcMut(serverSHM);

    serverSHM->pocetKlientov = 0;
    serverSHM->sym.koniec = false;
    serverSHM->sym.symInfo = symInfo;
    serverSHM->koniec_info = false;

    //odpojenie
    munmap(serverSHM, sizeof(server));
    close(shm_fd);

    //start serveru
    pid_t pid = fork(); 

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        execl("./server", "./server", shm_name, (char *)NULL);
        perror("execl");
        exit(EXIT_FAILURE);
    }
}

void* vystupFun(void * arg) {
    klientData* data = arg;

    while (!atomic_load(data->koniec))
    {
        pthread_mutex_lock(& data->serverData->sym.symMutex);
        pthread_cond_wait(& data->serverData->sym.posunCond, & data->serverData->sym.symMutex);
        //CLEAR TERMINAL AND WRITE
        
        //TODO:REMOVE
        //system("clear"); 
        printf("\nPopisovatel: %s\n", data->popisovac);

        if(!atomic_load(data->koniec)) {
            pthread_mutex_lock(& data->serverData->serverMutex);
            pthread_mutex_lock(data->internalMutex);
            vykresliMapu(& data->serverData->sym, data->serverData->zob, data->sumZob);
            pthread_mutex_unlock(data->internalMutex);
            pthread_mutex_unlock(& data->serverData->serverMutex);
        }
        

        pthread_mutex_unlock(& data->serverData->sym.symMutex);
        pthread_cond_signal(& data->serverData->sym.posunCond);

        printf("\nPrikazy:\n");  
        printf("m -> zmenenie modu\n");
        printf("o -> odchod\n");
        printf("u -> ukoncenie symulacie\n");
        printf("d -> zmenenie zobrazenych udajov (iba v SUM mode)\n");
        printf("> ");
    }
    
    return NULL;
}

void* vstupFun(void * arg) {
    klientData* data = arg;

    while (!atomic_load(data->koniec))
    {
        char odpoved = 'N';
        scanf("%c", &odpoved);
        printf("%c", odpoved);

        if (odpoved == 'o') {
            *data->koniec = true;
            pthread_cond_signal(&data->serverData->koniec);
        } else if (odpoved == 'm') {
            if(!atomic_load(data->koniec)) {
                pthread_mutex_lock(& data->serverData->serverMutex);
                if (data->serverData->zob == SYM_MOD)
                {
                    data->serverData->zob = SUM_MOD;
                } 
                else 
                {
                    data->serverData->zob = SYM_MOD;
                }
                pthread_mutex_unlock(& data->serverData->serverMutex);
            }
        } else if (odpoved == 'u')
        {
            if(!atomic_load(data->koniec)) {
                pthread_mutex_lock(& data->serverData->sym.symMutex);
                data->serverData->sym.koniec = true;
                pthread_mutex_unlock(& data->serverData->sym.symMutex);
            }
        } else if (odpoved == 'd') {
            if(!atomic_load(data->koniec)) {
                pthread_mutex_lock(data->internalMutex);
                if (data->sumZob== KROKY)
                {
                    data->sumZob = PRAVD;
                } 
                else 
                {
                    data->sumZob = KROKY;
                }
                pthread_mutex_unlock(data->internalMutex);
            }
        }
    }
    
    return NULL;
}

void pripojNaServer(char * popisovac) {
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

    pthread_t vystup;
    pthread_t vstup;
    atomic_bool koniec = false;
    klientData klientData;
    klientData.koniec = &koniec;
    klientData.serverData = serverSHM;
    klientData.popisovac = popisovac;
    klientData.sumZob = KROKY;

    pthread_mutex_t internalMutex;
    pthread_mutex_init(&internalMutex, NULL);
    klientData.internalMutex = &internalMutex;

    pthread_mutex_lock(&serverSHM->serverMutex);

    serverSHM->pocetKlientov++;
    if (serverSHM->pocetKlientov == 1)
    {
        serverSHM->zob = SYM_MOD;
    }
    
    pthread_create(&vystup, NULL, &vystupFun, &klientData); 
    pthread_create(&vstup, NULL, &vstupFun, &klientData); 

    while (!serverSHM->koniec_info && !atomic_load(&koniec))
    {
        pthread_cond_wait(&serverSHM->koniec, &serverSHM->serverMutex);
        printf("presiel \n");
    }
    printf("presiel waitom\n");

    serverSHM->pocetKlientov--;
    pthread_mutex_unlock(&serverSHM->serverMutex);

    koniec = true;
    pthread_cond_signal(&serverSHM->sym.posunCond);
    pthread_join(vystup, NULL);

    pthread_cond_signal(&(serverSHM->koniec));
    
    //TODO:REMOVE
    //system("clear"); 
    printf("Pre uplne ukoncenie stlacte enter\n");

    pthread_join(vstup, NULL); 
    pthread_mutex_destroy(&internalMutex);

    //odpojenie
    munmap(serverSHM, sizeof(server));
    close(shm_fd);
}