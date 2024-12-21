#include <stdio.h>
#include "debugTests.h"
#include "dataStructures.h"

void vypisSvet(svet mapa) {
    printf("Rozmery sveta: %d x %d\n", mapa.rozmerySveta[0], mapa.rozmerySveta[1]);
    printf("Počet prekážok: %d\n", mapa.pocetPrekaziek);
    printf("Súradnice prekážok:\n");
    for (int i = 0; i < mapa.pocetPrekaziek; i++) {
        printf("(%d, %d)\n", mapa.prekazky[i].x, mapa.prekazky[i].y);
    }
}

void vypisSymulaciu(symInfo symulacia) {
    printf("Simulačné parametre:\n");
    printf("Počet replikácií: %d\n", symulacia.replikacie);
    printf("Maximálny počet krokov: %d\n", symulacia.maxPocetKrokov);
    printf("Pravdepodobnosti smerov:\n");
    printf("Hore: %.2f, Dole: %.2f, Vľavo: %.2f, Vpravo: %.2f\n",
           symulacia.smeri[0], symulacia.smeri[1], symulacia.smeri[2], symulacia.smeri[3]);
    printf("Uloženie výsledkov: %s\n", symulacia.ulozenie);

    vypisSvet(symulacia.svet);
}