#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N;
int map[500][500];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

int devideSand(int y, int x, int sand){
    if(y >= 0 && x >= 0 && y < N &&x < N){
        map[y][x] += sand;
        return 0;
    }
    return sand;
}

int wind(int y, int x, int d){
    int ret  = 0;
    int one = map[y][x] / 100;
    int two = 2 * map[y][x] / 100;
    int five = 5 * map[y][x] / 100;
    int sev = 7 * map[y][x] / 100;
    int ten = 10 * map[y][x] / 100;
    int alpha = map[y][x] - 2*one - 2*two - 2*sev - 2*ten - five;

    ret += devideSand(y+dy[d], x+dx[d], alpha);
    ret += devideSand(y-dy[d]+dy[(d+1)%4], x-dx[d]+dx[(d+1)%4], one);
    ret += devideSand(y-dy[d]+dy[(d+3)%4], x-dx[d]+dx[(d+3)%4], one);
    ret += devideSand(y+2*dy[(d+1)%4], x+2*dx[(d+1)%4], two);
    ret += devideSand(y+2*dy[(d+3)%4], x+2*dx[(d+3)%4], two);
    ret += devideSand(y+2*dy[d], x+2*dx[d], five);
    ret += devideSand(y+dy[(d+1)%4], x+dx[(d+1)%4], sev);
    ret += devideSand(y+dy[(d+3)%4], x+dx[(d+3)%4], sev);
    ret += devideSand(y+dy[d]+dy[(d+1)%4], x+dx[d]+dx[(d+1)%4], ten);
    ret += devideSand(y+dy[d]+dy[(d+3)%4], x+dx[d]+dx[(d+3)%4], ten);

    return ret;
}

int main(){
    scanf("%d", &N);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf("%d", &map[y][x]);
        }
    }

    int ans = 0;
    int cx = N >> 1;
    int cy = cx;
    int len = 1;
    int flow = 0;
    int dir = 0;
    bool flag = true;

    while(flag){
        for(int i = 1; i <= len; i++){
            int ny = cy + dy[dir];
            int nx = cx + dx[dir];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N){
                flag = false;
                break;
            }
            ans += wind(ny, nx, dir);
            cy = ny, cx = nx;
        }
        flow++;
        dir = (dir+1) % 4;
        if(flow==2){
            flow = 0;
            len++;
        }
    }
    printf("%d", ans);
}