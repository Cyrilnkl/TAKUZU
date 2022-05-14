#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <functions.h>

int** array() {
    int** test = (int**) malloc(6*sizeof (int*));
    for (int i = 0; i < 6; ++i) {
        test[i]= (int*) malloc(6*sizeof(int));
    }
    for (int i = 0; i < 6 ; ++i) {
        for (int j = 0; j <6 ; ++j) {
            if (i>=4|| j>=4)
                test[i][j]=-1;
            else if(i == 0 && j == 0 ||
            i == 0 && j == 3 || i == 1 && j == 0 ||
            i == 1 && j == 2 || i == 2 && j == 1 || i == 2 && j == 3 || i == 3 && j == 1 || i == 3 && j == 2)
                test[i][j] = 0;
            else
                test[i][j] = 1;
        }
    }
    return test;
}
void Menu_principal(int value){
    int choice;
    if (value == 0) {
        printf("====================================================================\n\n"
               "   =======      ==        ==     ==  ==    ==   ======   ==    ==\n"
               "      =       ==  ==      ==    ==   ==    ==      ==    ==    ==\n"
               "      =      == == ==     ==   ==    ==    ==     ==     ==    ==\n"
               "      =     ==      ==    ==     ==     ====     ======     ====\n\n"
               "====================================================================\n\n");
        printf("Hi !\nWelcome in our new game : The TAKUZU !\n");
        printf("\nThere what you can do in my world ! Just ask and admire :p\n  1. Solve a grid\n  2. Automatically solve a grid\n  3. Generate a grid\n\n  -> ");
        scanf("%d", &choice);
    }
    else if (value == 1){
        printf("Here we go again in our new game : The TAKUZU !\nI'm surprise, I thought you might be tired of it");
        printf("\nThere what you can do in my world ! Just ask and admire :p\n  1. Solve a grid\n  2. Automatically solve a grid\n  3. Generate a grid\n\n  -> ");
        scanf("%d", &choice);
    }
    if (choice == 1){
        Menu_second_1();
    }
    else if (choice == 2){
        Menu_second_2();
    }
}

void Menu_second_2(){
    int choice, size, **grid, **mask;
    int ** grid4 = array();
    int ** grid8 = array();
    printf("\n\nWait ! What ?? You're playing on my game and you want to me to work at your place ??\nWhat a world !\n");
    printf("\nPff, enter the size in which you want to play please :\n  1. 4x4\n  2. 8x8\n\n   -> ");
    scanf("%d", &choice);
    if (choice == 1){
        size = 4;
        grid = grid4;
    }
    else{
        size = 8;
        grid = grid8;
    }
    mask = Create_mask(size, grid);
    printf("\n\nThere is your matrice chef ! I will work on it right now !\n\n");
    int** grid_game = print_pad_mask(mask, grid, size);
    auto_fill(grid_game, size);
    printf("\nIT'S COMPLETE !!\n\n");
    display_pad(grid_game, size);
    printf("\n\nYour Game is finish, I hope you took some pleasure by playing.\nTo return to main menu, enter anything pleeeeaaase\n  -> ");
    scanf("%d", &choice);
    Menu_principal(1);
}

void Menu_second_1(){
    int choice, size, **grid;
    int ** grid4 = array();
    int ** grid8 = array();
    printf("\n\nSo you wanna play ?! Let's play !\n");

    printf("\nBut firstly, enter the size in which you want to play please :\n  1. 4x4\n  2. 8x8\n\n   -> ");
    scanf("%d", &choice);
    if (choice == 1){
        size = 4;
        grid = grid4;
    }
    else{
        size = 8;
        grid = grid8;
    }
    printf("\n\nThere what you can do ! Just ask and admire :p\n  1. Enter a mask manually\n  2. Automatically generate a mask\n  3. Play\n\n  -> ");
    scanf("%d", &choice);

    if (choice==1){
        Menu_enter_mask(grid, size);
    }
    else if (choice == 2){
        Menu_auto_mask(grid, size);
    }
    else if (choice == 3){
        play_game_new(grid, size);
    }
}

void play_game_new(int** grid_existant,int size){
    int** mask;
    int choice;
    mask = Create_mask(size, grid_existant);
    play_game(grid_existant, size, mask);
}

