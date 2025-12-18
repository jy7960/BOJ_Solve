#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int main(){
    bool flag = true;
    int N;
    scanf("%d", &N);
    while(N--){
        char str[51];
        scanf("%s",str);
        if(flag){
            if(strcmp(str,"yonsei")==0){
                printf("Yonsei Won!");
                flag = false;
            }
            else if(strcmp(str,"korea")==0){
                printf("Yonsei Lost...");
                flag = false;
            }
        }
    }
    
}