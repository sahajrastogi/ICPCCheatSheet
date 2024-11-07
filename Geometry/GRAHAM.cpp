#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;
#define pb push_back
#define f first
#define s second
#define int int64_t
#define pi pair<int,int>


pi operator-(const pi &l, const pi &r) { return {l.f - r.f, l.s - r.s}; }
int norm(const pi &p) { return (p.f*p.f) + (p.s*p.s); }  // x^2 + y^2
int cross(const pi &a, const pi &b) { return a.f * b.s - a.s * b.f; }  // cross product
int cross(const pi &p, const pi &a, const pi &b) {                      // cross product
	return cross(a - p, b - p);
}

vector<int> hullInd(const vector<pi> &v) {
    if(v.size()==0)return {};
	int ind = int(min_element(v.begin(),v.end()) - v.begin());
	vector<int> cand, hull{ind}; 
	for(int i=0;i<v.size();i++) if (v[i] != v[ind]) cand.pb(i);

	sort(cand.begin(),cand.end(), [&](int a, int b) {  // sort by angle, tiebreak by distance
		pi x = v[a] - v[ind], y = v[b] - v[ind];
		int t = cross(x, y);
		return t != 0 ? t > 0 : norm(x) < norm(y);
	});

	for(int c : cand) {  // for every point
		while (hull.size() > 1 && cross(v[end(hull)[-2]], v[hull.back()], v[c]) <= 0) {
			hull.pop_back();  // pop until counterclockwise and size > 1
		}
		hull.pb(c);
	}

	return hull;
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif

    int t; cin >> t;
    while(t--){
        vector<pi> v;
        int n; cin >> n;
        for(int i=0;i<n;i++){
            int a; int b; cin >> a >> b;
            v.pb({a,b});
        }

        vector<int> ans = hullInd(v);
        cout << ans.size() << "\n";
        for(int i : ans){
            cout << v[i].f << " " << v[i].s << "\n";
        }
    }

    
}
