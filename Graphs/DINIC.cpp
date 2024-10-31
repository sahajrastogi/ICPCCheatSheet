#include <bits/stdc++.h>


typedef long long ll;

using namespace std;
//using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define pb push_back
#define f first
//#define s second
//#define int ll
#define pi pair<int,int>
#define pf pair<float,float>

struct Dinic {     // flow template
	using F = ll;  // flow type
	struct Edge {
		int to;
		F flo, cap;
	};
	int N;
	vector<Edge> eds;
	vector<vector<int>> adj;
	void init(int _N) {
		N = _N;
		adj.resize(N), cur.resize(N);
	}
	/// void reset() { trav(e,eds) e.flo = 0; }
	void ae(int u, int v, F cap, F rcap = 0) {
		assert(min(cap, rcap) >= 0);
		adj[u].pb((eds).size());
		eds.pb({v, 0, cap});
		adj[v].pb(eds.size());
		eds.pb({u, 0, rcap});
	}
	vector<int> lev;
	vector<vector<int>::iterator> cur;
	bool bfs(int s, int t) {  // level = shortest distance from source
		lev = vector<int>(N, -1);
		for(int i=0;i<N;i++) cur[i] = begin(adj[i]);
		queue<int> q({s});
		lev[s] = 0;
		while (q.size()) {
			int u = q.front();
			q.pop();
			for (auto e : adj[u]) {
				const Edge &E = eds[e];
				int v = E.to;
				if (lev[v] < 0 && E.flo < E.cap) q.push(v), lev[v] = lev[u] + 1;
			}
		}
		return lev[t] >= 0;
	}
	F dfs(int v, int t, F flo) {
		if (v == t) return flo;
		for (; cur[v] != end(adj[v]); cur[v]++) {
			Edge &E = eds[*cur[v]];
			if (lev[E.to] != lev[v] + 1 || E.flo == E.cap) continue;
			F df = dfs(E.to, t, min(flo, E.cap - E.flo));
			if (df) {
				E.flo += df;
				eds[*cur[v] ^ 1].flo -= df;
				return df;
			}  // saturated >=1 one edge
		}
		return 0;
	}
	F maxFlow(int s, int t) {
		F tot = 0;
		while (bfs(s, t))
			while (F df = dfs(s, t, numeric_limits<F>::max())) tot += df;
		return tot;
	}
};

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    // #ifndef ONLINE_JUDGE
    // freopen("file.txt", "r", stdin);
    // #endif
    int l; int r; int n; cin>>l>>r>>n;
    Dinic d;
    d.init(l+r+2);
    
    for(int i=0;i<n;i++){
        int a; int b; cin>>a>>b;
        d.ae(a+1,l+b+1,1);
    }
    for(int i=0;i<l;i++){
        d.ae(0,i+1, 1);
    }
    for(int i=0;i<r;i++){
        d.ae(i+1+l,l+r+1, 1);
    }
    
    cout<< d.maxFlow(0, l+r+1)<< "\n";
    d.bfs(0,l+r+1);

    for(int i=1;i<=l;i++){
        for(int v:d.adj[i]){
            if(d.eds[v].cap==0) continue;
            if(d.eds[v].cap==d.eds[v].flo) cout<< i-1 <<" "<< d.eds[v].to-l-1<<"\n";
        }
    }
    return 0;
    
    
}
