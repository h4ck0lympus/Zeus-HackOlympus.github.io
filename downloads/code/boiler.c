#include <stdio.h>
#include <stdlib.h>

int main() 
{
    srand(0x11C4) ;

    printf(" %d \n",rand()  ^ rand() ^ 0x3597B741) ; 
    return 0 ; 
}
