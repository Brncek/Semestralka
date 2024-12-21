#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#include "symulator.h"

#define cas_medzi_krokmi 0.5

int svetX(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[1];
}

int svetY(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[0];
}

smer randSmer(sym * sym) {
    double nahodne = (double)rand() / (double)RAND_MAX;
    
    if (nahodne <= sym->symInfo.smeri[0])
    {
        return HORE_SMER;
    } 
    else if (nahodne <= sym->symInfo.smeri[1])
    {
        return DOLE_SMER;
    } 
    else if (nahodne <= sym->symInfo.smeri[2])
    {
        return VPAVO_SMER;
    } 
    else 
    {
        return VPAVO_SMER;
    }
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

        cords * prekazky = sym->symInfo.svet.prekazky;
        for (int i = 0; i < sym->symInfo.svet.pocetPrekaziek; i++)
        {
            if (prekazky[i].x == posunCords.x && prekazky[i].y == posunCords.y)
            {
                kolizia = true;
                break; 
            }
        }
    }

    sym->aktualRep.aktPozicia.x = posunCords.x;
    sym->aktualRep.aktPozicia.y = posunCords.y;
    sym->aktualRep.prejdenePolicka[posunCords.y][posunCords.x] = true;
    sym->aktualRep.krok++;
}

//POZOR SVET OSTAVA ALOKOVANY
void symuluj(sym* sym) {
    //ZAMKNI
    sym->poctyDlzokSum = callock(svetY(sym), sizeof(int*));
    sym->poctyDosSum = callock(svetY(sym), sizeof(int*));
    sym->aktualRep.prejdenePolicka = callock(svetY(sym), sizeof(bool*));
    sym->aktualRep.poctyDlzok = callock(svetY(sym), sizeof(int*));
    sym->aktualRep.poctyDos = callock(svetY(sym), sizeof(int*));
    for (int y = 0; y < svetY(sym); y++)
    {
        sym->poctyDlzokSum[y] = callock(svetX(sym), sizeof(int));
        sym->poctyDosSum[y] = callock(svetX(sym), sizeof(int));
        sym->aktualRep.prejdenePolicka[y] = callock(svetX(sym), sizeof(bool)); 
        sym->aktualRep.poctyDlzok[y] = callock(svetX(sym), sizeof(int));
        sym->aktualRep.poctyDos[y] = callock(svetX(sym), sizeof(int));  
    }

    //PRIPRAVA
    srand(Time(NULL));
    sym->aktualRep.poradie = 1;
    cords stred;
    stred.x = svetX(sym) / 2 + 1;
    stred.y = svetY(sym) / 2 + 2;
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

                //PRESKOCENIE STREDU
                if (stred.x == x && stred.y == y)
                {
                    continue;
                }

                //PRESKOCENIE SYMULOVANIA Z PREKAZKY
                cords * prekazky = sym->symInfo.svet.prekazky;
                for (int i = 0; i < sym->symInfo.svet.pocetPrekaziek; i++)
                {
                    if (prekazky[i].x == x && prekazky[i].y == y) {
                        continue;
                    }
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

                    if (sym->aktualRep.aktPozicia.x == stred.x &&
                        sym->aktualRep.aktPozicia.y == stred.y) 
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
                    
                    //TODO: ODOMKNI
                    sleep(cas_medzi_krokmi); 
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

   //DEALOCK
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
}