void Menu_auto_mask(int** grid_existant, int size){
    int** mask;
    int choice;
    printf("\nWell, you want a mask ? There it is :\n\n");
    mask = Create_mask(size, grid_existant);
    display_pad(mask, size);
    printf("\nWell now ?\n  1. Play this mask with an existant grid\n  2. Return to main menu\n\n  -> ");
    scanf("%d", &choice);
    if (choice == 1){
        play_game(grid_existant, size, mask);
    }
    else if(choice == 2){
        Menu_principal(1);
    }
}

void Menu_enter_mask(int** grid_existant,int size){
    int choice;
    int** mask = create_pad(size + 2);
    printf("\n\nWell, there is your mask : \n\n");
    display_pad(mask, size);
    printf("\n\nThanks ! Now let's fill it !\n\n");
    mask = manual_mask(size);
    printf("\nCongratulations for your mask !\nThere is the matrice which correspond !\n\n");
    print_pad_mask(mask, grid_existant, size);

    printf("\nWhat do you want to do now ?\n  1. Use this mask on an existant grid and play\n  2. Return to main menu\n  -> ");
    scanf("%d", &choice);
    if (choice == 1){
        play_game(grid_existant, size, mask);
    }
    else if (choice == 2){
        Menu_principal(1);
    }
}

void play_game(int** grid_solution, int size, int** mask) {
    int life=3, choice;
    int** grid_game = print_pad_mask(mask, grid_solution, size);
    printf("\n\n\n");
    do {
        play_coord(grid_solution, size, grid_game, &life);
        printf("\nYou have : %d life !\n", life);
    } while ((end_game(grid_game, size) != 0) && (life>0));
    printf("IT'S COMPLETE !!\n");
    display_pad(grid_game, size);
    printf("\n\nYour Game is finish, I hope you took some pleasure by playing.\nTo return to main menu, enter anything pleeeeaaase\n  -> ");
    scanf("%d", &choice);
    Menu_principal(1);
}

int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}

int** create_pad(int size){
    int** L;
    L = (int**) malloc (size*sizeof(int*));
    for (int i=0; i<size+2; i++){
        L[i] = malloc (size*sizeof(int));
    }
    for (int i=0; i<size+2; i++){
        for (int j=0; j<size; j++){
            L[i][j]=-1;
        }
    }
    return L;
}

int** create_pad_test(int size, int** L){
    srand(time(NULL));
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            L[i][j] = rand() % 2;
        }
    }
    return L;
}

int auto_possible(int** solution, int size){
    int answer, number_checked=0;
    int** check=create_pad(size);
    do {
        for (int line=0; line<size; line++){
            for (int col=0; col<size; col++){
                check[line][col]=solution[line][col];
                if (solution[line][col]==-1) {     // Take only empty spaces
                    for (int value=0; value<2; value++) {       // test for 0 and 1
                        answer = return_check_auto(solution, size, col, line, value);        // return of check
                        if (answer != 100){
                            break;
                        }
                    }
                    if (answer==4){
                        solution[line][col]=1;
                    }
                    else if (answer==5){
                        solution[line][col]=1;
                    }
                    else if (answer==1){
                        solution[line][col]=1;
                    }
                    else if (answer==2){
                        solution[line][col]=0;
                    }
                    else if (answer==3){
                        solution[line][col]=0;
                    }
                    else if (answer==0){
                        solution[line][col]=0;
                    }
                }
            }
        }
        number_checked++;
    } while ((number_checked<30) && ((end_game(solution, size) != 0) && (answer != 100)));
    if (answer==100 || number_checked<13){
        return 0;
    }
    return 1;
}


int** copy_pad_mask(int** M, int** L, int size){    /*     A TEST    */
    int** solution;
    solution = create_pad(size+2);
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            if (M[i][j]==1){
                solution[i][j]=L[i][j];
            }
            else{
                solution[i][j]=-1;
            }
        }
    }
    return solution;
}

int** Create_mask(int size, int** L){
    int** M;
    int show_num, number=0;
    M = create_pad(size+2);
    srand(time(NULL));
    do{
        number=0;
        for(int i = 0 ; i < size; i++ ) {
            for (int j = 0; j < size; j++) {
                show_num = rand() % 6;
                if ((show_num == 2) || (show_num == 3)) {
                    M[i][j] = 0;
                } else {
                    M[i][j] = 1;
                    number += 1;
                }
            }
        }
    }while (auto_possible(copy_pad_mask(M, L, size), size) && (number < size*2 && number >((size*2)+3)));
    return M;
}

