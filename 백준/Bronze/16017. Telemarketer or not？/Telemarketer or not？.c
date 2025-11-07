#include <stdio.h>

int main(){
    int arr[4];
    for(int i = 0; i < 4; i++)  scanf("%d", arr+i);
    if(arr[0] > 7 && arr[1]==arr[2] && arr[3] > 7)  printf("ignore");
    else                                            printf("answer");
}