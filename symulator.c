#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#include "symulator.h"


int svetX(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[1];
}

int svetY(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[0];
}

bool jePrekazka(sym * sym, cords cord) {
    cords * prekazky = sym->symInfo.svet.prekazky;
    for (int i = 0; i < sym->symInfo.svet.pocetPrekaziek; i++)
    {
        if (prekazky[i].x == cord.x && prekazky[i].y == cord.y)
        {
            return true;
        }
    }   
    return false;
}

bool jeStred(sym * sym, cords cord) {
    cords stred;
    stred.x = svetX(sym) / 2;
    stred.y = svetY(sym) / 2;

    return stred.x == cord.x && stred.y == cord.y;
}

smer randSmer(sym * sym) {
    double nahodne = (double)rand() / (double)RAND_MAX;
    
    if (nahodne <= sym->symInfo.smeri[0])
    {
        return HORE_SMER;
    } 
    nahodne -= sym->symInfo.smeri[0];

    if (nahodne  <= sym->symInfo.smeri[1])
    {
        return DOLE_SMER;
    } 
    nahodne -= sym->symInfo.smeri[1];

    if (nahodne <= sym->symInfo.smeri[2])
    {
        return VPAVO_SMER;
    } 
    
    return VLAVO_SMER;
}

void posun(sym* sym) {
    bool kolizia = true;
    cords posunCords;
  
    while (kolizia)
    {
        kolizia = false;
        posunCords.x = sym->aktualRep.aktPozicia.x;
        posunCords.y = sym->aktualRep.aktPozicia.y;

        switch (randSmer(sym))
        {
        case HORE_SMER:
            posunCords.y--;
            break;
        case DOLE_SMER:
            posunCords.y++;
            break;
        case VPAVO_SMER:
            posunCords.x++;
            break;
        case VLAVO_SMER:
            posunCords.x--;
            break;
        
        default:
            break;
        }

        if(posunCords.x < 0 || posunCords.y < 0) {
            kolizia = true;
            continue;
        }

        if(posunCords.x >= svetX(sym) || posunCords.y >= svetY(sym)) {
            kolizia = true;
            continue;
        }

        kolizia = jePrekazka(sym, posunCords);
        cords * prekazky = sym->symInfo.svet.prekazky;
    }

    sym->aktualRep.aktPozicia.x = posunCords.x;
    sym->aktualRep.aktPozicia.y = posunCords.y;
    sym->aktualRep.prejdenePolicka[posunCords.y][posunCords.x] = true;
    sym->aktualRep.krok++;
}

