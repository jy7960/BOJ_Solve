#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MIX 999

typedef struct fireBall
{
    int y, x, m, s, d;
} fireBall;

typedef struct queue
{
    int top, rear;
    fireBall* arr;
} queue;

int N, M, K;
int dy[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dx[8] = {0, 1, 1, 1, 0, -1, -1, -1};
int map[50][50][4];    // 질량, 개수, 속력, 퍼질 방향(섞이면 999)

queue* initQueue(int size){
    queue* q = (queue *)malloc(sizeof(queue));
    q->rear = -1;
    q->top = -1;
    q->arr = (fireBall *)malloc(sizeof(fireBall) * size);

    return q;
}

void freeQueue(queue* q){
    free(q->arr);
    free(q);
}

bool isEmpty(queue* q){
    return q->top == q->rear;
}

void enqueue(queue* q, fireBall f){
    q->arr[++(q->top)] = f;
}

fireBall dequeue(queue* q){
    return q->arr[++(q->rear)];
}

void boom(queue* q){
    int tmp_map[50][50][4];
    memset(tmp_map, 0, sizeof(tmp_map));
    // 파이어볼 하나씩 이동
    while(!isEmpty(q)){
        fireBall f = dequeue(q);
        int y = (f.y + dy[f.d] * (f.s % N) +  N) % N;
        int x = (f.x + dx[f.d] * (f.s % N) +  N) % N;
        tmp_map[y][x][0] += f.m;
        tmp_map[y][x][1]++;
        tmp_map[y][x][2] += f.s;
        if(tmp_map[y][x][1] > 1){
            if(tmp_map[y][x][3]%2 != f.d%2) tmp_map[y][x][3] = MIX;
        }
        else{
            tmp_map[y][x][3] = f.d;
        }
    }
    // 파이어볼 넣기 위한 큐 초기화
    q->rear = -1;
    q->top = -1;
    // 바뀐 맵으로 수정하며 파이어볼 인큐
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < 4; k++)  map[i][j][k] = tmp_map[i][j][k];
            if(map[i][j][1] == 1){
                fireBall f = {i, j, map[i][j][0], map[i][j][2], map[i][j][3]};
                enqueue(q, f);
            }
            else if(map[i][j][1] > 1){
                int m = map[i][j][0] / 5;
                if(m == 0)  continue;
                int s = map[i][j][2] / map[i][j][1];

                if(map[i][j][3] == MIX){
                    for(int d = 1; d <= 7; d+=2){
                        fireBall f = {i, j, m, s, d};
                        enqueue(q, f);
                    }   
                }
                else{
                    for(int d = 0; d <= 6; d+=2){
                        fireBall f = {i, j, m, s, d};
                        enqueue(q, f);
                    }   
                }
            }
        }
    }
}

int main(){
    scanf("%d %d %d", &N, &M, &K);
    queue* q = initQueue(N*N*4);
    for(int i = 0; i < M; i++){
        int y, x, m, s, d;
        scanf("%d %d %d %d %d", &y, &x, &m, &s, &d);
        y--, x--;
        fireBall f = {y, x, m, s, d};
        enqueue(q, f);
        map[y][x][0] = m;
        map[y][x][1] = 1;
        map[y][x][2] = s;
        map[y][x][3] = d;
    }

    while(K--){
        boom(q);
    }
    int ans = 0;
    while(!isEmpty(q)){
        ans += dequeue(q).m;
    }
    printf("%d", ans);
    freeQueue(q);
}