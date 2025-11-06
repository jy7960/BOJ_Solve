#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define SIZE 3000
#define min(a,b) (a>b?b:a)
#define max(a,b) (a>b?a:b)

typedef struct point{
    int x;
    int y;
}point;

typedef struct line{
    point p1;
    point p2;
} line;

int parent[SIZE];
int group[SIZE];
line l[SIZE];

int find(int x){
    if(parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

void unite(int a, int b){
    a = find(a);
    b = find(b);
    if(a != b){
        parent[b] = a;
        group[a] += group[b];
    }
}

int ccw(point a, point b, point c){
    int ccw = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
    if(ccw>0)       return 1;
    else if(ccw<0)  return -1;
    return 0;
}

bool isIntersect(line l1, line l2){
    point a = l1.p1, b = l1.p2, c = l2.p1, d = l2.p2;
    int ab = ccw(a, b, c) * ccw(a, b, d);
    int cd = ccw(c, d, a) * ccw(c, d, b);

    if(ab == 0 && cd == 0){
        if(max(a.x, b.x) < min(c.x, d.x) || max(c.x, d.x) < min(a.x, b.x) ||
            max(a.y, b.y) < min(c.y, d.y) || max(c.y, d.y) < min(a.y, b.y)){
            return false;
        }
        return true;
    }
    return ab <= 0 && cd <= 0;

}

int main(){
    int N;
    scanf("%d", &N);
    for(size_t i = 0; i < N; i++){
        scanf("%d %d %d %d", &l[i].p1.x, &l[i].p1.y, &l[i].p2.x, &l[i].p2.y);
        parent[i] = i;
        group[i] = 1;    
    }
    for(size_t i = 0; i < N; i++){
        for(size_t j = i+1; j < N; j++){
            if(isIntersect(l[i], l[j])) 
                unite(i, j);
        }
    }
    int cnt = 0;
    int maxSize = 0;
    for (int i = 0; i < N; i++) {
        if (parent[i] == i) {
            cnt++;
            if (group[i] > maxSize) {
                maxSize = group[i];
            }
        }
    }
    printf("%d\n%d\n", cnt, maxSize);
}