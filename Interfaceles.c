//
// Created by eyfel on 13/05/2022.
//


#include "functions.h"
#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "time.h"
#include "conio.h"

//Display all rows that respect Takuzu rule for a given size
void display_all_valid_rows(int size)
{
    //Generation of valid lines
    int decimal_lines_ls;
    int* decimal_lines_list = decimal_line_array(size, &decimal_lines_ls);
    int* binary_code = (int*) malloc(size* sizeof(int ));
    printf("Generating all valid rows. Wait please...\n");
    valid_decimal_numbers(decimal_lines_list, &decimal_lines_ls, size);
    printf("All valid rows generated. Press any key to start grid generation.\n");
    getch();
    //Display of all valid lines

    int cpt = 0;
    int page = 1;
    for (int i = 0; i < decimal_lines_ls; ++i) {
        number2binary(decimal_lines_list[i], size, &size, binary_code);

        //printing all valid row


        for (int j = 0; j < size; ++j) {
            printf("%d",binary_code[j]);
        }
        printf("\n");
        cpt++;


        //If it's needed, multiple pages
        if(cpt == 35*5)
        {
            printf("End of page ");
            printf("%d.",page);
            printf("\n\tPress any key to progress to next page.");
            getch();
            cpt=0;
            page++;
        }

    }
    //Waits for an input to go back to main menu
    printf("Press any key to go back to the menu.\n\n");
    getch();
}

//returns a generated grid and puts success or failure in *created
int** generate_grid(int size, bool* created, bool automatic)
{
    //UI generation

    //Variables
    bool grid_created =0;
    bool escaped = false;
    int** grid = (int**) malloc((size+2) * sizeof(int*));
    int decimal_lines_ls;
    int* decimal_lines_list = decimal_line_array(size, &decimal_lines_ls);
    //Valid rows generation
    if(size == 16 ) {
        printf("16x16 is rather long.");
    }
    if(size != 16 && !automatic)
        printf("Generating all valid rows. Wait please...\n");
    valid_decimal_numbers(decimal_lines_list, &decimal_lines_ls, size);
    if (size != 16 && !automatic) {
        printf("All valid rows generated. Press any key to start grid generation.\n");
        getch();
    }
    if(size == 16)
    {
        printf("\n\tEscape by pressing any key.");
    }
    //Start of grid generation
    while(!grid_created && !escaped) {
        srand(time(NULL));
        int X, used_ls = 0, tested_ls = 0;
        int * used = (int*) malloc(size* sizeof(int));
        int* tested;
        int* binary_code = (int*) malloc(size* sizeof(int ));
        for(int i = 0; i < size+2; i++)
            grid[i] = (int*) malloc((size+2)* sizeof(int));



// First line of the grid randomly chosen
        X = rand() % decimal_lines_ls;
        number2binary(decimal_lines_list[X], size, &size, binary_code);
        add_line(grid[0], binary_code, size);
        used[0] = X;
        used_ls += 1;
        if(size != 16 && !automatic)
            display_grid(grid, size, 1);
        if(size != 16 && !automatic ) {
            printf("First line randomly chosen. Press any key to continue.\n");
            getch();
        }
// Second line onwards loop
        bool line_OK;

        for (int i = 1; i < size; i++) {
            if( size != 16 && !automatic) {
                printf("Choosing line ");
                printf("%d:\n", i + 1);
            }

            // Fresh and sorted tested array for each loop
            tested = (int *) malloc(decimal_lines_ls * sizeof(int));
            for (int j = 0; j < used_ls; j++)
                tested[j] = used[j];
            tested_ls = used_ls;
            selection_sorting(tested, tested_ls);

            //Grid construction
            line_OK = 0;
            while (tested_ls != decimal_lines_ls && !line_OK)
            {

                if(size == 16 && kbhit())
                {
                    escaped = true;
                    break;
                }
                //Chooses random number that has not been used or tested in the grid
                do {
                    X = rand() % decimal_lines_ls;
                } while (dichotomic_search(X, tested, tested_ls) >= 0);
                number2binary(decimal_lines_list[X], size, &size, binary_code);
                add_line(grid[i], binary_code, size);


                // Checks if Takuzu rules are respected, and if so, validate the line as used

                    if (!check_column(grid, size, i + 1)) {
                        add_ascending_order(X, tested, &tested_ls);
                    }

                    else {
                        line_OK = 1;
                        used[i] = X;
                        used_ls += 1;
                        //Display
                        if (size != 16 && !automatic) {
                            display_grid(grid, size, i + 1);
                            display_tested(decimal_lines_list, tested, tested_ls);
                            display_used(decimal_lines_list, used, used_ls);
                        }
                        free(tested);
                        tested = NULL;
                        tested_ls = 0;
                        if(size !=16 && !automatic) {
                            printf("Press any key to start next line.\n\n");
                            getch();
                        }
                    }




            }
            //If the grid is impossible to complete or 16x16 is taking too long
            if (!line_OK || escaped){
                //printf("F\n");
                break;
            }
        }
//If there's no solution for the next line, redo grid from scratch, else finish grid
        if(escaped)//Only in 16x16
        {
            *created = false;
        }
        else if(!line_OK || !check_same_column(grid, size))
        {
            free(tested); free(used);
            tested_ls = 0; used_ls = 0;
            for(int i = 0; i < size+2; i++)
                free(grid[i]);
            if(size != 16 && !automatic) {
                printf("Invalid grid, press any key for next generation.\n\n");
                getch();
            }
        }
        else {
            grid_created = 1;
            free(used);
            //free(binary_code);
            free(tested);
            *created = true;
            if(!automatic){
                printf("Grid created!\n\n");
                getch();
            }
        }
    }

    return grid;
}

