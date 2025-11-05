#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 1024*20


int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
bool map[102][102];

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        // 정보 받고 방향 계산
        int x, y, d, g;
        scanf("%d %d %d %d", &x, &y, &d, &g);
        int arr[1024][3]; // x, y, d
        int idx = 0;
        arr[idx][0] = x, arr[idx][1] = y, arr[idx++][2] = d;
        for(int j = 1; j <= g; j++){
            for(int k = 0; k < idx; k++){
                arr[idx+k][0] = arr[idx+k-1][0] + dx[arr[idx+k-1][2]];
                arr[idx+k][1] = arr[idx+k-1][1] + dy[arr[idx+k-1][2]];
                arr[idx+k][2] = (arr[idx-k-1][2] + 1) % 4;
            }
            idx *= 2;
        }
        arr[idx][0] = arr[idx-1][0] + dx[arr[idx-1][2]];
        arr[idx][1] = arr[idx-1][1] + dy[arr[idx-1][2]];
        // 맵 채우기
        for(int j = 0; j <= idx; j++)
            map[arr[j][1]][arr[j][0]] = true;
    }
    // 정사각형 찾기
    int ans = 0;
    for(int y = 0; y <= 100; y++){
        for(int x = 0; x <= 100; x++){
            if(map[y][x] && map[y+1][x] && map[y][x+1] && map[y+1][x+1]) ans++;
        }
    }
    printf("%d", ans);
}