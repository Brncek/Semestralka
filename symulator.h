#pragma once

#include "dataStructures.h"

void symuluj(sym * sym);
void vykresliMapu(sym * sym, zobrazenie zobrazenie, sumZob sumZob);
bool jePrekazka(sym * sym, cords cord);
int svetX(sym* sym);
int svetY(sym* sym);
double pravStred(sym * sym, cords cord);
int priemKrokov(sym * sym, cords cord);