//Full menu + puts the generated matrix inside given pointer and returns confirmation of creation
bool menu_generation(int**full_grid)
{
    int input, size;
    bool created;
    printf("\n======= Generation =======\n");
    printf("What do you want to do ?\n");
    printf("    1. Display all valid rows\n");
    printf("    2. Generate a grid\n");
    printf("        0. Back\n\n  ->");
    other_entry_check(&input, 0, 2);
    if(input)
        Get_size(&size);
    if(input == 1)
    {
        display_all_valid_rows(size);
    }
    else if(input == 2)
    {
        full_grid = generate_grid(size, &created, false);
        return created;
    }
}

//printd and reads the size of the grid
void Get_size(int * size)
{
    int input;
    printf("\n======= Size =======\n");
    printf("Which size ?\n");
    printf("    1. 4x4\n");
    printf("    2. 8x8\n");
    printf("    3. 16x16\n");
    printf("  ->");
    other_entry_check(&input, 1, 3);
    *size = pow(2, input+1);
}
//Display all the tested valid line numbers when generating a grid
void display_tested(int* valid_lines, int* tested, int tested_size)
{
    printf("Tested valid lines: ");
    for (int i = 0; i < tested_size; ++i) {
        printf("%d ", valid_lines[tested[i]]);
    }
    printf("\n");
}

//Display all the used line numbers when generating a grid
void display_used(int*valid_lines, int* used, int used_size)
{
    printf("Used valid lines: ");
    for (int i = 0; i < used_size; ++i) {
        printf("%d ", valid_lines[used[i]]);
    }
    printf("\n");
}

//Displays the incomplete or complete grid
void display_grid(int** M, int size, int nb_line)
{

    printf(" ");
    for(int i = 0; i < size; i++)
    {
        printf("   %c", 65+i);
    }
    printf("\n");
    for (int i = 0; i < nb_line; ++i) {
        printf("%d", i+1);
        for (int j = 0; j < size; ++j) {
            printf("   %d", M[i][j]);
        }
        printf("\n");
    }
}



//returns array with all numbers. max of 2^size
int* decimal_line_array(int size, int * arr_size)
{
    *arr_size = pow(2, size) - pow(2, size-3);
    int* arr = (int*) malloc(*arr_size * sizeof(int));
    for(int i = 0; i < *arr_size; i++)
        *(arr+i) = pow(2, size-3)+i;
    return arr;
}

