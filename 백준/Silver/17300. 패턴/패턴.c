#include <stdio.h>
#include <stdbool.h>

int main() {
    int L;
    int arr[9];
    scanf("%d", &L);

    for(int i = 0; i < L; i++)
        scanf("%d", &arr[i]);
    
    bool visited[9] = {false};
    // 사이 연결관계
    int skip[9][9] = {0}; 
    skip[0][2] = skip[2][0] = 1;
    skip[3][5] = skip[5][3] = 4;
    skip[6][8] = skip[8][6] = 7;
    skip[0][6] = skip[6][0] = 3;
    skip[1][7] = skip[7][1] = 4;
    skip[2][8] = skip[8][2] = 5;
    skip[0][8] = skip[8][0] = 4;
    skip[2][6] = skip[6][2] = 4;


    visited[arr[0] - 1] = true;

    for(int i = 1; i < L; i++){
        int cur = arr[i] - 1;
        if(visited[cur]){
            printf("NO\n");
            return 0;
        }
        visited[cur] = true;
        int prev = arr[i-1] - 1;
        if(skip[cur][prev] && !visited[skip[cur][prev]]){
            printf("NO\n");
            return 0;
        }
        
    }

    printf("YES\n");
}