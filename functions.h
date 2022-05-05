#include <stdio.h>
#include <stdlib.h>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

int** create_pad(int size);
void update(int** L, int size);
void invent_pad(int** L, int invent_pad);
void fill_pad(int** L, int size);
void display_pad(int** L, int size);
void check(int** L, int size, int check, int i, int j);
int plagiat(int** L, int size);
void initialise(int** L, int size);

#endif