//Returns 0 if there is more than 2 of the same number in a row in a line
int check_row_two_or_less(int* L, int size) {
    for (int j = 2; j < (size); j++) {
        if (L[j - 2] == L[j - 1] && L[j - 1]== L[j]) {
            return 0;
        }
    }
    return 1;
}

//Returns 0 if there is more than 2 of the same number in a row in a column
int check_column_two_or_less(int** M, int size, int nb_line)
{
    for(int i = 0; i < size; i++) {
        for (int j = 2; j < nb_line; j++) {
            if (M[j - 2][i] == M[j - 1][i] && M[j - 1][i] == M[j][i])
                return 0;
        }
    }
    return 1;
}

//Returns 0 if there is more than half of the size of a number in a line
int check_number_in_row(int *L, int size)
{
    int number_0 = 0, number_1 = 0;
    for(int i =0; i < size; i++ )
    {
        if(L[i])
            number_1 += 1;
        else
            number_0 += 1;
        if(number_0 > size/2 || number_1 > size/2)
            return 0;
    }
    return 1;
}

//Returns 0 if there is more than half of the size of a number in a column
int check_number_in_column(int** M, int size, int nb_line)
{
    int number_0, number_1;
    for(int i = 0; i < size; i++){
        number_0 = 0; number_1 = 0;
        for(int j = 0; j < nb_line; j++)
        {
            if(M[j][i])
                number_1 += 1;
            else
                number_0 += 1;
            if(number_0 > size/2 || number_1 > size/2)
                return 0;
        }
    }
    return 1;
}

//Returns 0 if the previous row condition aren't met
int check_row(int* L, int size)
{
    if(check_row_two_or_less(L, size) && check_number_in_row(L, size))
        return 1;
    return 0;

}

//Returns 0 if the previous column condition aren't met
int check_column(int** M, int size, int nb_line)
{
    if(check_column_two_or_less(M, size, nb_line) && check_number_in_column(M, size, nb_line))
        return 1;
    return 0;
}

//Returns 0 two columns are the same
bool check_same_column(int**M, int size)
{
    for(int i = 0; i < size-1; i++)
        for(int j = i+1; j < size; j++) {
            int check = 0;
            for (int k = 0; k < size; k++) {
                if (M[k][i] == M[k][j])
                    check += 1;
                else
                    break;
            }
            if(check == size) {
                return 0;
            }
        }
    return 1;
}

//To avoid an infinite loop if the user inputs the wrong type
int clean_stdin()
{
    while (getchar()!='\n');
    return 1;
}


//Checks all other inputs
void other_entry_check(int* input, int low_bound, int high_bound)
{
    char c;
    while (((scanf("%d%c", input, &c)> 3  || c!='\n') && clean_stdin()) || *input < low_bound || *input > high_bound )
    {
        printf("Invalid input.\n");
    }
}

//Takes a decimal number and returns an array with its binary code
int number2binary(double nb, int size, int* original_size, int* binary)
{
    if(size < 0)
        return 0;
    if (nb - pow(2, size-1) >= 0) {
        *(binary + *original_size - size) = 1;
        number2binary(nb - pow(2, size-1), size-1, original_size,  binary);
    }
    else {
        *(binary + *original_size - size) = 0;
        number2binary(nb, size-1, original_size, binary);
    }
}

//Search a value through an array
int dichotomic_search(int searched, int* array, int ls)
{
    int low = 0, middle, high, pos;
    bool stop = 0;
    high = ls-1;
    while(low <= high) {
        middle = (high + 1 / 2);
        if (searched == array[middle])
            return middle;
        else{
            if(searched > array[middle])
                low = middle + 1;
            else
                high = middle - 1;
        }
    }
    return -1;
}

