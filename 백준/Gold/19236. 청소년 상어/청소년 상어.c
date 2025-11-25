#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a,b) (a>b?a:b)
#define DEAD 999
#define SHARK 17

typedef struct fish
{
    int y, x;
    int num;
    int dir;
    bool life;
} fish;

// 위부터 반시계
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, -1, -1, -1, 0, 1, 1, 1};
int map[4][4];
int ans = 0;
fish f[18];

void moveFish(int idx){
    int y = f[idx].y;
    int x = f[idx].x;
    for(int i = 0; i < 8; i++){
        int d = (f[idx].dir + i) % 8;
        int ny = y + dy[d];
        int nx = x + dx[d];
        if(ny < 0 || nx < 0 || ny > 3 || nx > 3 || map[ny][nx] == SHARK)   continue;
        int nf = map[ny][nx];
        if(nf != DEAD){
            map[y][x] = nf;
            f[nf].y = y;
            f[nf].x = x;
        }
        else{
            map[y][x] = DEAD;
        }
        f[idx].y = ny;
        f[idx].x = nx;
        f[idx].dir = d;
        map[ny][nx] = idx;
        return;
    }
}

int eatFish(int y, int x){
    int ret = f[map[y][x]].num;
    f[SHARK].dir = f[map[y][x]].dir;
    f[SHARK].x = x;
    f[SHARK].y = y;
    f[ret].life = false;
    map[y][x] = SHARK;

    return ret;
}

void reviveFish(int sy, int sx, int sd, int fy, int fx, int num){
    map[fy][fx] = num;
    f[num].life = true;
    
    map[sy][sx] = 17;
    f[SHARK].y = sy;
    f[SHARK].x = sx;
    f[SHARK].dir = sd;
}

void backtrack(int eat){
    int temp_map[4][4];
    fish temp_f[18];
    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++)
            temp_map[y][x] = map[y][x];

    for(int i = 0; i < 18; i++)
        temp_f[i] = f[i];

    for(int i = 1; i <= 16; i++)
        if(f[i].life)   moveFish(i);   
    
    bool home = true;
    int y = f[SHARK].y;
    int x = f[SHARK].x;
    int d = f[SHARK].dir;
    // 상어가 어디로 가나
    for(int i = 1; i < 4; i++){
        int ny = y + i * dy[d];
        int nx = x + i * dx[d];
        if(ny < 0 || nx < 0 || ny > 3 || nx > 3)   break;
        if(map[ny][nx] == DEAD) continue;
        home = false;
        int meal = eatFish(ny, nx);
        map[y][x] = DEAD;
        backtrack(eat+meal);
        reviveFish(y, x, d, ny, nx, meal);
    }

    // 배열 복구
    for(int y = 0; y < 4; y++)
        for(int x = 0; x < 4; x++)
            map[y][x] = temp_map[y][x];
    for(int i = 0; i < 18; i++)
        f[i] = temp_f[i];

    if(home){
        ans = max(ans, eat);
        return;
    }
}

int main(){
    for(int y = 0; y < 4; y++){
        for(int x = 0; x < 4; x++){
            int n, d;
            scanf("%d %d", &n, &d);
            f[n].num = n;
            f[n].dir = d-1;
            f[n].x = x;
            f[n].y = y;
            f[n].life = true;
            map[y][x] = n;
        }
    }
    // 상어가 한 마리 냠냠
    f[SHARK].num = 17;
    f[SHARK].life = true;
    ans += eatFish(0,0);
    backtrack(ans);

    printf("%d", ans);
}