#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    int size, **L, k=0;
    printf("Which size do you want ?");
    scanf("%d", &size);
    L = create_pad(size+2);
    printf("1\n");
    update(L, size);
    display_pad(L, size+2);
    printf("2\n");
    display_pad(L, size+2);
    printf("cp2\n");
    invent_pad(L, 1);
    update(L, size);
    display_pad(L, size+2);
    printf("cp3\n");
    fill_pad(L, size);
    update(L, size);
    display_pad(L, size+2);
}


/*do{
printf("CP");
display_pad(L, size+2);
printf("cp2");
invent_pad(L);
update(L, size);
fill_pad(L, size);
update(L, size);
k++;
}while (plagiat(L, size)!=0);*/