//Sorts an array in ascending order
void selection_sorting(int* array, int ls)
{
    int temp, min;
    for(int i = 0; i < ls -1; i++)
    {
        min = i;
        for(int j = i+1; j < ls; j++)
        {
            if(array[j] < array[min])
                min = j;
        }
        if(min != i)
        {
            temp = array[i];
            array[i] = array[min];
            array[min] = temp;
        }
    }
}

//Adds val at the right place to conserve ascending order
void add_ascending_order(int val, int* array, int* ls)
{
    int i = 0;
    while(i < *ls && val > array[i])
        i++;
    if (i != *ls)
        for(int j = *ls; j > i; j--)
        {
            array[j] = array[j-1];
        }
    array[i] = val;
    *ls += 1;
}

//Deletes all numbers that would be invalid lines
void valid_decimal_numbers(int* array, int* ls, int size )
{
    int *binary_code = (int *) malloc(size * sizeof(int));
    for(int i = 0; i < *ls; i++) {
        number2binary(array[i], size, &size, binary_code);
        if (!check_row(binary_code, size))
        {
            for(int j = i; j < *ls-1; j++)
                array[j] = array[j+1];
            *ls -= 1;
            i--;
        }
    }
}

//Adds a line to the grid
void add_line (int* grid_line, int* added_line, int size)
{
    for(int i = 0; i < size; i++)
    {
        grid_line[i] = added_line[i];
    }
}


//Cyril


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
            value = 1;
        } else if (choice == 2) {
            Menu_second_2();
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
    printf("\n\nYour Game is finish, I hope you took some pleasure by playing.\nTo return to main menu, enter anything pleeeeaaase\n  ->\n\n ");
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

int** print_pad_mask(int** M, int** L, int size){
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
                    printf("\n");

                }
            }
        }number_check++;    //truc qui arrete le temps
    } while (end_game(solution, size) != 0);
}




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

int** array8() {
    int** test = (int**) malloc(10*sizeof (int*));
    for (int i = 0; i < 10; ++i) {
        test[i]= (int*) malloc(10*sizeof(int));
    }
    for (int i = 0; i < 10 ; ++i) {
        for (int j = 0; j <10 ; ++j) {
            if (i>=8|| j>=8)
                test[i][j]=-1;
            else if(i == 0 && j == 0 || i == 0 && j == 2 || i == 0 && j == 3 || i == 0 && j == 5 ||
                    i == 1 && j == 0 || i == 1 && j == 2 || i == 1 && j == 4 || i == 1 && j == 7 ||
                    i == 2 && j == 1 || i == 2 && j == 3 || i == 2 && j == 4 || i == 2 && j == 6 ||
                    i == 3 && j == 1 || i == 3 && j == 3 || i == 3 && j == 5 || i == 3 && j == 6 ||
                    i == 4 && j == 0 || i == 4 && j == 2 || i == 4 && j == 5 || i == 4 && j == 7 ||
                    i == 5 && j == 1 || i == 5 && j == 4 || i == 5 && j == 6 || i == 5 && j == 7 ||
                    i == 6 && j == 2 || i == 6 && j == 3 || i == 6 && j == 5 || i == 6 && j == 6 ||
                    i == 7 && j == 0 || i == 7 && j == 1 || i == 7 && j == 4 || i == 7 && j == 7 )
                test[i][j] = 1;
            else
                test[i][j] = 0;
        }
    }
    return test;
}

