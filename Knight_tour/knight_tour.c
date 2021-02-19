#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define BOARD_SIZE 5

int board[BOARD_SIZE][BOARD_SIZE];
int visited[BOARD_SIZE][BOARD_SIZE];
int x_moves[]={2,1,-1,-2,-2,-1, 1, 2};
int y_moves[]={1,2, 2, 1,-1,-2,-2,-1};
int total_squares = BOARD_SIZE * BOARD_SIZE;
int cnt = 0;

bool is_valid(int x, int y, int count, int move){
    //char move[5];
    int i;

    if(x < 0 || y < 0 || x >= BOARD_SIZE || y >= BOARD_SIZE){
        printf("\t%d) ", cnt);
        for(i = 0; i < count; i++){
            printf("-");
        }
        if(move == 0){
            printf("R1.");
        }
        else if(move == 1){
            printf("R2.");
        }
        else if(move == 2){
            printf("R3.");
        }
        else if(move == 3){
            printf("R4.");
        }
        else if(move == 4){
            printf("R5.");
        }
        else if(move == 5){
            printf("R6.");
        }
        else if(move == 6){
            printf("R7.");
        }
        else if(move == 7){
            printf("R8.");
        }
        printf(" U=%d, V=%d. L=%d. Out.\n", x+1, y+1, count);
        return false;
    }
    if(visited[x][y] != -1){
        printf("\t%d) ", cnt);
        for(i = 0; i < count; i++){
            printf("-");
        }
        if(move == 0){
            printf("R1.");
        }
        else if(move == 1){
            printf("R2.");
        }
        else if(move == 2){
            printf("R3.");
        }
        else if(move == 3){
            printf("R4.");
        }
        else if(move == 4){
            printf("R5.");
        }
        else if(move == 5){
            printf("R6.");
        }
        else if(move == 6){
            printf("R7.");
        }
        else if(move == 7){
            printf("R8.");
        }
        printf(" U=%d, V=%d. L=%d. Thread.\n", x+1, y+1, count);
        return false;
    }
    return true;
}

bool solving(int x, int y, int count){
    if(count == total_squares + 1){
        return true;
    }
    int i, next_x, next_y;
    //char move[5];
    for(i = 0; i < 8; i++){
      int move = i;
        next_x = x + x_moves[i];
        next_y = y + y_moves[i];
        cnt++;
        if(is_valid(next_x, next_y, count, i)){
            visited[next_x][next_y] = count;
            printf("\t%d) ", cnt);
            int n;
            for(n = 0; n < count; n++){
                printf("-");
            }
            if(move == 0){
                printf("R1.");
            }
            else if(move == 1){
                printf("R2.");
            }
            else if(move == 2){
                printf("R3.");
            }
            else if(move == 3){
                printf("R4.");
            }
            else if(move == 4){
                printf("R5.");
            }
            else if(move == 5){
                printf("R6.");
            }
            else if(move == 6){
                printf("R7.");
            }
            else if(move == 7){
                printf("R8.");
            }
            printf(" U=%d, V=%d. L=%d. Free. BOARD[%d,%d]:=%d.\n", next_x+1, next_y+1, count, next_x+1, next_y+1, count);

            if(solving(next_x, next_y, count + 1)){
                return true;
            }
            printf("Backtrack\n");
            /* for(k = BOARD_SIZE-1; k >= 0; k--){
                printf("%d)", i);
                for(j = 0; j < BOARD_SIZE; j++){
                    if(visited[k][j] > 9){
                        printf("\t%d", visited[j][k]);
                    }
                    else{
                        printf("\t%d", visited[j][k]);
                    }
                }
                printf("\n");
            } */
            visited[next_x][next_y] = -1;
            //sleep(2);
        }

    }
    return false;
}

int main(int argc, char *argv[]){

    int i, j;
    int initial_x;
    int initial_y;

    if(argc < 3){
        printf("Wrong number of parameters!\n");
        return -1;
    }
    initial_x = atoi(argv[1]);
    initial_y = atoi(argv[2]);
    initial_x = initial_x - 1;
    initial_y = initial_y - 1;

    if(initial_x < 0 || initial_x > BOARD_SIZE || initial_y < 0 || initial_y > BOARD_SIZE){
        printf("Wrong parameters given!\n");
        printf("The initial positions should be less than Board_Size\n");
        return -1;
    }
    for(i = 0; i < BOARD_SIZE; i++){
        for(j = 0; j < BOARD_SIZE; j++){
            board[i][j] = 0;
            visited[i][j] = -1;
        }
    }
    visited[initial_x][initial_y] = 1;
    /* for(i = BOARD_SIZE-1; i >= 0; i--){
        printf("%d)", i+1);
        for(j = 0; j < BOARD_SIZE; j++){
            if(visited[i][j] > 9){
                printf("\t%d", visited[j][i]);
            }
            else{
                printf("\t%d", visited[j][i]);
            }
        }
        printf("\n");
    } */
    printf("PART 1. Data\n");
    printf("\t1) Board %dx%d\n", BOARD_SIZE, BOARD_SIZE);
    printf("\t2) Initial position X=%d, Y=%d. L=1\n", initial_x + 1, initial_y + 1);
    //printf("Part 2. Trace\n");

    if( solving(initial_x, initial_y, 2) ){
        printf("PART 3. Results\n");
        printf("\t1) Path is found. Trials=%d.\n", cnt);
        printf("\t2) Path graphically.\n\n");
        printf("     Y, V ^\n");
        for(i = BOARD_SIZE-1; i >= 0; i--){
            printf("\t%d | ", i+1);
            for(j = 0; j < BOARD_SIZE; j++){
                if(visited[i][j] > 9){
                    printf("\t%d", visited[j][i]);
                }
                else{
                    printf("\t%d", visited[j][i]);
                }
            }
            printf("\n");
        }
        printf("\t  ---------------------------------------------------> X, U\n\t\t");
        for(i = 0; i < BOARD_SIZE; i++){
            printf("%d\t", i+1);
        }
        printf("\n");
    }
    else
    {
        printf("PART 3. Results\n");
        printf("\tNo path found. Trials=%d.\n", cnt);
    }


    return 0;
}
