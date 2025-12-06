#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 49
#define BOOM 999

int start;  // 시작 위치
int mapSize;
int N, M;
int group[SIZE*SIZE*2];
int arr[SIZE*SIZE];
int map[SIZE][SIZE];
int magic[100][2];  //방향, 크기
int dy[4] = {-1, 1, 0, 0};  // 마법 방향
int dx[4] = {0, 0, -1, 1};
int cy[4] = {0, 1, 0, -1};  // 사이클링
int cx[4] = {-1, 0, 1, 0};
int chain[3];

void blizzard(int d, int s){
    for(int i = 1; i <= s; i++){
        int ny = start + i * dy[d];
        int nx = start + i * dx[d];
        map[ny][nx] = BOOM;
    }

    bool flag = true;
    int y = start, x = start; 
    int len = 1, cnt = 0;
    int dir = 0, idx = 0;
    // 1자로 피기
    while(flag){
        for(int i = 0; i < len; i++){
            y = y + cy[dir];
            x = x + cx[dir];
            if(y < 0 || x < 0 || y >= N || x >= N){
                flag = false;
                break;
            }
            if(map[y][x] != BOOM && map[y][x] != 0){
                arr[idx++] = map[y][x];
                //printf("%d ", map[y][x]);
            }
        }
        cnt++;
        dir = (dir+1)%4;
        if(cnt==2){
            len++;
            cnt = 0;
        }
    }
    // 구슬 폭발
    flag = true;
    while(flag){
        flag = false;
        int erase = 0;
        int cur = arr[0];
        cnt = 1;
        
        for(int i = 1; i < idx; i++){
            if(arr[i]==cur){
                cnt++;
            }
            else{
                if(cnt >= 4){
                    flag = true;
                    for(int j = 1; j <= cnt; j++){
                        arr[i-j] = BOOM;
                    }
                    chain[cur-1] += cnt;
                    erase += cnt;
                }
                cur = arr[i];
                cnt = 1;
            }
        }
        if(cnt >= 4){
            flag = true;
            for(int j = 1; j <= cnt; j++){
                arr[idx-j] = BOOM;
            }
            chain[cur-1] += cnt;
            erase += cnt;
        }
        int nIdx = 0;
        for(int i = 0; i < idx; i++){
            if(arr[i]!=BOOM)    arr[nIdx++] = arr[i];
        }
        idx = nIdx;
    }

    // 버블 그룹화
    int gIdx = 0;
    if (idx > 0){
        int cur = arr[0];
        cnt = 1;
        for(int i = 1; i < idx; i++){
            if(arr[i]==cur){
                cnt++;
            }
            else{
                group[gIdx] = cnt;
                group[gIdx+1] = cur;
                gIdx+=2;
                cur = arr[i];
                cnt = 1;
            }
        }
        group[gIdx] = cnt;
        group[gIdx+1] = cur;
        gIdx+=2;
    }
    // 다시 맵 정렬
    flag = true;
    y = start, x = start; 
    len = 1, cnt = 0;
    dir = 0, idx = 0;
    while(flag){
        for(int i = 0; i < len; i++){
            y = y + cy[dir];
            x = x + cx[dir];
            if(y < 0 || x < 0 || y >= N || x >= N){
                flag = false;
                break;
            }
            if(idx < gIdx){
                map[y][x] = group[idx++];
            }
            else{
                map[y][x] = 0;
            }
        }
        cnt++;
        dir = (dir+1)%4;
        if(cnt==2){
            len++;
            cnt = 0;
        }
    }
    
}

int main(){
    scanf("%d %d", &N, &M);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf("%d", &map[y][x]);
        }
    }
    start = N >> 1;
    mapSize = N * N - 1;
    for(int i = 0; i < M; i++){
        scanf("%d %d", &magic[i][0], &magic[i][1]);
        magic[i][0]--;
    }

    for(int i = 0; i < M; i++){
        blizzard(magic[i][0], magic[i][1]);
    }
    printf("%d", chain[0]+2*chain[1]+3*chain[2]);
}