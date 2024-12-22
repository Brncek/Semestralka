#include <stdio.h>
#include <stdlib.h>

#include "dataStructures.h"
#include "fileManager.h"
#include "debugTests.h"
#include "symulator.h"
#include "klientIPC.h"

symInfo novaSymulaciaDialog() {
    int odpoved;
    symInfo symInfo;

    printf("Replikacie: ");
    scanf("%d", &odpoved);
    if (odpoved < 1)
    {
        printf("Nespravny pocet replikacii\n");
        exit(0);
    }
    symInfo.replikacie = odpoved;

    printf("Max pocet krokov: ");
    scanf("%d", &odpoved);
    if (odpoved < 1)
    {
        printf("Nespravny pocet krokov\n");
        exit(0);
    }
    symInfo.maxPocetKrokov = odpoved;

    printf("ulozenie symulacie: ");
    scanf("%255s", symInfo.ulozenie);

    printf("Zadavaju sa iba 3 posledna sa dopocita sama\n");
    printf("pravdepodobnosti smerov H D P L: ");
    float smeri[4];
    scanf("%f %f %f", &smeri[0], &smeri[1], &smeri[2]);
    smeri[3] = 1 - smeri[0] - smeri[1] - smeri[2];

    for (size_t i = 0; i < 4; i++)
    {
        if (smeri[i] < 0)
        {
            printf("Smer nesmie byt zaporny\n");
            exit(0);
        }

        if (smeri[i] > 1)
        {
            printf("Smer nesmie byt vecsi ako 1\n");
            exit(0);
        }
        symInfo.smeri[i] = smeri[i];
    }


    printf("Typ sveta \n");
    printf("1: prazdny\n");
    printf("2: prekazky\n");
    printf("> ");
    scanf("%d", &odpoved);
    switch (odpoved)
    {
    case 1:
        svet svet;
        printf("Zadaj sirku a vysku (minimum 5): ");
        scanf("%d %d", &svet.rozmerySveta[1], &svet.rozmerySveta[0]);
        if (svet.rozmerySveta[0] < 5 || svet.rozmerySveta[1] < 5) 
        {
            printf("Nespravne rozmery\n");
            exit(0);
        }
        svet.pocetPrekaziek = 0;
        symInfo.svet = svet;
        break;
    case 2:
        printf("Zadaj mapu: ");
        char nazovSuboru[256];
        scanf("%255s", nazovSuboru);
        symInfo.svet = nacitajSvet(nazovSuboru);
        break;
    
    default:
        printf("Neznami vstup\n");
        exit(0);
        break;
    }

    return symInfo;
}

symInfo znovuSymulaciaDialog() {
    int replikacie;
    printf("Replikacie: ");
    scanf("%d", &replikacie);
    if (replikacie < 1)
    {
        printf("Nespravny pocet replikacii\n");
        exit(0);
    }

    char odpovedCesta[256];
    printf("simulacia cesta: ");
    scanf("%255s", odpovedCesta);

    symInfo symInfo = nacitajSymulaciu(odpovedCesta);
    symInfo.replikacie = replikacie;

    printf("ulozenie symulacie: ");
    scanf("%255s", symInfo.ulozenie);

    return symInfo;
}

int mainMenu() {
    printf("Menu vyber \n");
    printf("1: nova symulacia\n");
    printf("2: pripojenie k simulacii\n");
    printf("3: znovuspustenie symulacie\n");
    printf("4: koniec\n");
    printf("> ");
    int odpoved;
    scanf("%d", &odpoved);
    return odpoved;
}

void novaSymulacia() {
    char popisovac[7];
    symInfo symInfo = novaSymulaciaDialog();
    spustServer(popisovac, symInfo);
    pripojNaServer(popisovac);
}

void pripojenie() {
    char odpovedCesta[256];
    printf("popisovac: ");
    scanf("%255s", odpovedCesta);
    pripojNaServer(odpovedCesta);
}

void znovuspustenie() {
    char popisovac[7];
    symInfo symInfo = znovuSymulaciaDialog();
    spustServer(popisovac, symInfo);
    pripojNaServer(popisovac);
}

int main()
{
    printf("\n");
    int menuOdpoved = mainMenu();

    switch (menuOdpoved)
    {
    case 1: 
        novaSymulacia();
        break;
    case 2: 
        pripojenie();
        break;
    case 3: 
        znovuspustenie();
        break;
    case 4: 
        printf("koniec\n");
        break;
    default:
        printf("Neznama akcia\n");
        break;
    }

    return 0;
}