int** array16() {
    int** test = (int**) malloc(18*sizeof (int*));
    for (int i = 0; i < 18; ++i) {
        test[i]= (int*) malloc(18*sizeof(int));
    }
    for (int i = 0; i < 18 ; ++i) {
        for (int j = 0; j <18 ; ++j) {
            if (i>=16|| j>=16)
                test[i][j]=-1;
            else if(i == 0 && j == 0 || i == 0 && j == 2 || i == 0 && j == 3 || i == 0 && j == 5 ||
                    i == 0 && j == 7 || i == 0 && j == 10 || i == 0 && j == 12 || i == 0 && j == 14 ||
                    i == 1 && j == 2 || i == 1 && j == 3 || i == 1 && j == 5 || i == 1 && j == 6 ||
                    i == 1 && j == 9 || i == 1 && j == 11 || i == 1 && j == 13 || i == 1 && j == 15 ||
                    i == 2 && j == 1 || i == 2 && j == 4 || i == 2 && j == 6 || i == 2 && j == 8 ||
                    i == 2 && j == 9 || i == 2 && j == 12 || i == 2 && j == 13 || i == 2 && j == 15 ||
                    i == 3 && j == 0 || i == 3 && j == 1 || i == 3 && j == 4 || i == 3 && j == 7 ||
                    i == 3 && j == 8 || i == 3 && j == 10 || i == 3 && j == 11 || i == 3 && j == 14 ||
                    i == 4 && j == 2 || i == 4 && j == 3 || i == 4 && j == 5 || i == 4 && j == 6 ||
                    i == 4 && j == 9 || i == 4 && j == 11 || i == 4 && j == 13 || i == 4 && j == 14 ||
                    i == 5 && j == 0 || i == 5 && j == 1 || i == 5 && j == 4 || i == 5 && j == 6 ||
                    i == 5 && j == 8 || i == 5 && j == 10 || i == 5 && j == 12 || i == 5 && j == 15 ||
                    i == 6 && j == 1 || i == 6 && j == 2 || i == 6 && j == 5 || i == 6 && j == 7 ||
                    i == 6 && j == 8 || i == 6 && j == 11 || i == 6 && j == 12 || i == 6 && j == 14 ||
                    i == 7 && j == 0 || i == 7 && j == 3 || i == 7 && j == 5 || i == 7 && j == 6 ||
                    i == 7 && j == 9 || i == 7 && j == 10 || i == 7 && j == 13 || i == 7 && j == 15 ||
                    i == 8 && j == 2 || i == 8 && j == 4 || i == 8 && j == 6 || i == 8 && j == 7 ||
                    i == 8 && j == 9 || i == 8 && j == 11 || i == 8 && j == 12 || i == 8 && j == 15 ||
                    i == 9 && j == 1 || i == 9 && j == 2 || i == 9 && j == 5 || i == 9 && j == 7 ||
                    i == 9 && j == 8 || i == 9 && j == 10 || i == 9 && j == 13 || i == 9 && j == 14 ||
                    i == 10 && j == 0 || i == 10 && j == 3 || i == 10 && j == 4 || i == 10 && j == 6 ||
                    i == 10 && j == 8 || i == 10 && j == 9 || i == 10 && j == 12 || i == 10 && j == 15 ||
                    i == 11 && j == 0 || i == 11 && j == 1 || i == 11 && j == 4 || i == 11 && j == 7 ||
                    i == 11 && j == 9 || i == 11 && j == 11 || i == 11 && j == 14 || i == 11 && j == 15 ||
                    i == 12 && j == 2 || i == 12 && j == 3 || i == 12 && j == 5 || i == 12 && j == 7 ||
                    i == 12 && j == 8 || i == 12 && j == 10 || i == 12 && j == 11 || i == 12 && j == 13 ||
                    i == 13 && j == 1 || i == 13 && j == 2 || i == 13 && j == 4 || i == 13 && j == 6 ||
                    i == 13 && j == 9 || i == 13 && j == 10 || i == 13 && j == 12 || i == 13 && j == 13 ||
                    i == 14 && j == 0 || i == 14 && j == 3 || i == 14 && j == 5 || i == 14 && j == 8 ||
                    i == 14 && j == 11 || i == 14 && j == 12 || i == 14 && j == 14 || i == 14 && j == 15 ||
                    i == 15 && j == 0 || i == 15 && j == 1 || i == 15 && j == 3 || i == 15 && j == 4 ||
                    i == 15 && j == 7 || i == 15 && j == 10 || i == 15 && j == 13 || i == 15 && j == 14 )
                test[i][j] = 1;
            else
                test[i][j] = 0;
        }
    }
    return test;
}