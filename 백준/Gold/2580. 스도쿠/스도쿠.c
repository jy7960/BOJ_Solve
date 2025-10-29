#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int tar = 0;
int tarP[81][2];
int p[9][9];

void printAll(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            printf("%d ", p[i][j]);
        }
        printf("\n");
    }
}

void solve(int cnt){
    if(cnt == tar){
        printAll();
        exit(0);
    }

    int y = tarP[cnt][1];
    int x = tarP[cnt][0];

    bool checked[10] = {false};
    checked[0] = true;

    for(int i = 0; i < 9; i++){
        if(p[i][x] != 0) checked[p[i][x]] = true;
        if(p[y][i] != 0) checked[p[y][i]] = true;
    }

    int py = (y / 3) * 3;
    int px = (x / 3) * 3;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(p[py+i][px+j] != 0) checked[p[py+i][px+j]] = true;
        }
    }

    for(int i = 1; i <= 9; i++){
        if(!checked[i]){
            p[y][x] = i;
            solve(cnt + 1);
            p[y][x] = 0;
        }
    }
}

int main(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            scanf("%d", &p[i][j]);
            if(p[i][j] == 0){
                tarP[tar][0] = j;
                tarP[tar++][1] = i;
            }
        }
    }

    if(tar == 0){
        printAll();
        return 0;
    }

    solve(0);

    return 0;
}
