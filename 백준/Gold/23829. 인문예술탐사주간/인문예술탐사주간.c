#include <stdio.h>
#include <stdlib.h>

#define ll long long

int N, Q;
ll arr[100000];
ll sum[100001];

int cmp(const void* a, const void* b){
    if(*(ll *)a < *(ll *)b) return -1;
    else if(*(ll *)a > *(ll *)b)    return 1;
    return 0;
}

int binsearch(int l, int r, int tar){
    int k = 0;
    while (l <= r){
        int m = l + (r-l) / 2;
        if(arr[m] <= tar){
            k = m+1;
            l = m+1;
        }
        else{
            r = m-1;
        }
    }
    return k;
}

int main(){
    scanf("%d %d", &N, &Q);
    for(int i = 0; i < N; i++)  scanf("%lld", arr+i);
    qsort(arr, N, sizeof(ll), cmp);
    for(int i = 0; i < N; i++)  sum[i+1] = sum[i] + arr[i];

    for(int i = 0; i < Q; i++){
        int x;
        scanf("%d", &x);
        int idx = binsearch(0, N-1, x);
        
    ll sumL = (ll)idx * x - sum[idx];
    ll sumR = -(ll)(N - idx) * x + (sum[N] - sum[idx]);
        printf("%lld\n", sumL+sumR);
    }

}