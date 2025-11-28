#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define min(a, b) (a>b?b:a)

int N, K, T;
int arr[100000];

int cmp(const void* a, const void* b){
    int x = *(int *)a % K;
    int y = *(int *)b % K;

    return y-x;
}

bool shake(int l, int r, int cnt){
    if(cnt > T) return false;
    if(l >= r)  return true;
    int tmpL = K - arr[l];
    int tmpR = arr[r];
    int mix = min(tmpL, tmpR);
    arr[l] += mix;
    arr[r] -= mix;

    if(mix == tmpL)
        return shake(l+1, r, cnt+mix);
    else
        return shake(l, r-1, cnt+mix);
}

int main(){
    scanf("%d %d %d",&N, &K, &T);
    int sum = 0;
    bool flag = true;
    for(int i = 0; i < N; i++){
        scanf("%d", arr+i);
        if(arr[i] > 0)  flag = false;
        sum += arr[i];
        sum %= K;
    }
    // 애초에 불가능
    if(sum%K != 0 && !flag){
        printf("NO");
        return 0;
    }
    // 나도리가 없어
    if(flag){
        printf("YES");
        return 0;
    }
    qsort(arr, N, sizeof(int), cmp);
    
    if(shake(0, N-1, 0))    printf("YES");
    else                    printf("NO");

}