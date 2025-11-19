#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define min(a,b) (a>b?b:a)
#define INF 987654321

typedef struct point
{
    int y, x;
} point;

typedef struct queue
{
    int top, rear;
    point *arr;
} queue;

int N;
int map[100][100];
int dist[100][100];
int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

queue* initQueue(int size){
    queue* q = (queue *)malloc(sizeof(queue));
    q->rear = -1;
    q->top = -1;
    q->arr = (point *)malloc(sizeof(point) * size);

    return q;
}

void freeQueue(queue* q){
    free(q->arr);
    free(q);
}

bool isEmpty(queue* q){
    return q->top == q->rear;
}

void enqueue(queue* q, point p){
    q->arr[++(q->top)] = p;
}

point dequeue(queue* q){
    return q->arr[++(q->rear)];
}

void divide(int y, int x, int num){
    queue* q = initQueue(N*N);
    enqueue(q, (point){y,x});
    map[y][x] = num;
    while(!isEmpty(q)){
        point cur = dequeue(q);
        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny >= N || nx >= N || ny < 0 || nx < 0)  continue;
            if(map[ny][nx]==1){
                map[ny][nx] = num;
                enqueue(q, (point){ny, nx});
            }
        }
    }
    freeQueue(q);
}

int buildBridge(int y, int x, int num){
    int cnt = 0;
    for(int i = 0; i < 4; i++){
        int ny = y + dy[i];
        int nx = x + dx[i];
        if(map[ny][nx]==num || ny >= N || nx >= N || ny < 0 || nx < 0)  cnt++;
    }
    if(cnt == 4) return INF;

    memset(dist, 0, sizeof(dist));

    queue* q = initQueue(N*N);
    enqueue(q, (point){y,x});
    while(!isEmpty(q)){
        point cur = dequeue(q);
        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny >= N || nx >= N || ny < 0 || nx < 0)  continue;
            if(map[ny][nx]==0 && !dist[ny][nx]){
                dist[ny][nx] = dist[cur.y][cur.x] + 1;
                enqueue(q, (point){ny, nx});
            }
            else if(map[ny][nx]!=num && !dist[ny][nx]){
                freeQueue(q);
                return dist[cur.y][cur.x];
            }
        }
    }
    freeQueue(q);
    return INF;
}

int main(){
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            scanf("%d", &map[i][j]);
        }
    }

    int num = 2;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(map[i][j]==1)    divide(i, j, num++);
        }
    }
    int ans = INF;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(map[i][j]>0)   ans = min(ans, buildBridge(i, j, map[i][j]));
        }
    }
    printf("%d", ans);
}