// générer manuellement  le mask

void display_pad(int** L, int size){
    for (int i=0; i<size; i++){
        printf("[");
        for (int j=0; j<size; j++){
            if ((i>=size) && (j>=size))
                printf("X  ");
            else if (L[i][j]==-1){
                printf("_  ");
            }
            else if ((L[i][j]==1) || (L[i][j]==0)){
                printf("%d  ", L[i][j]);
            }
            else{
                printf("%d  ", L[i][j]);
            }
        }
        printf("]\n");
    }
}

int** manual_mask(int size) {
    int choice, ** M;
    M = create_pad(size+2);
    for(int i = 0 ; i < size; i++ ) {
        for(int j = 0 ; j < size; j++ ) {
            do {
                printf("\nChoose the mask value of the case %d%c -> ",i+1,j+65);
                scanf("%d", &choice);
            }while(choice<0 || choice > 1);
            M[i][j] = choice;
            display_pad(M, size);
        }
    }
    return M;
}



int** print_pad_mask(int** M, int** L, int size){    /*     A TEST    */
    int** solution;
    solution = create_pad(size+2);
    printf("\nThere is your matrice, let's start :\n");
    for (int i=0; i<size; i++){
        printf("[");
        for (int j=0; j<size; j++){
            if (M[i][j]==1){
                solution[i][j]=L[i][j];
                printf("%d  ", solution[i][j]);
            }
            else{
                solution[i][j]=-1;
                printf("_  ");
            }
        }
        printf("]\n\n");
    }
    return solution;
}

void get_size(int* size){
    int temp;
    printf("Which size do you want ?\n  1. 4x4\n  2. 8x8\n-> ");
    scanf("%d", &temp);
    if (temp == 1){
        *size = 4;
    }
    else if (temp == 2){
        *size = 8;
    }
}

