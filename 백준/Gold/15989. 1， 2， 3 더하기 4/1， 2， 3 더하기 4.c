#include <stdio.h>
#include <stdlib.h>

int main(){
    int T, N;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &N);
        int ans = 0;
        for(int i = 0; i <= (N/3); i++){
            int tmp = N - (3*i);
            ans += tmp/2+1;
        }
        printf("%d\n", ans);
    }
}