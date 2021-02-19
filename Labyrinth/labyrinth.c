#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define width 7
#define height 8

int labyrinth [width][height];
int x_moves[] = { 0, 0,-1, 1};
int y_moves[] = {-1, 1, 0, 0};
int counter = 2;

bool find_path(int x, int y, int trial){

    int next_x, next_y;
    int i, j, k;
    //printf("trial: %d\n", trial);

    if(x == 0 || x == width || y == 0 || y == height){
        return true;
    }

    for(i = 0; i < 4; i++){
        next_x = x + x_moves[i];
        next_y = y + y_moves[i];

        if(labyrinth[next_x][next_y] == 0){
            trial++;
            counter++;
            labyrinth[next_x][next_y] = counter;

            // printf("***********************************************************\n");
            // for(k = width -1 ; k >= 0; k--){
            //     for(j = 0; j < height; j++){
            //         if(labyrinth[k][j] < 0){
            //             printf("\t%d", labyrinth[k][j]);
            //         }
            //         else{
            //             printf("\t %d", labyrinth[k][j]);
            //         }
            //     }
            //     printf("\n");
            // }
            //printf("\t%d)", );
            if(!find_path(next_x, next_y, trial)){
                counter--;
                labyrinth[next_x][next_y] = -1;
            }
            else{
                return true;
            }
        }
    }

    return false;
}

int main(int argc, char * argv[]){

    int initial_x;
    int initial_y;
    int i, j;
    int trial = 0;
    //int fd;
    //int number = 0;
    //char *bf;


    if(argc != 3){
        printf("Not enough parameters\n");
        return -1;
    }

    /* fd = open("labyrinth.txt", O_RDONLY);

    initial_x = atoi(argv[1]);
    initial_y = atoi(argv[2]);
    if(initial_x +1 <= 0 || initial_x +1 > width || initial_y +1  <= 0 || initial_y +1  > height){
        printf("Wrong parameters\n");
        return -1;
    }

    for(i = 0; i < width; i++){
        for(j = 0; j < height; j++){
            labyrinth[i][j] = 0;
        }
    }

    printf("edo\n");
    for(i = 0; i < width; i++){
        for(j = 0; j < height; j++){
            read(fd, bf, 1);
            number = atoi(bf);
            printf("number : %d\n", number);
            labyrinth[i][j] = number;
        }
    }

    for(i = width-1 ; i >= 0; i--){
        for(j = 0; j < height; j++){
            if(labyrinth[i][j] > 9){
                printf("\t%d", labyrinth[j][i]);
            }
            else{
                printf("\t%d", labyrinth[j][i]);
            }
        }
        printf("\n");
    } */

    labyrinth[0][0]= 1;
    labyrinth[0][1]= 1;
    labyrinth[0][2]= 1;
    labyrinth[0][3]= 1;
    labyrinth[0][4]= 1;
    labyrinth[0][5]= 1;
    labyrinth[0][6]= 1;

    labyrinth[1][0]= 1;
    labyrinth[1][1]= 0;
    labyrinth[1][2]= 0;
    labyrinth[1][3]= 1;
    labyrinth[1][4]= 1;
    labyrinth[1][5]= 0;
    labyrinth[1][6]= 1;

    labyrinth[2][0]= 1;
    labyrinth[2][1]= 0;
    labyrinth[2][2]= 1;
    labyrinth[2][3]= 1;
    labyrinth[2][4]= 0;
    labyrinth[2][5]= 0;
    labyrinth[2][6]= 1;

    labyrinth[3][0]= 1;
    labyrinth[3][1]= 0;
    labyrinth[3][2]= 0;
    labyrinth[3][3]= 0;
    labyrinth[3][4]= 0;
    labyrinth[3][5]= 1;
    labyrinth[3][6]= 1;

    labyrinth[4][0]= 1;
    labyrinth[4][1]= 1;
    labyrinth[4][2]= 1;
    labyrinth[4][3]= 1;
    labyrinth[4][4]= 0;
    labyrinth[4][5]= 1;
    labyrinth[4][6]= 1;

    labyrinth[5][0]= 0;
    labyrinth[5][1]= 0;
    labyrinth[5][2]= 0;
    labyrinth[5][3]= 0;
    labyrinth[5][4]= 0;
    labyrinth[5][5]= 0;
    labyrinth[5][6]= 0;

    labyrinth[6][0]= 1;
    labyrinth[6][1]= 1;
    labyrinth[6][2]= 1;
    labyrinth[6][3]= 1;
    labyrinth[6][4]= 1;
    labyrinth[6][5]= 0;
    labyrinth[6][6]= 1;



    initial_x = atoi(argv[2]);
    initial_x = initial_x - 1;
    initial_y = atoi(argv[1]);
    initial_y = initial_y - 1;
    if(initial_x < 0 || initial_x >= width || initial_y < 0 || initial_y >= height){
        printf("Wrong parameters!\n");
        return -1;
    }
    labyrinth[initial_x][initial_y] = counter;
    printf("PART 1. Data\n");
    printf("\t1.1 Labyrinth\n");
    printf("\t  Y, V\n");
    printf("\t  ^\n");
    for(i = width - 1; i >= 0; i--){
      printf("\t %d|", i+1);
      for(j = 0; j < height; j++){
        printf("\t%d", labyrinth[i][j] );
      }
      printf("\n");
    }
    printf("\t  -----------------------------------------------------------> X, U\n\n");
    printf("\t\t1\t 2\t 3\t 4\t 5\t 6\t 7\n");

    printf("\t1.2. Initial position X=%d, Y=%d. L=%d\n", initial_y + 1, initial_x + 1, counter);

    printf("PART 2. Trace\n");
    if(initial_x == 0 || initial_x == width-1 || initial_y == 0 || initial_y == height-1){
      printf("PART 3. Results\n");
      printf("\t3.1. Path is found.\n");
      printf("\t3.2. Path grafically\n");
      printf("\t  Y, V\n");
      printf("\t  ^\n");
      for(i = width - 1; i >= 0; i--){
        printf("\t %d|", i+1);
        for(j = 0; j < height; j++){
          if(labyrinth[i][j] < 0){
            printf("\t%d", labyrinth[i][j]);
          }
          else{
            printf("\t %d", labyrinth[i][j] );
          }

        }
        printf("\n");
      }
      printf("\t  -----------------------------------------------------------> X, U\n");

      return 0;
    }

    if(find_path(initial_x, initial_y, trial)){
      printf("PART 3. Results\n");
      printf("\t3.1. Path is found.\n");
      printf("\t3.2. Path grafically\n");
      printf("\t  Y, V\n");
      printf("\t  ^\n");
      for(i = width - 1; i >= 0; i--){
        printf("\t %d|", i+1);
        for(j = 0; j < height; j++){
          if(labyrinth[i][j] < 0){
            printf("\t%d", labyrinth[i][j]);
          }
          else{
            printf("\t %d", labyrinth[i][j] );
          }

        }
        printf("\n");
      }
      printf("\t  -----------------------------------------------------------> X, U\n");
      printf("\t\t1\t 2\t 3\t 4\t 5\t 6\t 7\n");
    }
    else
    {
        printf("Failed\n");
    }


    return 0;
}
