#include <stdio.h>

#define MAX 1000000

int N;
double A[MAX];

int solve(){
    double minAverage = (A[0]+ A[1]) / 2;
    int idx = 0;

    for(int i = 2; i < N; i++){
        double temp = (A[i - 2] +
        A[i - 1] + A[i]) / 3;
        if(temp < minAverage){
            minAverage= temp;
            idx = i - 2;
        }
    }

    for(int i = 1; i < N; i++){
        double temp = (A[i - 1] +  A[i]) / 2;

        if (temp < minAverage){
            minAverage= temp;
            idx = i - 1;
        }
    }

    return idx;
}



int main(void){
    scanf("%d", &N);
    for (int i = 0; i < N; i++) scanf("%lf", A+i);
    if(N == 2) printf("0");
    else    printf("%d", solve());
}
