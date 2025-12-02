#include <stdio.h>
#include <stdbool.h>

int arr[101];
int ab[20000][2];
bool check[20000];

int main(){
    int a, b, T;
    scanf("%d", &T);
    for(int i = 0; i < T; i++){
        scanf("%d", &arr[i]);
    }
    int idx = 0;
    if(T > 1){
        for(a = 0; a <= 10000; a++){
            for(b = 0; b<= 10000; b++){
                if(((a *((a * arr[0] + b) % 10001) + b) % 10001) == arr[1]){
                    ab[idx][0] = a;
                    ab[idx][1] = b;
                    idx++;
                }
            }
        }

        for(int i = 1; i < T-1; i++){
            for(int j = 0; j < idx; j++){
                if(check[j])    continue;
                if(((ab[j][0] *((ab[j][0] * arr[i] + ab[j][1]) % 10001) + ab[j][1]) % 10001) != arr[i+1]){
                    check[j] = true;
                }
            }
        }
    }
    else{
        printf("0");
        return 0;
    }
    for(int j = 0; j < idx; j++){
        if(!check[j]){
            for(int i = 0; i < T; i++){
                printf("%d\n", (ab[j][0] * arr[i] + ab[j][1]) % 10001);
            }
            break;
        }
    }
}