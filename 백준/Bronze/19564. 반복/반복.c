#include <stdio.h>
#include <string.h>

char str[100001];

int main(){
    scanf("%s",str);
    int len = strlen(str);
    int ans = 1;
    char cur = str[0];
    for(int i = 1; i < len; i++){
        if(cur >= str[i])    ans++;
        cur = str[i];
    }
    printf("%d",ans);
}