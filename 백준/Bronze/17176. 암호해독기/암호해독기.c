#include <stdio.h>

int arr[53];

int main(){
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        int a;
        scanf("%d", &a);
        arr[a]++;
    }
    char c;
    getchar();
    for(int i = 0; i < N; i++){
        scanf("%c", &c);
        int idx;
        if(c==' '){
            idx = 0;
        }
        else if(c >= 'A' && c <= 'Z'){
            idx = (int)(c-'A')+1;
        }
        else if(c >= 'a' && c <= 'z'){
            idx = (int)(c-'a')+27;
        }
        arr[idx]--;
        if(arr[idx] < 0){
            printf("n");
            return 0;
        }
    }
    printf("y");
}