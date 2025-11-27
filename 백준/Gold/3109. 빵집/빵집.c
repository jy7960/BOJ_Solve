#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int ans = 0;
int Y, X;
int dx[3] = {1, 1, 1};
int dy[3] = {-1, 0, 1};
char map[10001][501];
bool visited[10001][501];

bool dfs(int y, int x){
    if(x == X - 1){
 		ans++;
		return true;
	}

 	visited[y][x] = true;

	for(int i = 0; i < 3; i++){
		int ny = y + dy[i];
		int nx = x + dx[i];

		if(ny < 0 || ny >= Y  || nx >= X || visited[ny][nx] || map[ny][nx] == 'x')  continue;
        // 길을 찾아야만 진행
		if(dfs(ny, nx)) return true;
	}

	return false;
}

int main(){
    scanf("%d %d", &Y, &X);

    for(int y = 0; y < Y; y++)  scanf("%s", map[y]);

    for(int y = 0; y < Y; y++)  dfs(y, 0);
        
    printf("%d", ans);
}