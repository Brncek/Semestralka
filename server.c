#include <stdio.h>
#include "serverIPC.h"
#include "dataStructures.h"
#include "fileManager.h"

int main(int argc, char const *argv[])
{
    printf("Server spusteni\n");
    sym symData = spust(argv[1]);
    ulozSym(&symData);
    return 0;
}
