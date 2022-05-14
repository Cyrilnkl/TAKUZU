#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int** create_pad(int size);
void update(int** L, int size);
void invent_pad(int** L, int invent_pad);
void fill_pad(int** L, int size);
void display_pad(int** L, int size);
void Start_game();
void update(int** L, int size);
void get_size(int* size);
void play_coord(int** L, int size, int** solution, int *life);
int** Create_mask(int size, int** L);
int** manual_mask(int size);
int** print_pad_mask(int** M, int** L, int size);
int auto_possible(int** solution, int size);
void return_check(int** L, int** solution, int size, int col, int line, int value, int *life);
int end_game(int** L, int size);
int return_check_auto(int** solution, int size, int col, int line, int value);
void Menu_principal(int value);
void Menu_second_1();
void Menu_enter_mask(int** grid_existant, int size);
void play_game(int** grid_solution, int size, int** mask);
void Menu_auto_mask(int** grid_existant, int size);
void play_game_new(int** grid,int size);
void auto_fill(int** solution, int size);
void Menu_second_2();

#endif
