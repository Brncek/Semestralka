#pragma once
#include <stdbool.h>

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
    cords * prekazky;
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
    bool ** prejdenePolicka;
    int ** poctyDlzok;
    int ** poctyDos;
    int krok;
    cords aktPozicia;
} rep;


typedef struct sym {
    symInfo symInfo;
    rep aktualRep;
    int ** poctyDlzokSum;
    int ** poctyDosSum;
    //TODO synchronizacia
} sym;

typedef struct server {
    sym sym;
    zobrazenie zob;
    int pocetKlientov;
    //TODO: synchronizacia
}server;