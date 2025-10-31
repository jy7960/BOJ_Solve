#include <stdio.h>
#include <string.h>
#include <stdlib.h>

double prefix(char p){
    if (p == 'm') return 1e-3;
    if (p == 'k') return 1e3;
    if (p == 'M') return 1e6;
    return 1.0;
}

int main(){
    int T;
    scanf("%d", &T);
    getchar();

    for(int i = 1; i <= T; i++){
        char line[1000];
        fgets(line, sizeof(line), stdin);

        double P = -1, U = -1, I = -1;
        char *ptr = line;

        while((ptr = strchr(ptr, '=')) != NULL){
            char concept = *(ptr - 1); // P, U, I
            ptr++;

            double val = atof(ptr);

            // 숫자 끝으로 포인터 이동
            while((*ptr >= '0' && *ptr <= '9') || *ptr == '.')
                ptr++;

            // 접두사 확인
            double mul = 1.0;
            if(*ptr == 'm' || *ptr == 'k' || *ptr == 'M'){
                mul = prefix(*ptr);
                ptr++;
            }

            if(*ptr == 'W' && concept == 'P') P = val * mul;
            if(*ptr == 'V' && concept == 'U') U = val * mul;
            if(*ptr == 'A' && concept == 'I') I = val * mul;
        }

        printf("Problem #%d\n", i);
        if(P < 0){
            P = U * I;
            printf("P=%.2fW\n\n", P);
        }
        else if (U < 0){
            U = P / I;
            printf("U=%.2fV\n\n", U);
        }
        else if (I < 0){
            I = P / U;
            printf("I=%.2fA\n\n", I);
        }
    }
}
