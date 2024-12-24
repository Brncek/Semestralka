#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "symulator.h"


int svetX(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[1];
}

int svetY(sym* sym) {
    return sym->symInfo.svet.rozmerySveta[0];
}

double pravStred(sym * sym, cords cord) {
    if (sym->poctyDosSum[cord.y][cord.x] == 0)
    {
        return 0;
    }

    return (double)sym->poctyDosSum[cord.y][cord.x] / (sym->aktualRep.poradie - 1) * 100; 
}

int priemKrokov(sym * sym, cords cord) {
    if (sym->poctyDlzokSum[cord.y][cord.x] == 0)
    {
        return 0;
    }

    return (int)((double)sym->poctyDlzokSum[cord.y][cord.x] / sym->poctyDosSum[cord.y][cord.x]); 
}

bool jePrekazka(sym * sym, cords cord) {
    
    for (int i = 0; i < sym->symInfo.svet.pocetPrekaziek; i++)
    {
        if (sym->symInfo.svet.prekazky[i].x == cord.x && sym->symInfo.svet.prekazky[i].y == cord.y)
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
    }

    sym->aktualRep.aktPozicia.x = posunCords.x;
    sym->aktualRep.aktPozicia.y = posunCords.y;
    sym->aktualRep.prejdenePolicka[posunCords.y][posunCords.x] = true;
    sym->aktualRep.krok++;
}

//POZOR symulacia ostava alokovana
void symuluj(sym* sym) {
    pthread_mutex_lock(&(sym->symMutex));
    
    for (int y = 0; y < svetY(sym); y++)
    {
        for (size_t x = 0; x < svetX(sym); x++)
        {
            sym->poctyDlzokSum[y][x] = 0; 
            sym->poctyDosSum[y][x] = 0; 
            sym->aktualRep.prejdenePolicka[y][x] = 0;
            sym->aktualRep.poctyDlzok[y][x] = 0;
            sym->aktualRep.poctyDos[y][x] = 0; 
        }
    }

    //PRIPRAVA
    srand(time(NULL));
    sym->aktualRep.poradie = 1;
    

    while (sym->aktualRep.poradie <= sym->symInfo.replikacie)
    {

        //REPLIKACIA
        for (int x = 0; x < svetX(sym); x++)
        {
            for (int y = 0; y < svetY(sym); y++)
            {
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

                bool pokracuj = true;

                while (pokracuj)
                {
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
                    pthread_mutex_unlock(&(sym->symMutex));
                    pthread_cond_broadcast(&(sym->posunCond));
                    sleep(1); 
                    pthread_mutex_lock(&(sym->symMutex));

                    if (sym->koniec) {
                        pthread_mutex_unlock(&(sym->symMutex));
                        pthread_cond_broadcast(&(sym->posunCond));
                        return;
                    }
                }
            }
        }

        //PRIDANIE VYSLEDKOV
        sym->aktualRep.poradie++;
        for (int x = 0; x < svetX(sym); x++)
        {
            for (int y = 0; y < svetY(sym); y++)
            {
                sym->poctyDlzokSum[y][x] += sym->aktualRep.poctyDlzok[y][x];
                sym->poctyDosSum[y][x] += sym->aktualRep.poctyDos[y][x];
            }
        }
    }

    sym->aktualRep.poradie--;
    pthread_mutex_unlock(&(sym->symMutex));
    pthread_cond_broadcast(&(sym->posunCond));
}

void vykresliMapu(sym * sym, zobrazenie zobrazenie, sumZob sumZob) {
    printf("\n");
    if (zobrazenie == SYM_MOD)
    {
        printf("MOD: SYM\n");
    } else {
        if (sumZob == KROKY)
        {
            printf("MOD: SUM-PRIEMERNE KROKY\n");
        } 
        else
        {
            printf("MOD: SUM-PRAVDEPODOBNOST DOSIAHNUTIA\n");
        }
    }
    
    printf("|-------------------------------------------|\n");
    printf("SMERY: HORE: %.2lf DOLE: %.2lf VPRAVO: %.2lf VLAVO: %.2lf\n", 
    sym->symInfo.smeri[0], sym->symInfo.smeri[1], sym->symInfo.smeri[2], sym->symInfo.smeri[3] );
    printf("REPS: %d / %d\n", sym->symInfo.replikacie, sym->aktualRep.poradie);
    printf("Krok: %d / %d\n", sym->symInfo.maxPocetKrokov, sym->aktualRep.krok);
    printf("|-------------------------------------------|\n\n");

    if (zobrazenie == SYM_MOD)
    {
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
                else if (sym->aktualRep.prejdenePolicka[y][x])
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
        if (sumZob == KROKY)
        {
            for (int y = 0; y < svetY(sym); y++)
            {
                for (int x = 0; x < svetX(sym); x++)
                {
                    cords cord;
                    cord.x = x;
                    cord.y = y;

                    printf("[%d]", priemKrokov(sym, cord));
                }
                printf("\n");        
            }
        } 
        else
        {
            for (int y = 0; y < svetY(sym); y++)
            {
                for (int x = 0; x < svetX(sym); x++)
                {
                    cords cord;
                    cord.x = x;
                    cord.y = y;

                    printf("[%.2lf]", pravStred(sym, cord));
                }
                printf("\n");        
            }
        }
    }
    printf("\n");
}