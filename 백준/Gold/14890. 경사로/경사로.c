#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int N, L;
int map[100][100];
int road[100];
bool visited[100];

bool solve(){
    for(int i = 0; i < N; i++)
        visited[i] = false;
    
    for(int i = 0; i < N - 1; i++){
        int diff = road[i] - road[i+1];

        // 높이 차이 1 이상 X
        if(abs(diff) > 1)   return false;

        // 내리막길
        if(diff == 1){
            // 경사로가 밖에 나가면 X
            if(i + L >= N) return false;

            int h = road[i+1];
            for(int j = i + 1; j <= i + L; j++){
                if(road[j] != h || visited[j])  return false;
                visited[j] = true;
            }
        }
        else if (diff == -1) {
            if (i - L + 1 < 0) return false;

            int h = road[i];
            for(int j = i; j >= i - L + 1; j--){
                if (road[j] != h || visited[j]) return false;
                visited[j] = true;
            }
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &N, &L);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf("%d", &map[y][x]);
        }
    }

    int ans = 0;

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            road[j] = map[i][j];
        
        if(solve()) ans++;
    }

    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            road[j] = map[j][i];
        
        if(solve()) ans++;
        
    }

    printf("%d\n", ans);
    return 0;
}
