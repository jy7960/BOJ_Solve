#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_K 20
#define MAX_MASKS (1 << MAX_K)

int N, K;
bool dp[MAX_MASKS];
char S[MAX_K+1];

void update(int mask) {
    if(dp[mask])
        return;
    

    dp[mask] = true;

    for (int i = 0; i < K; i++) {
        if (mask & (1 << i)) {
            update(mask ^ (1 << i));
        }
    }
}

int main() {
    scanf("%d %d", &N, &K);

    int z = 0;
    for(int i = 0; i < N; i++){
        scanf("%s", S);

        int cur = 0;
        if(z == 0){
            for(int j = 0; j < K; j++){
                if(S[j] == '1') cur |= (1 << j);
            }
        }
        else{
            for(int j = 0; j < K; j++){
                if(S[K - 1 - j] == '1') cur |= (1 << j);
            }
        }


        if(dp[cur]){
            printf("WellKnown\n");
            z = 0;
        }
        else{
            printf("AdHoc\n");
            z = 1;
            update(cur);
        }
    }

    return 0;
}