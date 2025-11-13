#include <stdio.h>

int main(){
    int N, ans = 0;
    scanf("%d", &N);
    char c[100001];
    scanf("%s", c);

    for(int i = 1; i < N; i++){
        if((int)c[i] == (int)(c[i-1]+1) || (int)c[i] == (int)(c[i-1]-1))
            ans++;
        else
            ans = 0;
            if(ans >= 4)    break;
    }
    if(ans >= 4)    printf("YES");
    else            printf("NO");
}