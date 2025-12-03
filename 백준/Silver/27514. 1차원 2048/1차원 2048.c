#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ll long long

int N;
ll arr[200000];
ll power[63];
int cnt[63];

int cmp(const void* a, const void* b){
    if(*(ll *) a > *(ll *) b )    return 1;
    else if(*(ll *) a < *(ll *) b )   return -1;
    return 0;
}

int root2(ll a){
    ll idx = 0;
    while((1LL << idx) < a){
        idx++;
    }
    return idx;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++)
        scanf("%lld", &arr[i]);
    
    qsort(arr, N, sizeof(ll), cmp);
    for(int i = 0; i < N; i++){
        if(arr[i] != 0){
            int idx = root2(arr[i]);
            cnt[idx]++;
        }
    }

    for(int i = 0; i < 62; i++){
        cnt[i + 1] += cnt[i] / 2;
        cnt[i] %= 2;
    }

    for(int i = 62; i >= 0; i--){
        if(cnt[i] > 0){
            printf("%lld", 1LL << i);
            return 0;
        }
    }
}