//POZOR symulacia ostava alokovana
void symuluj(sym* sym) {
    //ZAMKNI
    sym->poctyDlzokSum = calloc(svetY(sym), sizeof(int*));
    sym->poctyDosSum = calloc(svetY(sym), sizeof(int*));
    sym->aktualRep.prejdenePolicka = calloc(svetY(sym), sizeof(bool*));
    sym->aktualRep.poctyDlzok = calloc(svetY(sym), sizeof(int*));
    sym->aktualRep.poctyDos = calloc(svetY(sym), sizeof(int*));
    for (int y = 0; y < svetY(sym); y++)
    {
        sym->poctyDlzokSum[y] = calloc(svetX(sym), sizeof(int));
        sym->poctyDosSum[y] = calloc(svetX(sym), sizeof(int));
        sym->aktualRep.prejdenePolicka[y] = calloc(svetX(sym), sizeof(bool)); 
        sym->aktualRep.poctyDlzok[y] = calloc(svetX(sym), sizeof(int));
        sym->aktualRep.poctyDos[y] = calloc(svetX(sym), sizeof(int));  
    }

    //PRIPRAVA
    srand(time(NULL));
    sym->aktualRep.poradie = 1;
    
    //TODO: ODOMKNI

    while (sym->aktualRep.poradie <= sym->symInfo.replikacie)
    {

        //REPLIKACIA
        for (int x = 0; x < svetX(sym); x++)
        {
            for (int y = 0; y < svetY(sym); y++)
            {
                //TODO: zamkni
                for (int x = 0; x < svetX(sym); x++)
                {
                    for (int y = 0; y < svetY(sym); y++)
                    {
                        sym->aktualRep.prejdenePolicka[y][x] = false;
                    }
                }

                cords cord;
                cord.x = x;
                cord.y = y;

                if (jeStred(sym, cord))
                {
                    continue;
                }
                if (jePrekazka(sym, cord))
                {
                    continue;
                }

                sym->aktualRep.aktPozicia.x = x;
                sym->aktualRep.aktPozicia.y = y; 
                sym->aktualRep.krok = 0;
                sym->aktualRep.prejdenePolicka[y][x] = true;
                //TODO: ODOMKNI

                bool pokracuj = true;

                while (pokracuj)
                {
                    //TODO: ZAMKNI
                    posun(sym);

                    if (jeStred(sym,sym->aktualRep.aktPozicia)) 
                    {
                        sym->aktualRep.poctyDos[y][x] = 1;
                        sym->aktualRep.poctyDlzok[y][x] =  sym->aktualRep.krok;   
                        pokracuj = false;
                    }
                    if (sym->aktualRep.krok == sym->symInfo.maxPocetKrokov)
                    {
                        sym->aktualRep.poctyDos[y][x] = 0;
                        sym->aktualRep.poctyDlzok[y][x] = 0;    
                        pokracuj = false;
                    }   
                    vykresliMapu(sym, SYM_MOD);
                    //TODO: ODOMKNI
                    sleep(1); 
                }
            }
        }

        //PRIDANIE VYSLEDKOV
        //TODO: ZAMKNI
        sym->aktualRep.poradie++;
        int ** poctyDlzokSum = sym->poctyDlzokSum; 
        int ** poctyDosSum = sym->poctyDosSum;
        int ** poctyDlzok = sym->aktualRep.poctyDlzok;
        int ** poctyDos = sym->aktualRep.poctyDos;
        for (int x = 0; x < svetX(sym); x++)
        {
            for (int y = 0; y < svetY(sym); y++)
            {
                poctyDlzokSum[y][x] += poctyDlzok[y][x];
                poctyDosSum[y][x] += poctyDos[y][x];
            }
        }
        //TODO: ODOMKNI
    }
}

void destroySym(sym * sym) {
    for (int y = 0; y < svetY(sym); y++)
    {
        free(sym->aktualRep.prejdenePolicka[y]);
        free(sym->poctyDlzokSum[y]);
        free(sym->poctyDosSum[y]);   
        free(sym->aktualRep.poctyDlzok[y]); 
        free(sym->aktualRep.poctyDos[y]);  
    }
    free(sym->aktualRep.prejdenePolicka);
    free(sym->poctyDlzokSum);
    free(sym->poctyDosSum);    
    free(sym->aktualRep.poctyDlzok);
    free(sym->aktualRep.poctyDos);

    free(sym->symInfo.svet.prekazky);
}

void vykresliMapu(sym * sym, zobrazenie zobrazenie) {
    printf("\n");
    if (zobrazenie == SYM_MOD)
    {
        printf("MOD: SYM\n");
    } else {
        printf("MOD: SUM\n");
    }
    
    printf("|-------------------------------------------|\n");
    printf("SMERY: \nHORE: %lf \nDOLE: %lf \nVPRAVO: %lf \nVLAVO: %lf\n", 
    sym->symInfo.smeri[0], sym->symInfo.smeri[1], sym->symInfo.smeri[2], sym->symInfo.smeri[3] );
    printf("REPS: %d / %d\n", sym->symInfo.replikacie, sym->aktualRep.poradie);
    printf("Krok: %d / %d\n", sym->symInfo.maxPocetKrokov, sym->aktualRep.krok);
    printf("|-------------------------------------------|\n\n");

    if (zobrazenie == SYM_MOD)
    {

        bool ** prejdene = sym->aktualRep.prejdenePolicka;
        for (int y = 0; y < svetY(sym); y++)
        {
            for (int x = 0; x < svetX(sym); x++)
            {
                cords cord;
                cord.x = x;
                cord.y = y;
                if (jePrekazka(sym, cord))
                {
                    printf("\u2588\u2588");
                }
                else if (sym->aktualRep.aktPozicia.x == x && 
                sym->aktualRep.aktPozicia.y == y) {
                    printf("[]");    
                }
                else if (jeStred(sym, cord)) 
                {
                    printf("/\\");
                } 
                else if (prejdene[y][x])
                {
                    printf("::");    
                } 
                else 
                {
                    printf("--");
                }
            }
            printf("\n");
        }
    }
    else 
    {
        //SUMAR STRING
    }
    printf("\n");
}