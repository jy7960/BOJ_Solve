#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define max(a,b) (a>b?a:b)
#define min(a,b) (a>b?b:a)

typedef struct point
{
    int y,x;
} point;

typedef struct queue
{
    int top, rear;
    point* arr;
} queue;

int N, M, V = 0, R = 0;
int ans = 9999;
int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, -1, 0, 1};
char map[50][50];
int map2[50][50];
bool visitied[50][50];
point virus[10];
point tmp[10];
bool tmpCheck[10];

queue* initQueue(int size){
    queue* q = (queue *)malloc(sizeof(queue));
    q->rear = -1;
    q->top = -1;
    q->arr = (point *)malloc(sizeof(point)*size);

    return q;
}

void freeQ(queue *q){
    free(q->arr);
    free(q);
}

bool isEmpty(queue *q){
    return q->rear==q->top;
}

void enqueue(queue* q, point p){
    q->arr[++q->top] = p;
}

point dequeue(queue* q){
    return q->arr[++q->rear];
}

int bfs(){
    memset(visitied, false, 2500*sizeof(bool));
    memset(map2, 0, 2500*sizeof(int));
    int ret = 0;
    int r = V;
    queue* q = initQueue(N*N);
    for(int i = 0; i < M; i++){
        enqueue(q, tmp[i]);
        visitied[tmp[i].y][tmp[i].x] = true;
    }
    
    while(!isEmpty(q) && r < R){
        point cur = dequeue(q);
        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N)  continue;
            if(!visitied[ny][nx] && map[ny][nx] != '1'){
                visitied[ny][nx] = true;
                map2[ny][nx] = map2[cur.y][cur.x] + 1;
                if(map[ny][nx] == '0'){
                    r++;
                    ret = max(ret, map2[ny][nx]);
                }
                enqueue(q, (point){ny, nx});
            }
        }
    }
    freeQ(q);
    if(r==R)    return ret;
    return 9999;
}

void solve(int m, int s){
    if(m==M){
        ans = min(ans, bfs());
        return;
    }
    for(int i = s; i < V; i++){
        if(!tmpCheck[i]){
            tmpCheck[i] = true;
            tmp[m] = virus[i];
            solve(m+1, i+1);
            tmpCheck[i] = false;
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf(" %c", &map[y][x]);
            if(map[y][x]!='1')    R++;
            if(map[y][x]=='2'){
                virus[V].y = y;
                virus[V++].x = x;
            }
        }
    }
    solve(0, 0);
    printf("%d", ans==9999? -1 : ans);

}