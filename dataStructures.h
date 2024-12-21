#pragma once

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