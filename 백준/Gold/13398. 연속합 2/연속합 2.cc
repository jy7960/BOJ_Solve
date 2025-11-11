#include<iostream>
#include<algorithm>
using namespace std;

int a[100001];
int dp[100001][2];

int main(){
    int n;
    cin >> n;
    for(int i = 0; i < n; i++)
        cin >> a[i];
    
    int ans = a[0];
    for(int i = 0; i < n; i++){
        dp[i][0] = dp[i][1] = a[i];
        if(i == 0) continue;
        dp[i][0] = max(dp[i - 1][0] + a[i], a[i]);
        dp[i][1] = max(dp[i - 1][0], dp[i - 1][1] + a[i]);
        ans = max(ans, max(dp[i][0], dp[i][1]));
    }
    cout << ans << '\n';
    return 0;
}