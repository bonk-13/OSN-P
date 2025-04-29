#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAX_N = 1e6 + 5;
const int MOD = 1e9 + 7;

ll dp[MAX_N][2], pref[MAX_N];

int multi(ll a, ll b){
    return ((a % MOD) * (b % MOD)) % MOD;
}

int pangkat(ll b, ll e){
    if(e == 0) return 1;
    ll tmp = pangkat(b, e/2);

    if(e&1) return multi(multi(tmp, tmp), b);
    return multi(tmp, tmp);
}

void solve() {
    int N, M, K; cin >> N >> M >> K;
    dp[0][0] = 1;
    for(int i = 1; i < K; i++){
        dp[i][0] = (M * dp[i - 1][0]) % MOD;
        dp[i][1] = 0;
        pref[i] = (pref[i - 1] + dp[i][0]) % MOD;
    }
    
    dp[K][0] = (pangkat(M, K) - M + MOD) % MOD;
    dp[K][1] = M;
    
    pref[K] = (pref[K - 1] + dp[K][0]) % MOD;
    
    for(int i = K + 1; i <= N; i++){
        dp[i][0] = multi(M - 1, (pref[i - 1] - pref[i - K] + MOD) % MOD);
        dp[i][1] = (pangkat(M, i) - dp[i][0] + MOD) % MOD;
        pref[i] = (pref[i - 1] + dp[i][0]) % MOD;
    }

    cout << dp[N][1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int tc = 1;
    while(tc--){
        solve();
    }

    return 0;
}
