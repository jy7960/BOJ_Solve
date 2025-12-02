#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a,b) (a>b?a:b)

typedef struct point
{
    int y, x;
}point;

typedef struct queue
{
    int top, rear;
    point* arr;
} queue;

queue* initQ(int size){
    queue* q = (queue *)malloc(sizeof(queue));
    q->top = -1;
    q->rear = -1;
    q->arr = (point *)malloc(sizeof(point)*size);

    return q;
}

bool isEmpty(queue* q){
    return q->rear == q->top;
}

void enqueue(queue* q, point data){
    q->top+=1;
    q->arr[q->top] = data;
}

point dequeue(queue* q){
    q->rear += 1;
    return q->arr[q->rear];
}

void freeQ(queue* q){
    free(q->arr);
    free(q);
}

int map[64][64];
bool visitied[64][64];
int N, Q, M = 1;
int cmd[1000];
int dy[4] = {-1, 0, 1, 0};
int dx[4] = {0, -1, 0, 1};
int total = 0;
int area = 0;
int powpow[7] = {1, 2, 4, 8, 16, 32, 64};

void turn2(int sy, int sx, int len){
    int tmp[64][64];
    for(int y = 0; y < len; y++){
        for(int x = 0; x < len; x++){
            tmp[sy + y][sx + x] = map[sy + y][sx + x];
        }
    }
    for(int y = 0; y < len; y++){
        for(int x = 0; x < len; x++){
            map[sy + x][sx + len - 1 - y] = tmp[sy + y][sx + x];
        }
    }
}

void turn(int cmd){
    int size = powpow[cmd];
    int sy = 0;
    int sx = 0;
    int iter = M >> cmd;
    for(int i = 0; i < iter; i++){
        sx = 0;
        for(int j = 0; j < iter; j++){
            turn2(sy, sx, size);
            sx += size;
        }
        sy += size;
    }


}

void melt(){
    int tmp[64][64];
    for(int y = 0; y < M; y++){
        for(int x = 0; x < M; x++){
            tmp[y][x] = 0;
        }
    }

    for(int y = 0; y < M; y++){
        for(int x = 0; x < M; x++){
            if(map[y][x] == 0)  continue;
            int cnt = 0;
            for(int d = 0; d < 4; d++){
                int ny = y + dy[d];
                int nx = x + dx[d];
                if(ny < 0 || nx < 0 || ny >= M || nx >= M || map[ny][nx] <= 0){
                    cnt++;
                }
                if(cnt > 1){
                    tmp[y][x] = -1;
                    total--;
                    break;
                }
            }
        }
    }

    for(int y = 0; y < M; y++){
        for(int x = 0; x < M; x++){
            map[y][x] += tmp[y][x];
        }
    }

}

int bfs(int y, int x, queue* q){
    int ret = 1;
    q->rear = -1;
    q->top = -1;
    visitied[y][x] = true;
    enqueue(q, (point){y,x});

    while(!isEmpty(q)){
        point cur = dequeue(q);
        for(int d = 0; d < 4; d++){
            int ny = cur.y + dy[d];
            int nx = cur.x + dx[d];
            if(ny < 0 || nx < 0 || ny >= M || nx >= M)  continue;
            if(map[ny][nx]>0 && !visitied[ny][nx]){
                ret++;
                visitied[ny][nx] = true;
                enqueue(q, (point){ny,nx});
            }
        }
    }
    
    return ret;
}

int main(){
    scanf("%d %d", &N, &Q);

    M = powpow[N];

    for(int y = 0; y < M; y++){
        for(int x = 0; x < M; x++){
            scanf("%d", &map[y][x]);
            total += map[y][x];
        }
    }

    for(int i = 0; i < Q; i++)  scanf("%d", &cmd[i]);

    for(int i = 0; i < Q; i++){
        turn(cmd[i]);
        melt();
    }
    queue* q = initQ(M*M);
    for(int y = 0; y < M; y++){
        for(int x = 0; x < M; x++){
            if(map[y][x] && !visitied[y][x]){
                int tmp = bfs(y,x,q);
                area = max(area, tmp);
            }
        }
    }
    freeQ(q);
    
    printf("%d\n%d", total, area);
    
}