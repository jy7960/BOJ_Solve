#include <stdio.h>

int main(){
    int T;
    scanf("%d", &T);

    while(T--){
        long long N;
        scanf("%lld", &N);

        long long power = 5;
        int k = 1;

        while(N > power){
            power *= 5;
            k++;
        }

        if(k == 1)
            printf("MIT time\n");
        else
            printf("MIT^%d time\n", k);       
    }
}
