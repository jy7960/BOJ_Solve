#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1001

int n;
char board[SIZE][SIZE];
bool check[SIZE][SIZE];

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    scanf("%d", &n);
    scanf("%s", board[0]);
    
    for(int i = 1; i < n; i++){
        for(int j = 0; j < n; j++){
            if(board[i - 1][j] != '#')  continue;
            for(int k = 0; k < 4; k++){
                int nx = i - 1 + dx[k];
                int ny = j + dy[k];
                if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
                check[nx][ny] = !check[nx][ny];
            }
        }
        
        for(int j = 0; j < n; j++){
            board[i][j] = check[i - 1][j] ? '#' : '.';
        }
        board[i][n] = '\0';
    }
    
    for(int i = 0; i < n; i++){
        printf("%s\n", board[i]);
    }
}