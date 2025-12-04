#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 20
#define BOOM -9

typedef struct standard
{
    int area, rb_cnt, y, x;
} standard;

typedef struct point
{
    int y, x;
} point;

typedef struct queue
{
    int top, rear;
    point* arr;
} queue;

int ans = 0;
int N, M, R = 0;
int map[SIZE][SIZE];
bool visited[SIZE][SIZE];
int dy[4] = {-1, 1, 0, 0};
int dx[4] = {0, 0, -1, 1};
point rb[SIZE*SIZE];
standard std;

queue* initQueue(){
    queue* q = (queue *)malloc(sizeof(queue));
    q->rear = -1;
    q->top = -1;
    q->arr = (point *)malloc(sizeof(point)*SIZE*SIZE);

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

// mode 0 탐색, mode 1 블록 제거
bool bfs(queue* q, int y, int x, bool mode){
    int rb_cnt = 0;
    int tar = map[y][x];
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            if(map[y][x]==0) visited[y][x] = false;
        }
    }
    q->rear = -1;
    q->top = -1;
    visited[y][x] = true;
    enqueue(q, (point){y,x});
    if(mode)    map[y][x] = BOOM;

    while(!isEmpty(q)){
        point cur = dequeue(q);
        visited[cur.y][cur.x] = true;
        for(int i = 0; i < 4; i++){
            int ny = cur.y + dy[i];
            int nx = cur.x + dx[i];
            if(ny < 0 || nx < 0 || ny >= N || nx >= N) continue;
            if(!visited[ny][nx] && (map[ny][nx] == 0 || map[ny][nx] == tar)){
                visited[ny][nx] = true;
                enqueue(q, (point){ny, nx});
                if(map[ny][nx] == 0) rb_cnt++;
                if(mode)    map[ny][nx] = BOOM;
            }
        }
    }
    // 탐색 모드
    if(!mode){
        // 그룹이 2 미만
        if(q->top < 1){
            visited[y][x] = false;
            return false;
        }
        // 기준 정하기
        int area = (q->top)+1;
        if(area > std.area){
            std = (standard){area, rb_cnt, y, x};
        }
        else if(area == std.area){
            if(rb_cnt > std.rb_cnt) std = (standard){area, rb_cnt, y, x};
            else if(rb_cnt == std.rb_cnt){
                if(y > std.y) std = (standard){area, rb_cnt, y, x};
                else if(y == std.y){
                    if(x > std.x)   std = (standard){area, rb_cnt, y, x};
                }
            }
        }
    }
    else{
        int area = (q->top)+1;
        ans += area*area;
    }
    
    return true;
}

void gravity(){
    for(int x = 0; x < N; x++){
        int bottom = N - 1;

        for(int y = N - 1; y >= 0; y--){
            if(map[y][x] == BOOM){
                continue;
            }

            if(map[y][x] == -1){
                bottom = y - 1;
                continue;
            }

            int temp = map[y][x];
            map[y][x] = BOOM;
            map[bottom][x] = temp;
            bottom--;
        }
    }
}


void rotate(){
    int tmp[SIZE][SIZE];
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            tmp[N-1-x][y] = map[y][x];
        }
    }
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            map[y][x] = tmp[y][x];
        }
    }
}

int main(){
    scanf("%d %d", &N, &M);
    for(int y = 0; y < N; y++){
        for(int x = 0; x < N; x++){
            scanf("%d", &map[y][x]);
            if(map[y][x] == 0){
                rb[R++] = (point){y,x};
            }
        }
    }

    queue* q = initQueue();

    while(1){
        bool endFlag = true;
        std = (standard){-1, -1, -1, -1};

        memset(visited, false, sizeof(visited));
        // 탐색
        for(int y = 0; y < N; y++){
            for(int x = 0; x < N; x++){
                if(!visited[y][x] && map[y][x] > 0){
                    if(bfs(q, y, x, false)) endFlag = false;
                }
            }
        }
        if(endFlag) break;
        // 맵 지우기
        memset(visited, false, sizeof(visited));
        bfs(q, std.y, std.x, true);
        // 중력
        gravity();
        // 회전
        rotate();
        // 중력
        gravity();

    }
    printf("%d",ans);
    free(q);
    
}