int check_valid_off(int** L,int value, int i, int j, int check, int size){
    if ((value==0) && (L[i][size]>=size/2)){
        return 4;
    }
    else if ((value==0) && (L[size][j]>=size/2)){
        return 5;
    }
    else if ((value==1) && (L[i][size+1]>=size/2)){
        return 2;
    }
    else if ((value==1) && (L[size+1][j]>=size/2)){
        return 3;
    }
    if ((i<size && i>0) && (j<size && j>0) && (value == 0) && (L[i-1][j]==0 && L[i+1][j]==0) && (L[i][j-1]==0 && L[i][j+1]==0)){      //vérifie si la case est comprise dans le grand carré [1,n-1] && vérifie s'il est entouré de mêmes valeurs ou non
        return 1;
    }
    else if ((i<size && i>0) && (j<size && j>0) && (value == 1) && (L[i-1][j]==1 && L[i+1][j]==1) && (L[i][j-1]==1 && L[i][j+1]==1)){     //vérifie si la case est comprise dans le grand carré [1,n-1] && vérifie s'il est entouré de mêmes valeurs ou non
        return 0;
    }
    if ((i == 0 || i == size) && (value == 0) && (L[i][j-1]==0 && L[i][j+1]==0)){
        return 1;
    }
    else if ((i == 1 || i == size) && (value == 1) && (L[i][j-1]==1 && L[i][j+1]==1)){
        return 0;
    }
    if ((j == 0 || j == size) && (value == 0) && (L[i][j-1]==0 && L[i][j+1]==0)){
        return 1;
    }
    else if ((j == 1 || j == size) && (value == 1) && (L[i+1][j]==1 && L[i-1][j]==1)){
        return 0;
    }
    if (check==1){
        if ((value == 0) && ((L[i][j-1]==0 && L[i][j-2]==0) || (L[i+1][j]==0 && L[i+2][j]==0) || (L[i][j+1]==0 && L[i][j-1]==0) || (L[i][j+2]==0 && L[i][j+1]==0) || (L[i-1][j]==0 && L[i-2][j]==0) || (L[i-1][j]==0 && L[i+1][j]==0))){
            return 1;
        }
        else if (((L[i][j-2]==1 && L[i][j-1]==1) || (L[i][j+1]==1 && L[i][j-1]==1) || (L[i][j+2]==1 && L[i][j+1]==1) || (L[i-2][j]==1 && L[i-1][j]==1) || (L[i+2][j]==1 && L[i+1][j]==1)) && (value == 1)){
            return 0;
        }
        else return 100;
    }
    else if (check==2){
        if ((value == 0) && ((L[i][j-2]==L[i][j-1]==0) || (L[i][j+2]==L[i][j+1]==0) || (L[i+2][j]==L[i+1][j]==0))) {
            return 1;
        }
        else if ((value == 1) && ((L[i][j-2]==L[i][j-1]==1) || (L[i][j+2]==L[i][j+1]==1) || (L[i+2][j]==L[i+1][j]==1))){
            return 0;
        }
        return 100;
    }
    else if (check==3){
        if ((value == 0) && ((L[i][j-2]==0 && L[i][j-1]==0) || (L[i+2][j]==0 && L[i+1][j]==0))){
            return 1;
        }
        else if ((value == 1) && ((L[i][j-2]==1 && L[i][j-1]==1) || (L[i+2][j]==1 && L[i+1][j]==1))){
            return 0;
        }
        return 100;
    }
    else if (check==4) {
        if ((value == 0) && ((L[i][j - 2] == L[i][j - 1] == 0) || (L[i + 1][j] == L[i - 1][j] == 0) ||
                             (L[i - 2][j] == L[i - 1][j] == 0) || (L[i + 2][j] == L[i + 1][j] == 0))) {
            return 1;
        } else if ((value == 1) && ((L[i][j - 2] == L[i][j - 1] == 1) || (L[i + 1][j] == L[i - 1][j] == 1) ||
                                    (L[i - 2][j] == L[i - 1][j] == 1) || (L[i + 2][j] == L[i + 1][j] == 1))) {
            return 0;
        }
        return 100;
    }
    else if (check==5){
        if ((value == 0) && ((L[i][j-2]==0 && L[i][j-1]==0) && (L[i-2][j]==0 && L[i-1][j]==0))){
            return 1;
        }
        else if ((value == 1) && ((L[i][j-2]==1 && L[i][j-1]==1) && (L[i-2][j]==1 && L[i-1][j]==1))){
            return 0;
        }
        return 100;
    }
    else if (check==6) {
        if ((value == 0) && ((L[i][j - 2] == 0 && L[i][j - 1] == 0) || (L[i - 2][j] == 0 && L[i - 1][j] == 0) ||
                             (L[i][j + 2] == 0 && L[i][j + 1] == 0))) {
            return 1;
        } else if ((value == 1) && ((L[i][j - 2] == 1 && L[i][j - 1] == 1) || (L[i - 2][j] == 1 && L[i - 1][j] == 1) ||
                                    (L[i][j + 2] == 1 && L[i][j + 1] == 1))) {
            return 0;
        }
        return 100;
    }
    else if (check==7){
        if ((value == 0) && ((L[i-2][j]==0 && L[i-1][j]==0) || (L[i][j+2]==0 && L[i][j+1]==0))){
            return 1;
        }
        else if ((value == 1) && ((L[i-2][j]==1 && L[i-1][j]==1) || (L[i][j+2]==1 && L[i][j+1]==1))){
            return 0;
        }
        return 100;
    }
    else if (check==8){
        if ((value == 0) && ((L[i-2][j]==0 && L[i-1][j]==0) || (L[i][j+2]==0 && L[i][j+1]==0) || (L[i+2][j]==0 && L[i+1][j]==0))){
            return 1;
        }
        else if ((value == 1) && ((L[i-2][j]==1 && L[i-1][j]==1) || (L[i][j+2]==1 && L[i][j+1]==1) || (L[i+2][j]==1 && L[i+1][j]==1))){
            return 0;
        }
        return 100;
    }
    else if (check==9){
        if ((value == 0) && ((L[i+1][j]==0 && L[i+2][j]==0) || (L[i][j+2]==0 && L[i][j+1]==0))){
            return 1;
        }
        else if ((value == 1) && ((L[i+1][j]==1 && L[i+2][j]==1) || (L[i][j+2]==1 && L[i][j+1]==1))){
            return 0;
        }
        return 100;
    }
    return 100;
}

