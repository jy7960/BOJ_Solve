#include <stdio.h>

int main(){
    int y, x, tar;
    scanf("%d %d %d", &y, &x, &tar);
    if(y+x-1 > tar){
        printf("NO");
        return 0;
    }
    printf("YES\n");
    for(int i = 1; i <= y; i++){
        for(int j = 0; j < x; j++){
            printf("%d ", i+j);
        }
        printf("\n");
    }
}