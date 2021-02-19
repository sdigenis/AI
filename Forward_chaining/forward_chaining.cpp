#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <map>
using namespace std;

#define MAX_LINE_LEN 1024
#define RULES 100

string strs[RULES];
struct rule{
    char from[RULES][5];
    char to[RULES];
}rules;

struct visited{
    rule arc;
    int number[RULES];
    int yor;
    int end[RULES];
}visited;

string convertToString(char* a, int size)
{
    int i;
    string str = "";
    for (i = 0; i < size; i++) {
        str = str + a[i];
    }
    return str;
}

char facts[RULES];
char goal;
int facts_num;
int rules_num = 0;
int result_num = 0;

int main(int argc, char *argv[]){

    ifstream file;
    file.open("input.txt");
    char line[MAX_LINE_LEN];

    char *slash_ptr, *space_ptr, *fact_ptr;
    char* rule[RULES]={NULL};

    string str;
    int goal_flag = 0, fact_flag = 0;
    int i = 0, j = 0, k = 0;

    for(i = 0; i < RULES; i++){
        for(j = 0; j < 3; j++){
            rules.from[i][j] = '\0';
        }
        rules.to[i] = '\0';
    }
    for(i = 0; i < RULES; i++){
        facts[i] = '\0';
    }
    i = 0;
    j = 0;

    while(file.getline(line, MAX_LINE_LEN)){
        str = convertToString(line, strlen(line));
        strs[i] = str;
        if(goal_flag == 1){
            goal = line[0];
            //cout << goal << "\n";
            break;
        }
        if(str == "3) Goal"){
            goal_flag = 1;
            continue;
        }
        if(str == "2) Facts"){
            fact_flag = 1;
            continue;
        }
        if(fact_flag == 1){
            fact_ptr = strchr(line, ' ');
            while(1){
                if(fact_ptr == NULL){
                    fact_ptr = strrchr(line, ' ');
                    line[fact_ptr - line] = '\0';
                    facts[k] = line[fact_ptr - line+1];
                    k++;
                    facts_num = k;
                    //cout << "facts["<<k<<"]:"<<facts[k] <<'\n';
                    break;
                }
                else{
                    facts[k] = line[fact_ptr - line -1];
                    //cout << "facts["<<k<<"]:"<<facts[k] << ' ';
                    k++;
                    fact_ptr = strchr(fact_ptr+1, ' ');
                }
            }
            continue;
        }
		slash_ptr = strchr(line, '/');
        while (slash_ptr != NULL){
            line[slash_ptr - line] = '\0';
            rule[i]=(char *)malloc( strlen(line)+1);

            strcpy(rule[i],line);
            space_ptr = strchr(rule[i], ' ');
            int edo = 0;
            while(1){
                if(edo == 0)
                {
                    edo++;
                    rules.to[result_num] = rule[i][space_ptr - rule[i] -1];
                    space_ptr = strchr(space_ptr + 1, ' ');
                    result_num++;
                }
                else{
                        if(space_ptr == NULL){
                        space_ptr = strrchr(rule[i], ' ');
                        rules.from[i][j] = rule[i][space_ptr - rule[i] + 1];
                        rules_num++;
                        //cout << "rules.to["<<cnt<<"]: "<< rules.to[cnt] << '\n';
                        break;
                    }
                    else{
                        //cout << rule[i] << '\n';
                        rules.from[i][j] = rule[i][space_ptr - rule[i] -1];
                        //cout << "rules.from[" << i <<"]["<< j <<"]: "<<rules.from[i][j] << '\n';
                        j++;
                        space_ptr = strchr(space_ptr + 1, ' ');
                        rules_num++;
                    }
                }
            }
            //printf("\n");
            j = 0;

            i++;
            break;
        }
    }

    for(i = 0; i < result_num; i++){
        for (j = 0; j < 2; j++){
            if (rules.from[i][j] == '\0'){
                break;
            }
        }
        //printf("************************\n");

        visited.number[i] = j;
        visited.yor = 0;
        visited.end[i] = 0;
    }

    for(i = 0; i < result_num; i++){
        for(j = 0; j < 2; j++){
            visited.arc.from[i][j] = rules.from[i][j];
        }
        visited.arc.to[i] = rules.to[i];
        for(k = 0; k < facts_num; k++){
            //printf("visited:%c vs fact:%c\n", visited.arc.to[i], facts[k]);
            if(visited.arc.to[i] == facts[k]){
                //printf("here\n");
                visited.end[i] = 1;
            }
        }
        //printf("\n");
    }

    printf("PART 1. Data\n");
    printf("\t1) Rules\n");
    for(i = 0; i < rules_num; i++){
        if(visited.arc.to[i] == '\0'){
            break;
        }
        printf("\t    R%d: ", i+1);
        for(j = 0; j < 3; j++){
            if(visited.arc.from[i][j] == '\0'){
                break;
            }
            if(j == 0){
                cout << visited.arc.from[i][j];
            }
            else
            {
                cout << ", " << visited.arc.from[i][j];
            }

        }
        cout <<" -> "<< visited.arc.to[i] << '\n';
    }
    printf("\t2) Facts ");
    for(i = 0; i < facts_num; i++){
        if(i == facts_num - 1){
          printf("%c.\n", facts[i]);
          break;
        }
        printf("%c, ", facts[i]);
    }
    printf("\t3) Goal %c.\n", goal);
    printf("PART 2. Trace\n");

    int times = 0, jump = 0, exit = 0;
    times = 1;
    int iter = 1;
    int cnt, cnt2;
    while(exit != 1 ){
        //printf("\tITERATION %d\n", iter);
        //iter++;
        for(i = 0; i < result_num; i++){
            if(exit != 0){
                break;
            }
            //printf("\tITERATION %d\n", iter);

            jump = 0;
            //for(cnt = 0; cnt < i; cnt++){
                //printf("here\n");
            printf("\t\tnew fact to add: %c\n", visited.arc.to[i]);
                if(visited.end[i] == 1){
                    printf("\t\t%c already on the list\n", visited.arc.to[i]);
                    //continue;
                    //printf("\t\tR%d:%c->%c skip, because flag1 raised.\n", cnt+1, visited.arc.from[i][cnt], visited.arc.to[cnt]);
                }
                //break;
                //printf("\t\tR%d:%c->%c skip, because flag1 raised.\n", cnt+1, visited.arc.from[cnt][0], visited.arc.to[cnt]);
            //}

            //sleep(3);
            times = 0;
            //jump = 0;

            //printf("times: %d of trying\n", visited.number[i]);
              for(j = 0; j < facts_num; j ++){
                  if (visited.arc.to[i] == facts[j]){
                      //printf("\t\tR%d:%c->%c not applied, because RHS in facts. Raise flag2.\n", i+1, visited.arc.from[i][j], visited.arc.to[i]);
                      visited.end[i] = 2;
                      //printf("already on the list: %c\n", visited.arc.to[i]);
                      jump++;
                      //i++;
                      //flag2++;
                      break;
                  }
              }
              //if(flag2 != 0){
                //printf("here: flag2 : %d\n", flag2);
                //continue;
              //}
            //}
            //flag2 = 0;
            if(visited.end[i] == 0){
              printf("\t\twasnt in the list : %c\n", visited.arc.to[i]);
            }

            for(k = 0; k < 3; k++){
                if(exit != 0 || jump != 0){
                    break;
                }
                //printf("here\n");
                if(visited.arc.from[i][k] == '\0'){
                    break;
                }
                for(j = 0 ; j < facts_num; j++){

                    if(facts[j] == visited.arc.from[i][k]){
                        times++;
                        //printf("times:%d\n", times);
                    }
                    if(times == visited.number[i]){
                        facts[facts_num] = visited.arc.to[i];
                        if(facts[facts_num] == goal){
                            exit++;
                        }
                        facts_num++;
                        //printf("\t\tR%d:%c->%c apply. Raise flag1.", i+1, visited);
                        printf("\t\tadded on the list: %c\n", visited.arc.to[i]);
                        //printf("\t\tR%d:%c->%c apply. Raise flag1. Facts ", i+1, visited.arc.from[i][k], visited.arc.to[i]);
                        visited.end[i] = 1;
                        for(cnt = 0; cnt < facts_num; cnt++){
                            if(cnt == facts_num - 1){
                              //printf("%c.\n", facts[cnt]);
                              break;
                            }
                            //printf("%c, ", facts[cnt]);
                        }
                        jump++;
                        break;;
                    }
                }
            }
        }
        //printf("here\n");
        for(j = 0; j < facts_num; j++){
            if(exit != 0 || jump != 0){
                break;
            }
            for(k = 0; k < 3; k++){
                if(exit != 0 || jump != 0){
                    break;
                }
                if(visited.arc.from[j][k] == '\0'){
                    break;
                }
                for(i = 0 ; i < facts_num; i++){
                    if(jump != 0){
                      break;
                    }
                    if(facts[j] == visited.arc.from[j][k]){
                        times++;
                        //printf("times:%d\n", times);
                    }
                    if(times == visited.number[i] ){
                        facts[facts_num] = visited.arc.to[i];
                        printf("\t\tR%d:%c->%c apply. Raise flag1. Facts ", i+1, visited.arc.from[i][k], visited.arc.to[i]);
                        visited.end[i] = 1;
                        for(cnt = 0; cnt < facts_num; cnt++){
                            if(cnt == facts_num - 1){
                              printf("%c.\n", facts[cnt]);
                              break;
                            }
                            printf("%c, ", facts[cnt]);
                        }
                        if(facts[facts_num] == goal){
                            exit++;
                        }
                        facts_num++;
                        printf("added on the list: %c\n", visited.arc.to[i]);
                        jump++;
                    }
                    else if(i == facts_num - 1){
                        printf("here\n");
                        //R5:F,B->Z not applied, because of lacking F.
                        printf("\t%d:", j+1);
                        char character;
                        for(int cnt1 = 0; cnt1 < facts_num; cnt1++){
                            for(int cnt2 = 0; cnt2 < 3; cnt++){
                                if(visited.arc.from[cnt1][cnt2] == facts[cnt1]){
                                    character = visited.arc.from[cnt1][cnt2];
                                    break;
                                }
                            }
                            printf("%s not applied, because of lacking %c\n", strs[i].c_str(),character);
                        }
                    }
                }
            }
        }
    }

    printf("PART 3. Results\n");
    printf("\t1) Goal achieved.\n");
    printf("\t2) Path ");
    for(i = 0; i < facts_num; i++){
        if(i != facts_num - 1){
            printf("%c, ", facts[i]);
        }
        else
        {
            printf("%c.\n", facts[i]);
        }

    }
    //printf(".\n");

    return 0;
}
