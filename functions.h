#include <stdio.h>
#include <stdlib.h>

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
void play_coord(int* line, char* col, int* size);
int** Create_mask(int size);
int** manual_mask(int size);
void print_pad_mask(int** M, int size);

#endif
