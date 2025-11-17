#include <stdio.h>
#include <stdlib.h>

#define max(a,b) (a>b?a:b)

int dp[20];
int arr[15][2];

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++)  scanf("%d %d", &arr[i][0], &arr[i][1]);
    dp[arr[0][0]] = arr[0][1];
    for(int i = 1; i < N; i++){
        dp[i] = max(dp[i-1], dp[i]);
        dp[i+arr[i][0]] = max(dp[i+arr[i][0]], dp[i]+arr[i][1]);
    }
    int ans = 0;
    for(int i = 0; i <= N; i++) ans = max(ans, dp[i]);

    printf("%d", ans);
}