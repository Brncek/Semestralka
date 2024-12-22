#pragma once
#include <stdbool.h>
#include <pthread.h>
#include <stdatomic.h>

typedef enum zobrazenie {
    SYM_MOD,
    SUM_MOD
} zobrazenie;

typedef enum smer {
    HORE_SMER,
    DOLE_SMER,
    VPAVO_SMER,
    VLAVO_SMER
} smer ;

typedef struct cords{
    int x;
    int y;
} cords;

typedef struct svet {
    cords prekazky[20000];
    int pocetPrekaziek;
    int rozmerySveta[2];
} svet;

typedef struct symInfo
{
    svet svet;
    int replikacie;
    double smeri[4];
    int maxPocetKrokov;
    char ulozenie[256];

} symInfo;

typedef struct rep
{
    int poradie;
    bool  prejdenePolicka[150][150];
    int  poctyDlzok[150][150];
    int  poctyDos[150][150];
    int krok;
    cords aktPozicia;
} rep;


typedef struct sym {
    //synchronizacia
    pthread_mutex_t  symMutex;
    pthread_cond_t  posunCond;

    symInfo symInfo;
    rep aktualRep;
    int poctyDlzokSum[150][150];
    int poctyDosSum[150][150];
    bool koniec;
} sym;

typedef struct server {
    sym sym;
    
    //TODO: synchronizacia
    pthread_mutex_t serverMutex;
    pthread_cond_t  koniec;
    bool koniec_info;
    zobrazenie zob;
    int pocetKlientov;
}server;

typedef struct klientData {
    atomic_bool * koniec;
    server * serverData;
    char* popisovac; 
} klientData;