#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

int n, m;
int arr[10][10];
int rowd[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
int cold[8] = {0, 0, -1, 1, -1, 1, -1, 1};

int result = -1;
int now[20];
int now_len = 0;

int convert_to_int(){
    int x = 0;
    for(int i = 0; i < now_len; i++) x = x * 10 + now[i];
    return x;
}

int is_square(int x){
    if (x < 0) return 0;
    int r = (int)(sqrt(x) + 1e-9);
    return r * r == x;
}

void backtracking(int y, int x, int rd, int cd, int dir){
    int value = convert_to_int();
    
    if(is_square(value)){
        if (value > result) result = value;
    }

    if(dir == -1){
        for(int d = 0; d < 8; d++){
            for(int i = 1; i <= 8; i++){
                for(int j = 1; j <= 8; j++){
                    backtracking(y, x, i, j, d);
                }
            }
        }
    }
    else{
        int ny = y + rowd[dir] * rd;
        int nx = x + cold[dir] * cd;

        if(0 <= ny && ny < n && 0 <= nx && nx < m){
            now[now_len++] = arr[ny][nx];
            backtracking(ny, nx, rd, cd, dir);
            now_len--;
        }
    }
}

int main(){
    scanf("%d %d", &n, &m);
    
    char buf[20];
    for(int i = 0; i < n; i++){
        scanf("%s", buf);
        for(int j = 0; j < m; j++){
            arr[i][j] = buf[j] - '0';
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            now_len = 0;
            now[now_len++] = arr[i][j];
            backtracking(i, j, 0, 0, -1);
        }
    }

    printf("%d\n", result);
}
