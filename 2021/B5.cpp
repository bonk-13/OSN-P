#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;
using pii = pair<ll, ll>;

bool isLarger(pii a, pii b){
    return (a.first*b.second) > (b.first*a.second);
}

int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    ll N, M, A, B, Q; cin >> N >> M >> A >> B >> Q;

    const auto check = [&](ld x, ll k) -> pii {
        ll cnt = 0;
        pii ret = {-1, 1};

        for(int i = 1; i <= N; i++){
            //(B + j)/(A + i) <= x
            //(B + j) <= x * (A + i)
            //j <= x * (A + i) - B
            ll j = max(0LL, min(M, (ll)((x * (A + i) - B))));
            cnt += j;
            if((j > 0) && isLarger({B + j, A + i}, ret)) ret = {B + j, A + i};
            // if(cnt >= k) return ret;
        }

        if(cnt < k) ret = {-1, 1};
        return ret;
    };

    while(Q--){
        ll t; cin >> t;
        pii ans = {-1, -1};
        
        ld l = (ld)(B + 1)/(ld)(A + N), r = (ld)(B + M)/(ld)(A + 1);
        for(int i = 0; i < 65; i++){
            ld mid = (l + r)/2.0;
            auto [a, b] = check(mid, t);

            if(a != -1){
                ans = {a, b};
                r = mid;
            } else{
                l = mid;
            }
        }

        if(ans.first == -1 || ans.second == -1) assert(0);
        ll g = gcd(ans.first, ans.second);
        cout << ans.first/g << "/" << ans.second/g << '\n';
    }

    return 0;
}