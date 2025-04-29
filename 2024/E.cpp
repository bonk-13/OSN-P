#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct DSU{
	vector<int>p;
	vector<vector<int>>cc;
	
	DSU(int N){
		p.assign(N + 5, 0);
		cc.assign(N + 5, vector<int>());
		for(int i = 1; i <= N; i++) p[i] = i;
	}

	int par(int x){
		return (p[x] == x) ? (x) : (p[x] = par(p[x]));
	}

	void join(int a, int b){
		a = par(a); b = par(b);
		if(a == b) return;

		if(cc[a].size() < cc[b].size()) swap(a, b);
		while(!cc[b].empty()){
			cc[a].emplace_back(cc[b].back());
			cc[b].pop_back();
		}

		p[b] = a;
	}
};

int main(){	
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int N, M, K; cin >> N >> M >> K;
	vector<ll>B(N + 5), G(M + 5);
	DSU dsu(N);

	for(int i = 1; i <= N; i++) cin >> B[i], dsu.cc[i].emplace_back(B[i]);
	for(int i = 1; i <= M; i++) cin >> G[i];

	sort(G.begin() + 1, G.begin() + M + 1);

	while(K--){
		int u, v; cin >> u >> v;
		dsu.join(u, v);
	}

	const auto find = [&](int x) -> int {
		int l = 1, r = M, ret = 0;
		while(l <= r){
			int mid = (l + r)/2;
			if(G[mid] <= x){
				ret = mid;
				l = mid + 1;
			} else{
				r = mid - 1;
			}
		}

		return ret;
	};

	ll ans = 0;
	for(int i = 1; i <= N; i++){
		if(dsu.par(i) != i) continue;

		sort(dsu.cc[i].begin(), dsu.cc[i].end());
		int med = dsu.cc[i].size()/2;
		int tmp = find(dsu.cc[i][med]);

		ll tmpA = (tmp == 0) ? (1e18) : (0), tmpB = (tmp == M) ? (1e18) : (0);
		for(auto &x: dsu.cc[i]){
			if(tmp != 0) tmpA += abs(x - G[tmp]);
			if(tmp != M) tmpB += abs(x - G[tmp + 1]);
		}

		ans += min(tmpA, tmpB);
	}

	cout << ans << '\n';

	return 0;
}