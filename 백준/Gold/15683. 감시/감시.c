#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define min(a,b) (a>b?b:a)

typedef struct point
{
    int y, x;
} point;

int N, M;
int zero = 0;
int ans = 128;
int cCnt = 0;
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, 1, 0, -1};
int map[8][8];
point cctv[8];
point blind[64];

// 가능한지 확인
bool isPossible(int y, int x){
    if(y < 0 || x < 0 || y >=N || x >= M)   return false;
    if(map[y][x] == 6)  return false;

    return true;
}

// 번호 채우기
int fillNum(int y, int x, int idx){
    int a = 0;
    if(map[y][x] == 0){
        blind[idx].y = y;
        blind[idx].x = x;
        map[y][x] = -1;
        a++;
    }
    return a;
}

// 한 방향으로 확인 시작
int dirCheck(int y, int x, int dir, int bias){
    int cut = 0;
    for(int i = 1; i < 8; i++){
        int ny = y + i * dy[dir];
        int nx = x + i * dx[dir];
        if(!isPossible(ny, nx)) break;
        cut += fillNum(ny, nx, bias+cut);
    }

    return cut;
}

// CCTV 작동!
int cctvOn(int num, int dir, int bias){
    int y = cctv[num].y;
    int x = cctv[num].x;
    int c = map[y][x];
    int cut = 0;
    if(c == 1){
        cut += dirCheck(y, x, dir, bias+cut);
    }
    else if(c == 2){
        cut += dirCheck(y, x, dir, bias+cut);
        cut += dirCheck(y, x, (dir+2)%4, bias+cut);
    }
    else if(c == 3){
        cut += dirCheck(y, x, dir, bias+cut);
        cut += dirCheck(y, x, (dir+1)%4, bias+cut);
    }
    else if(c == 4){
        cut += dirCheck(y, x, dir, bias+cut);
        cut += dirCheck(y, x, (dir+1)%4, bias+cut);
        cut += dirCheck(y, x, (dir+2)%4, bias+cut);
    }
    else if(c == 5){
        cut += dirCheck(y, x, dir, bias+cut);
        cut += dirCheck(y, x, (dir+1)%4, bias+cut);
        cut += dirCheck(y, x, (dir+2)%4, bias+cut);
        cut += dirCheck(y, x, (dir+3)%4, bias+cut);
    }

    return cut;
}

// CCTV 끄기
void cctvOff(int num, int dir, int bias, int len){
    for(int i = bias; i < bias + len; i++){
        int y = blind[i].y;
        int x = blind[i].x;
        map[y][x] = 0;
    }
}

void solve(int cnt, int area){
    if(cnt == cCnt){
        ans = min(ans, zero - area);
        return;
    }

    for(int i = 0; i < 4; i++){
        int cut = cctvOn(cnt, i, area);
        solve(cnt+1, area+cut);
        cctvOff(cnt, i, area, cut);
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < M; x++){
            scanf(" %d", &map[y][x]);
            if(map[y][x] == 0)  zero++;
            else if(map[y][x] > 0 && map[y][x] < 6){
                cctv[cCnt].y = y;
                cctv[cCnt++].x = x;
            }
        }
    }

    solve(0, 0);
    printf("%d", ans);
}