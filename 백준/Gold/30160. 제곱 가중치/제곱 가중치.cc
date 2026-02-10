#include <iostream>
#include <vector>

#define FASTIO ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
using namespace std;

int main(){
    FASTIO
    int N;
    cin >> N;

	long res = 0, t = 0, s = 0;
	while(N--){
		int x; cin >> x;
        t += 2 * s + x;
		res += t;
        s += x;
		cout << res << ' ';
	}
}