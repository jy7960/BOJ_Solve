#include <stdio.h>

int main(){
    int X;
    scanf("%d", &X);
    int ans = 0;
    while(X>0){
        if(X%2) ans++;
        X = X >> 1;
    }
    printf("%d",ans);
}