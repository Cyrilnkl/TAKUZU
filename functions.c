#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** create_pad(int size){
    int** L;
    L = (int**) malloc (size*sizeof(int*));
    for (int i=0; i<size; i++){
        L[i] = malloc (size*sizeof(int));
    }
    return L;
}

void update(int** L, int size){
    for (int i=0; i<size; i++){
        int Lone = 0, Lzero = 0;
        for (int j=0; j<size; j++){
            if (L[i][j]==0){
                Lzero+=1;
            }
            else {
                Lone+=1;
            }
        }
        L[i][size]=Lzero;
        L[i][size+1]=Lone;
    }
    for (int j=0; j<size; j++){
        int Cone = 0, Czero = 0;
        for (int i=0; i<size; i++){
            if (L[i][j]==0){
                Czero+=1;
            }
            else {
                Cone+=1;
            }
        }
        L[size][j]=Czero;
        L[size+1][j]=Cone;
    }
}




void invent_pad(int** L, int reinitialised){
    srand(time(NULL));
    if (reinitialised==1) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                L[i][j] = rand() % 2;
            }
        }
    }
    else{
        for (int i = 1; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                L[i][j] = rand() % 2;
            }
        }
    }
}
void display_pad(int** L, int size){
    for (int i=0; i<size; i++){
        printf("[");
        for (int j=0; j<size; j++){
            if ((i==size-2 || i==size-1) && (j==size-2 || j==size-1))
                printf("X  ");
            else{
                printf("%d  ", L[i][j]);
            }
        }
        printf("]\n");
    }
}

void initialise(int** L, int size){
    for (int i=0; i<size; i++) {
        for (int j = 0; j < size; j++) {
            L[i][j] = 0;
        }
    }
    update(L, size);
}

int plagiat(int** L, int size){
    for (int i=0; i<size/2; i++) {
        for (int k = 1; k < size; k++){
            int nb=0;
            for (int j = 0; j < size; j++) {
                if (L[i][j]==L[i+k][j]){
                    nb+=1;
                }
            }
            if (nb==size){
                printf("plagiat\n");
                return 1;
            }
        }
    }
    return 0;
}

int check_line(int** L, int size, int i){
    for (int j=2; j<(size); j++){
        if (L[i][j-2]==0 && L[i][j-1]==0 && L[i][j]==0){
            return (1);
        }
    }
    return 0;
}

void check(int** L, int size, int check, int i, int j){
    if (check==1){
        if (L[i][size]>size/2) {
            L[i][j] = 1;
            printf("one\n");
        }
        else if (L[i][size+1]>size/2) {
            L[i][j] = 0;
            printf("two");
        }
    }
    else if (check==2) {
        if ((L[i][size]<size/2) && ((L[i][j-1]==L[i][j-2]==1) || (L[i][j+1]==L[i][j+2]==1) || (L[i+1][j]==L[i+2][j]==1) || (L[i-1][j]==L[i-2][j]==1))){
            L[i][j]=0;
        }
        else if ((L[i][size+1]<size/2) && ((L[i][j-1]==L[i][j-2]==0) || (L[i][j+1]==L[i][j+2]==0))){
                L[i][j]=1;
            }
    }
    else if(check==3) {
       if (L[i][size]>size/2) {
           if (L[i][j-1]==1 && L[i][j-2]==1){
               L[i][j]=0;
           }
           else{
               L[i][j]=1;
           }
       }
    }
    else if(check==4) {
        if (i < 2 && j < size/2) {
            if (L[i][size] > size-(size/4)) {
                L[i][j] = 1;
            } else if (L[i][size + 1] > size-(size/4)) {
                L[i][j] = 0;
            }
        }
        if (i<2 && j>=size/2){
            if ((L[i][size] > size/2) || (L[i][j-2]==0 && L[i][j-1]==0)) {
                L[i][j] = 1;
            } else if ((L[i][size + 1] >(size/2)) || (L[i][j-2]==1 && L[i][j-1]==1)) {
                L[i][j] = 0;
            }
        }
    }
}

void fill_pad(int** L, int size){
    for (int i=0; i<2; i++){
        for (int j = 2; j < size; j++) {
            if (size == 4) {
                check(L, size, 1, i, j);
            } else if (size == 8) {
                check(L, size, 4, i, j);
            }
            update(L, size);
        }
        display_pad(L, size+2);
    }
    for (int i=2; i<size/2; i++) {
            for (int j = 0; j < size; j++) {
                if (size == 4) {
                    check(L, size, 1, i, j);
                } else {
                    check(L, size, 3, i, j);
                }
                update(L, size);
        }
    } /*je remplis en mettant l'inverse lol*/
    for (int i=size/2; i<size; i++){
        for (int j=0; j<size; j++){
            if (L[i-size/2][j]==1) {
                L[i][j] = 0;
            }
            else if (L[i-size/2][j]==1){
                L[i][j] = 1;
            }
            else {
                L[i][j] = 1;
            }
        }
    }
}