void return_check(int** L, int** solution, int size, int col, int line, int value, int *life){
    int return_check=-1;
    if ((line > 1 && line < size-2) && (col > 1 && col < size-2)){
        return_check=check_valid_off(solution, value, line, col, 1, size);
    }
    else if ((line<2) && (col>1 && col< size-2)){
        return_check=check_valid_off(solution, value, line, col, 2, size);
    }
    else if ((line<2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 3, size);
    }
    else if ((line>=2 && line<size-2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 4, size);
    }
    else if ((line>=size-2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 5, size);
    }
    else if ((line>=size-2) && (col>1 && col< size-2)){
        return_check=check_valid_off(solution, value, line, col, 6, size);
    }
    else if ((line>=size-2) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 7, size);
    }
    else if ((line<size-2 && line>1) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 8, size);
    }
    else if ((line<2) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 9, size);
    }

    switch (return_check) {
        case 0:
            printf("There is too much 1 side by side !\n");
            *life-=1;
            break;
        case 1:
            printf("There is too much 0 side by side !\n");
            *life-=1;
            break;
        case 2:
            printf("There is too much 1 in this line !\n");
            *life-=1;
            break;
        case 3:
            printf("There is too much 1 in this column !\n");
            *life-=1;
            break;
        case 4:
            printf("There is too much 0 in this line !\n");
            *life-=1;
            break;
        case 5:
            printf("There is too much 0 in this column !\n");
            *life-=1;
            break;
        default :
            printf("\nIt looks like a valid mouv' !\n");
            solution[line][col]=value;
    }
    if (L[line][col]!=value){
        printf("\n(Hint : it's not a correct move !)\n"); /*mettre sleep*/
    }
}

void update(int** L, int size){
    int Zrow, Orow;
    for (int i=0; i<size; i++){
        Zrow=0, Orow=0;
        for(int j=0; j<size; j++){
            if (L[i][j]==0){
                Zrow++;
            }
            else if (L[i][j]==1){
                Orow++;
            }
        }
        L[i][size]=Zrow;
        L[i][size+1]=Orow;
    }
    int Zcol, Ocol;
    for (int j=0; j<size; j++){
        Zcol=0, Ocol=0;
        for(int i=0; i<size; i++){
            if (L[i][j]==0){
                Zcol++;
            }
            else if (L[i][j]==1){
                Ocol++;
            }
        }
        L[size][j]=Zcol;
        L[size+1][j]=Ocol;
    }
}

int return_check_auto(int** solution, int size, int col, int line, int value){
    int return_check=100;
    if ((line > 1 && line < size-2) && (col > 1 && col < size-2)){
        return_check=check_valid_off(solution, value, line, col, 1, size);
    }
    else if ((line<2) && (col>1 && col< size-2)){
        return_check=check_valid_off(solution, value, line, col, 2, size);
    }
    else if ((line<2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 3, size);
    }
    else if ((line>=2 && line<size-2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 4, size);
    }
    else if ((line>=size-2)&& (col>=size-2)){
        return_check=check_valid_off(solution, value, line, col, 5, size);
    }
    else if ((line>=size-2) && (col>1 && col< size-2)){
        return_check=check_valid_off(solution, value, line, col, 6, size);
    }
    else if ((line>=size-2) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 7, size);
    }
    else if ((line<size-2 && line>1) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 8, size);
    }
    else if ((line<2) && (col<2)){
        return_check=check_valid_off(solution, value, line, col, 9, size);
    }
    return return_check;
}


void manual_clues(int** solution, int size){
    int answer, found=0;
    for (int line=0; line<size; line++) {
        for (int col = 0; col < size; col++) {
            if (solution[line][col] == -1) {     // Take only empty spaces
                for (int value = 0; value < 2; value++) {       // test for 0 and 1
                    answer = return_check_auto(solution, size, col, line, value);        // return of check
                    if (answer != 100) {
                        break;
                    }
                }
                if (answer == 1 || answer == 4 || answer == 5) {
                    if (solution[line][size] == size / 2) {
                        printf("\nCoord : %d%c - > There are too many 0 in this line ! The maximum is %d !\n", line + 1,
                               col + 65, size / 2);
                    } else if (solution[size][col] == size / 2) {
                        printf("\nCoord : %d%c - > There are too many 0 in this column ! The maximum is %d !\n",
                               line + 1,
                               col + 65, size / 2);
                    } else {
                        printf("\nCoord : %d%c - > There are too many 0 side by side ! The maximum is 2 !\n", line + 1,
                               col + 65);
                    }
                    found = 1;
                    solution[line][col] = 1;
                    break;
                } else if (answer == 2 || answer == 3 || answer == 0) {

                    if (solution[line][size + 1] >= size / 2) {
                        printf("\nCoord : %d%c - > There are too many 1 in this line ! The maximum is %d !\n", line + 1,
                               col + 65, size / 2);

                        found = 1;
                    } else if (solution[size + 1][col] >= size / 2) {
                        printf("\nCoord : %d%c - > There are too many 1 in this column ! The maximum is %d !\n",
                               line + 1,
                               col + 65, size / 2);

                        found = 1;
                    } else {
                        printf("\nCoord : %d%c - > There are too many 1 side by side ! The maximum is 2 !\n", line + 1,
                               col + 65);

                        found = 1;
                    }
                }
                if (found==1) {
                    solution[line][col] = 0;
                    break;
                }
            }
            update(solution, size);
        }
        if (found == 1) {
            break;
        }
    }
}


