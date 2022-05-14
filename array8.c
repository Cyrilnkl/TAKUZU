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