/*
 * int fill_pad(int** L, int i, int j, int check){
    if (check==1){
        if (L[i][j-2]==L[i][j-1]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i-2][j]==L[i-1][j]==1){
            return 0;
        }
        else if (L[i][j+2]==L[i][j+1]==0){
            return 1;
        }
        else if (L[i][j+2]==L[i][j+1]==1){
            return 0;
        }
        else if (L[i+2][j]==L[i+1][j]==0){
            return 1;
        }
        else if (L[i+2][j]==L[i+1][j]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==2){
        if (L[i][j-2]==L[i][j-1]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i][j+2]==L[i][j+1]==0){
            return 1;
        }
        else if (L[i][j+2]==L[i][j+1]==1){
            return 0;
        }
        else if (L[i+2][j]==L[i+1][j]==0){
            return 1;
        }
        else if (L[i+2][j]==L[i+1][j]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==3){
        if (L[i][j-2]==L[i][j-1]==0){
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i+2][j]==L[i+1][j]==0){
            return 1;
        }
        else if (L[i+2][j]==L[i+1][j]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==4){
        if (L[i][j-2]==L[i][j-1]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i+2][j]==L[i+1][j]==0){
            return 1;
        }
        else if (L[i+2][j]==L[i+1][j]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==5){
        if (L[i][j-2]==L[i][j-1]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==6){
        if (L[i][j-2]==L[i][j-1]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i][j+2]==L[i][j+1]==0){
            return 1;
        }
        else if (L[i][j+2]==L[i][j+1]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==7){
        if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i][j+2]==L[i][j+1]==0){
            return 1;
        }
        else if (L[i][j+2]==L[i][j+1]==1){
            return 0;
        }
        return rand()%2;
    }
    else if (check==8){
        if (L[i-2][j]==L[i-1][j]==0){
            return 1;
        }
        else if (L[i][j-2]==L[i][j-1]==1){
            return 0;
        }
        else if (L[i][j+2]==L[i][j+1]==0){
            return 1;
        }
        else if (L[i][j+2]==L[i][j+1]==1){
            return 0;
        }
        else if (L[i+2][j]==L[i+1][j]==0){
            return 1;
        }
        else if (L[i+2][j]==L[i+1][j]==1){
            return 0;
        }
        return rand()%2;
    }
    return -1;
}


 test 2

 if ((L[i][size] < size / 2) && ((L[i][j - 2] == L[i][j - 1] == 1) || (L[i - 2][j] == L[i - 1][j] == 1) ||
                                        (L[i][j + 2] == L[i][j + 1] == 1) || (L[i + 2][j] == L[i + 1][j] == 1))) {
            L[i][j] = 0;
            printf("three");
        } else if ((L[i][size] < size / 2) && ((L[i][j - 2] == L[i][j - 1] == 0) || (L[i - 2][j] == L[i - 1][j] == 0) ||
                                               (L[i][j + 2] == L[i][j + 1] == 0) ||
                                               (L[i + 2][j] == L[i + 1][j] == 0))) {
            L[i][j] = 1;
            printf("four");
        } else if ((L[i][size + 1] < size / 2) &&
                   ((L[i][j - 2] == L[i][j - 1] == 1) || (L[i - 2][j] == L[i - 1][j] == 1) ||
                    (L[i][j + 2] == L[i][j + 1] == 1) || (L[i + 2][j] == L[i + 1][j] == 1))) {
            L[i][j] = 0;
            printf("three");
        } else if ((L[i][size + 1] < size / 2) &&
                   ((L[i][j - 2] == L[i][j - 1] == 0) || (L[i - 2][j] == L[i - 1][j] == 0) ||
                    (L[i][j + 2] == L[i][j + 1] == 0) || (L[i + 2][j] == L[i + 1][j] == 0))) {
            L[i][j] = 1;
            printf("four");
        } else if (L[i][size] > size / 2) {
            L[i][j] = 1;
            printf("one\n");
        } else if (L[i][size + 1] > size / 2) {
            L[i][j] = 0;
            printf("two");
        } else {
            return;
        }
    }

    for 6X6:

    if (L[i][size]>size/2) {
            if (L[i][j-1]!=L[i][j-2]){
                L[i][j] = 1;
            }
            else if (L[i][j-1]==L[i][j-2]==1){
                L[i][j] = 0;
            }
            else if (L[i][j-1]==L[i][j-2]==0){
                L[i][j] = 1;
            }
            printf("one\n");
        }




        FONCTIONNELLE :

        for (int i=0; i<2; i++){
        int f=0;
        do {
            if (f==1){
                for (int l=0; l<2; l++){
                    for (int z=0; z<2; z++){
                        L[l][z]=0;
                    }
                }
                invent_pad(L, 2);
                printf("reini\n\n\n");
            }
            for (int j = 2; j < size; j++) {
                if (size == 4) {
                    check(L, size, 1, i, j);
                } else if (size == 8) {
                    if (L[0][0]==0 && L[0][1]==0){
                        L[0][2]=1;
                    }
                    if (L[1][0]==0 && L[1][1]==0) {
                        L[1][2] = 1;
                    }
                    display_pad(L, size+2);
                    check(L, size, 3, i, j);
                }
                update(L, size);
            }
            display_pad(L, size+2);
            printf("\nnombre de rep : %d %d\n\n", i, check_line(L, size, i));
            f=check_line(L, size, i);
        }while (f==1);
    }
    int f2=1;
    for (int i=2; i<size/2; i++) {
            for (int j = 0; j < size; j++) {
                if (size == 4) {
                    check(L, size, 1, i, j);
                } else {
                    display_pad(L, size + 2);
                    check(L, size, 3, i, j);
                    printf("\n");
                }
                update(L, size);
        }
    }
 */