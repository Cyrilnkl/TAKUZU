
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
    int ** grid8 = array8();
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
    getch();
}
