#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileManager.h"
#include "symulator.h"

void ulozSim(sym * sym) {
    if (strcmp(sym->symInfo.ulozenie,"n") == 0)
    {
        return;
    }
    

    FILE * ulozisko = fopen(sym->symInfo.ulozenie, "w");
    if (ulozisko == NULL) {
        printf("Ulozenie error");
        return;
    }

    fprintf(ulozisko, "SMR: %.2lf %.2lf %.2lf %.2lf\n", sym->symInfo.smeri[0],
    sym->symInfo.smeri[1], sym->symInfo.smeri[2], sym->symInfo.smeri[3]);

    fprintf(ulozisko, "K: %d\n", sym->symInfo.maxPocetKrokov);

    fprintf(ulozisko, "REP: %d\n\n", sym->symInfo.replikacie);

    fprintf(ulozisko,"OUT:\n");

    for (int y = 0; y < svetY(sym); y++)
    {
        for (int x = 0; x < svetX(sym); x++)
        {
            cords cord;
            cord.x = x;
            cord.y = y;

            fprintf(ulozisko,"[%.2lf  %d]", pravStred(sym, cord), priemKrokov(sym, cord));
        }
        fprintf(ulozisko,"\n");        
    }


    fprintf(ulozisko,"\n");
    fprintf(ulozisko,"MAP: %d %d\n", sym->symInfo.svet.rozmerySveta[0], 
    sym->symInfo.svet.rozmerySveta[1]);
    for (int y = 0; y < svetY(sym); y++)
    {
        for (int x = 0; x < svetX(sym); x++)
        {
            cords cord;
            cord.x = x;
            cord.y = y;

            if (jePrekazka(sym, cord))
            {
                fprintf(ulozisko,"x ");
            } 
            else
            {
                fprintf(ulozisko,"o ");
            }
        }
        fprintf(ulozisko,"\n");        
    }
    

    fclose(ulozisko);
}

svet nacitajSvet(const char *nazovSuboru) {
    FILE *subor = fopen(nazovSuboru, "r");
    if (!subor) {
        exit(0);
    }

    svet mapa;
    mapa.pocetPrekaziek = 0;

    char riadok[256];
    int riadokIndex = 0;
    int x = 0, y = 0;

    while (fgets(riadok, sizeof(riadok), subor)) {
        if (strncmp(riadok, "MAP:", 4) == 0) {
            sscanf(riadok, "MAP: %d %d", &mapa.rozmerySveta[0], &mapa.rozmerySveta[1]);
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

    return mapa;
}


symInfo nacitajSymulaciu(const char *nazovSuboru) {
    FILE *subor = fopen(nazovSuboru, "r");
    if (!subor) {
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