#include <stdio.h>

#define SIZE 1001
#define MOD 10007

int dp[SIZE][SIZE];

int main(){
    int N, K;
    scanf("%d %d", &N, &K);
    for(int i = 0; i < SIZE; i++){
        dp[i][0] = 1;
        dp[i][i] = 1;
    }
    for(int i = 1; i < SIZE; i++){
        for(int j = 1; j < SIZE; j++){
            dp[i][j] = (dp[i-1][j-1] + dp[i-1][j]) % MOD;
        }
    }
    printf("%d", dp[N][K]);
}