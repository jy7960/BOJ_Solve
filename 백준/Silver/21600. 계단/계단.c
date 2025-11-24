#include <stdio.h>

#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)

int N;
int dp[100000];
int arr[100000];

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)  scanf("%d", arr+i);
    dp[0] = 1;
    for(int i = 1; i < N; i++){
        if(arr[i] > dp[i-1])    dp[i] = dp[i-1]+1;
        else{
            dp[i] = min(arr[i], i+1);
        }
    }
    int ans = 0;
    for(int i = 0; i < N; i++)  ans = max(ans, dp[i]);
    printf("%d", ans);
}