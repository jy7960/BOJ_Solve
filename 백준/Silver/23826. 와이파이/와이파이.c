#include <stdio.h>
#include <stdlib.h>

#define MAX_N 1000

typedef struct{
    int x, y, E;
} room;

int dist(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2);
}

int main(){
    int N;
    room r[MAX_N + 1];
    
    scanf("%d", &N);
    
    scanf("%d %d %d", &r[0].x, &r[0].y, &r[0].E);
    
    for(int i = 1; i <= N; i++){
        scanf("%d %d %d", &r[i].x, &r[i].y, &r[i].E);
    }
    
    int max_speed = -1;
    
    for(int i = 1; i <= N; i++){
        int wifi = r[0].E - dist(r[0].x, r[0].y, r[i].x, r[i].y);
        if (wifi < 0) wifi = 0;
        
        for(int j = 1; j <= N; j++){
            int hot = r[j].E - dist(r[j].x, r[j].y, r[i].x, r[i].y);
            if (hot < 0) hot = 0;
            wifi -= hot;
        }
        
        if(wifi > 0){
            if(wifi > max_speed){
                max_speed = wifi;
            }
        }
    }
    
    if(max_speed == -1)
        printf("IMPOSSIBLE\n");
    else
        printf("%d\n", max_speed);

}