void move_entry_check(int size, int* row, char* col)
{
    char c;
    do
    {
        printf("clue -> '7Z'\n");
        printf("\nEnter row and column:\n -> ");

    } while (((scanf("%d%c%c", row, col, &c)>4 || c!='\n') && clean_stdin()) || (*row<1 || *row>size || *col <'A' || *col >'A'+size-1) && (*row!=7 && *col!='Z'));
}

void play_coord(int** L, int size, int** solution, int *life){
    int row, tempV;
    char col;

    display_pad(solution, size);
    move_entry_check(size, &row, &col);

    if (row==7 && col=='Z'){
        printf("\nLet's give you a clue ! ");
        manual_clues(solution, size);
    }
    else {

        printf("\nWhich value do you want to put ?  -> ");
        scanf("%d", &tempV);
        while ((tempV < 0) || (tempV > 1)) {         /* fonctionne pas pour les lettres !! */
            printf("You can only enter 0 or 1 :\n   -> ");
            scanf("%d", &tempV);
        }
        row = row - 1;
        col -= 65;
        return_check(L, solution, size, col, row, tempV, life);
    }
    update(solution, size);
}

int end_game(int** L, int size){
    int count_num=0, verif=0;
    for (int i=0; i<size; i++){
        for (int j=0; j<size; j++){
            if ((L[i][j]==0) || (L[i][j]==1)){
                count_num++;
            }
        }

    }
    for (int i=0; i<size; i++){
        if ((L[i][size]==size/2) && (L[i][size+1]==size/2)){
            verif++;
        }
    }
    for (int j=0; j<size; j++){
        if ((L[size][j]==size/2) && (L[size+1][j]==size/2)){
            verif++;
        }
    }
    if ((verif==size*2) && (count_num==size*size)){
        return 0;
    }
    return 1;
}

void auto_fill(int** solution, int size){
    int answer, number_check=0;
    do {
        for (int line=0; line<size; line++){
            for (int col=0; col<size; col++){
                if (solution[line][col]==-1) {     // Take only empty spaces
                    if (number_check>100){
                        solution[line][col]=1;
                    }
                    for (int value=0; value<2; value++) {       // test for 0 and 1
                        answer = return_check_auto(solution, size, col, line, value);        // return of check
                        if (answer != 100){
                            break;
                        }
                    }
                    if (answer==4){
                        solution[line][col]=1;
                        printf("\nCoord : %d%c .There are too much 0 in this line !\n", line+1, col+65);
                    }
                    else if (answer==5){
                        solution[line][col]=1;
                        printf("\nCoord : %d%c .There are too much 0 in this column !\n", line+1, col+65);
                    }
                    else if (answer==1){
                        solution[line][col]=1;
                        printf("\nCoord : %d%c .There are too much 0 side by side !\n", line+1, col+65);
                    }
                    else if (answer==2){
                        solution[line][col]=0;
                        printf("\nCoord : %d%c .There are too much 1 in this line !\n", line+1, col+65);
                    }
                    else if (answer==3){
                        solution[line][col]=0;
                        printf("\nCoord : %d%c .There are too much 1 in this column !\n", line+1, col+65);
                    }
                    else if (answer==0){
                        solution[line][col]=0;
                        printf("\nCoord : %d%c .There are too much 1 side by side !\n", line+1, col+65);
                    }
                    update(solution, size);
                    display_pad(solution, size);

                }
            }
        }number_check++;    //truc qui arrete le temps
    } while (end_game(solution, size) != 0);
}