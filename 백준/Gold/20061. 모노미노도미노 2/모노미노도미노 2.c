#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int score = 0;
bool blue[6][4];
bool green[6][4];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

bool checkFill(bool map[6][4], int y){
    for(int i = 0; i < 4; i++){
        if(!map[y][i])   return false;
    }
    return true;
}

void dropBlock(bool map[6][4], int yIdx){
    for(int i = 0; i < 4; i++)  map[yIdx][i] = false;
    for(int y = yIdx; y > 0; y--){
        for(int x = 0; x < 4; x++){
            map[y][x] = map[y-1][x];
        }
    }
    for(int i = 0; i < 4; i++)  map[0][i] = false;
}

void fill(bool map[6][4], int t, int x) {
    int y = 0;
    if(t == 1){
        while (y + 1 < 6 && !map[y + 1][x]){
            y++;
        }
        map[y][x] = true;
    }
    else if(t == 2){
        while(y + 1 < 6 && !map[y + 1][x] && !map[y + 1][x + 1]){
            y++;
        }
        map[y][x] = true;
        map[y][x + 1] = true;
    }
    else{ 
        y = 1;
        while(y + 1 < 6 && !map[y + 1][x]){
            y++;
        }
        map[y][x] = true;
        map[y - 1][x] = true;
    }

    for(int y = 5; y >= 0; y--){
        if(checkFill(map, y)){
            score++;
            dropBlock(map, y);
            y++;
        }
    }

    int drop = 0;
    if(map[0][0] || map[0][1] || map[0][2] || map[0][3])
        drop = 2;
    else if(map[1][0] || map[1][1] || map[1][2] || map[1][3])
        drop = 1;

    for(int i = 0; i < drop; i++){
        dropBlock(map, 5);
    }
}

int countBlock(bool map[6][4]){
    int ret = 0;
    for(int y = 0; y < 6; y++){
        for(int x = 0; x < 4; x++){
            if(map[y][x])   ret++;
        }
    }
    return ret;
}

int main(){
    int T;
    scanf("%d", &T);

    while(T--){
        int t, x, y;
        scanf("%d %d %d", &t, &x, &y);
        if(t==1){
            fill(blue, 1, x);
            fill(green, 1, y);
        }
        else if(t==2){
            fill(blue, 3, x);
            fill(green, 2, y);
        }
        else{
            fill(blue, 2, x);
            fill(green, 3, y);
        }
    }
    printf("%d\n%d\n", score, countBlock(green)+countBlock(blue));

}