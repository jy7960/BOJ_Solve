#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_N 10
#define MAX_TREE 1000

int N, M, K;
int A[MAX_N][MAX_N];
int map[MAX_N][MAX_N]; 

int dy[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
int dx[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

int treeAge[MAX_N][MAX_N][MAX_TREE];
int treeCnt[MAX_N][MAX_N];

int cmp(const void* a, const void* b){
    return (*(int*)a - *(int*)b);
}


void SS(){
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            if(treeCnt[r][c] == 0)continue;

            qsort(treeAge[r][c], treeCnt[r][c], sizeof(int), cmp);

            int bob = map[r][c];
            int treeIdx = 0;
            int dead = 0;

            for(int i = 0; i < treeCnt[r][c]; i++){
                int age = treeAge[r][c][i];
                if(bob >= age){
                    bob -= age;
                    treeAge[r][c][treeIdx++] = age + 1;
                }
                else{
                    dead += age >> 1;
                }
            }
            map[r][c] = bob;
            map[r][c] += dead;
            treeCnt[r][c] = treeIdx;
        }
    }
}

void autumn() {
    int treeAge2[MAX_N][MAX_N][MAX_TREE];
    int treeCnt2[MAX_N][MAX_N] = {0};

    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            for(int i = 0; i < treeCnt[r][c]; i++){
                int age = treeAge[r][c][i];
                if(age % 5 == 0){
                    for(int d = 0; d < 8; d++){
                        int nr = r + dy[d];
                        int nc = c + dx[d];

                        if(nr >= 0 && nr < N && nc >= 0 && nc < N){
                            if(treeCnt2[nr][nc] < MAX_TREE) treeAge2[nr][nc][treeCnt2[nr][nc]++] = 1;
                        }
                    }
                }
            }
        }
    }

    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            for(int i = 0; i < treeCnt2[r][c]; i++){
                if(treeCnt[r][c] < MAX_TREE)    treeAge[r][c][treeCnt[r][c]++] = treeAge2[r][c][i];
            }
        }
    }
}

void winter(){
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            map[r][c] += A[r][c];
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &K);

    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            scanf("%d", &A[r][c]);
            map[r][c] = 5;
            treeCnt[r][c] = 0;
        }
    }

    for(int i = 0; i < M; i++){
        int r, c, age;
        scanf("%d %d %d", &r, &c, &age);
        --r; --c;
        if(treeCnt[r][c] < MAX_TREE){
            treeAge[r][c][treeCnt[r][c]++] = age;
        }
    }

    while(K--){
        SS();
        autumn();
        winter();
    }

    int ans = 0;
    for(int r = 0; r < N; r++){
        for(int c = 0; c < N; c++){
            ans += treeCnt[r][c];
        }
    }

    printf("%d", ans);

}
