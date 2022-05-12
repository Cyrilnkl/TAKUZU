#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int Menu(){
    printf("What do you want to do ?\n  -> Enter a mask manually\n  -> Automatically generate a mask\n  -> Play");
    return(0);
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

int** Create_mask(int size){
    int** M;
    int show_num, number=0;
    M = create_pad(size+2);
    srand(time(NULL));
    while ((number<(size*size/2))){
        for(int i = 0 ; i < size; i++ ) {
            for (int j = 0; j < size; j++) {
                show_num = rand() % 6;
                if ((show_num != 2) && (show_num != 3)) {
                    M[i][j] = 0;
                } else {
                    M[i][j] = 1;
                    number+=1;
                }
            }
        }
    }
    return M;
}

// générer manuellement  le mask

void display_pad(int** L, int size){
    for (int i=0; i<size+2; i++){
        printf("[");
        for (int j=0; j<size+2; j++){
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
    printf("There is your matrice :\n");
    for (int i=0; i<size; i++){
        printf("[");
        for (int j=0; j<size; j++){
            if (M[i][j]==1){
                solution[i][j]=L[i][j];
                printf("%d  ", solution[i][j]);
            }
            else{
                printf("_  ");
            }
        }
        printf("]\n");
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

void return_check(int** L, int** solution, int size, int col, int line, int value){
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

    printf("%d",return_check);
    switch (return_check) {
        case 0:
            printf("There is too much 1 side by side !\n");
            break;
        case 1:
            printf("There is too much 0 side by side !\n");
            break;
        case 2:
            printf("There is too much 1 in this line !\n");
            break;
        case 3:
            printf("There is too much 1 in this column !\n");
            break;
        case 4:
            printf("There is too much 0 in this line !\n");
            break;
        case 5:
            printf("There is too much 0 in this column ! !\n");
            break;
        default :
            printf("\nIt looks like a valid mouv' !\n");
            solution[line][col]=value;
    }
    if (L[line][col]!=value){
        printf("(Hint : it's not a correct mouv' ! %d and %d\n", L[line][col], value);
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

void play_coord(int** L, int size, int** solution){  /* Cette fonction récupère la ligne et la colone que le joeur souhaite remplir */
    /*ON A BESOIN D'INTRODUIRE LA MATRICE FINALE SOIT CELLE DU JOUEUR SOIT LA GENERE !!*/
    int row, tempV, life = 3;
    char col, c;

    display_pad(solution, size);
    do
    {
        printf("Enter row and column:");

    } while (((scanf("%d%c%c", &row, &col, &c)>4 || c!='\n') && clean_stdin()) || row<1 || row>size || col <'A' || col >'A'+size-1);
    printf("\nWhich value do you want to put ?  -> ");
    scanf("%d", &tempV);
    while ((tempV<0) || (tempV>1)){         /* fonctionne pas pour les lettres !! */
        printf("You can only enter 0 or 1 :\n   -> ");
        scanf("%d", &tempV);
    }
    row=row-1;
    col-=65;
    /* check_valid(tempC-65)*/
    printf("ook\n");
    return_check(L, solution, size, col, row, tempV);
    update(L, size);
}

int end_game(int** L, int size){
    int count_num=0, verif=1;
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
        if ((L[size][j]==size/2) && (L[size][j+1]==size/2)){
            verif++;
        }
    }
    if ((verif==size*2) && (count_num==size*size)){
        return 0;
    }
    return 1;
}

void Start_game() {
    int **L, **M, **solution, size, line;
    char col;
    get_size(&size);
    L = create_pad(size + 2);
    L = create_pad_test(size, L);
    M = Create_mask(size);
    display_pad(M, size);
    solution = print_pad_mask(M, L, size);
    printf("Ça commence \n\n");
    do {
        play_coord(L, size, solution);
        printf("\n");
    } while (end_game(L, size) != 0);
    if (L[0][0] == 1) {
        printf("hey");
    }
}