#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileManager.h"

svet nacitajSvet(const char *nazovSuboru) {
    FILE *subor = fopen(nazovSuboru, "r");
    if (!subor) {
        perror("Nepodarilo sa otvorit subor");
        exit(0);
    }

    svet mapa;
    mapa.pocetPrekaziek = 0;
    mapa.prekazky = NULL;

    char riadok[256];
    int riadokIndex = 0;
    int x = 0, y = 0;

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (strncmp(riadok, "MAP:", 4) == 0) {
            sscanf(riadok, "MAP: %d %d", &mapa.rozmerySveta[0], &mapa.rozmerySveta[1]);
            mapa.prekazky = malloc(mapa.rozmerySveta[0] * mapa.rozmerySveta[1] * sizeof(cords));
        } else if (strchr(riadok, 'o') || strchr(riadok, 'x')) {
            x = 0;
            for (int i = 0; riadok[i] != '\0'; i++) {
                if (riadok[i] == 'x') {
                    mapa.prekazky[mapa.pocetPrekaziek].x = x;
                    mapa.prekazky[mapa.pocetPrekaziek].y = y;
                    mapa.pocetPrekaziek++;
                }
                if (riadok[i] == 'o' || riadok[i] == 'x') {
                    x++;
                }
            }
            y++;
        }
    }

    fclose(subor);

    mapa.prekazky = realloc(mapa.prekazky, mapa.pocetPrekaziek * sizeof(cords));
    return mapa;
}


//TODO: chyba
symInfo nacitajSymulaciu(const char *nazovSuboru) {
    FILE *subor = fopen(nazovSuboru, "r");
    if (!subor) {
        perror("Nepodarilo sa otvoriť subor");
        exit(1);
    }

    symInfo symulacia;
    char riadok[256];

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (strncmp(riadok, "SMR:", 4) == 0) {
            sscanf(riadok, "SMR: %lf %lf %lf %lf", 
                   &symulacia.smeri[0], &symulacia.smeri[1], 
                   &symulacia.smeri[2], &symulacia.smeri[3]);
        } else if (strncmp(riadok, "K:", 2) == 0) {
            sscanf(riadok, "K: %d", &symulacia.maxPocetKrokov);
        } 
    }
    fclose(subor);


    symulacia.svet = nacitajSvet(nazovSuboru);
    
    return symulacia;
}