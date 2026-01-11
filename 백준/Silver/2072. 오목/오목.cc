#include <iostream>
using namespace std;

#define SIZE 20

int board[20][20];

int getChainCountRecursive(int y, int x, int dy, int dx, int color) {
    if (y >= SIZE || y < 1 || x >= SIZE || x < 1) {
        return 0;
    }

    if (board[y][x] == color) {
        return 1 + getChainCountRecursive(y + dy, x + dx, dy, dx, color);
    }
    return 0;
}

bool isGameOver(int y, int x, int color) {
    static int directions[4][2] = {
        {1, 0}, {0, 1}, {1, 1}, {-1, 1},
    };

    for (int i = 0; i < 4; ++i) {
        int dy = directions[i][0];
        int dx = directions[i][1];
        int count = getChainCountRecursive(y + dy, x + dx, dy, dx, color);
        count += getChainCountRecursive(y - dy, x - dx, -dy, -dx, color);

        if (count + 1 == 5) {
            return true;
        }
    }
    return false;
}


int main() {
    int N;

    cin >> N;

    for (int i = 1; i <= N; ++i) {
        int y, x;
        cin >> y >> x;

        if (isGameOver(y, x, i % 2 + 1)) {
            cout << i << endl;
            return 0;
        }
        board[y][x] = i % 2 + 1;
    }

    cout << -1 << endl;
    return 0;
}