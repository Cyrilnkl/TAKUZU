
#include "stdbool.h"
#include "conio.h"
void Menu_principal(int value){
    int choice;
    bool run = true;
    while(run) {
        if (value == 0) {
            printf("====================================================================\n\n"
                   "   =======      ==        ==     ==  ==    ==   ======   ==    ==\n"
                   "      =       ==  ==      ==    ==   ==    ==      ==    ==    ==\n"
                   "      =      == == ==     ==   ==    ==    ==     ==     ==    ==\n"
                   "      =     ==      ==    ==     ==     ====     ======     ====\n\n"
                   "====================================================================\n\n");
            printf("Hi !\nWelcome in our new game : The TAKUZU !\n");
            printf("\nHere is what you can do in my world ! Just ask and admire :p\n  1. Solve a grid\n  2. Automatically solve a grid\n  3. Generate a grid\n\t0. Quit\n\n  -> ");
            scanf("%d", &choice);
        } else if (value == 1) {
            printf("Here we go again in our new game : The TAKUZU !\nI'm surprise, I thought you might be tired of it");
            printf("\nHere is what you can do in my world ! Just ask and admire :p\n  1. Solve a grid\n  2. Automatically solve a grid\n  3. Generate a grid\n\t0. Quit\n\n  -> ");
            scanf("%d", &choice);
        }
        if (choice == 1) {
            Menu_second_1();
            printf("Menu1\n");
            value = 1;
        } else if (choice == 2) {
            Menu_second_2();
            printf("Menu2\n");
            value = 1;
        } else if (choice == 3){
            int** M;
            menu_generation(M);
            value = 1;
        }
        else
            run = false;
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
    getch();
}

void Menu_second_1(){
    int choice, size, **grid;
    int ** grid4 = array();
    int ** grid8 = array8();
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
    printf("\n\nHere is what you can do ! Just ask and admire :p\n  1. Enter a mask manually\n  2. Automatically generate a mask\n  3. Play\n\n  -> ");
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
