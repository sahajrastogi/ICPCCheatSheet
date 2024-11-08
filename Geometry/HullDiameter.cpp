#include <bits/stdc++.h>
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
double dist(pi &a, pi &b){
    pi d = a-b; return sqrt(norm(d));
}
// db diameter2(vP P) {
// 	P = hull(P);
// 	int n = sz(P), ind = 1; T ans = 0;
// 	if (n > 1) F0R(i,n) for (int j = (i+1)%n;;ind = (ind+1)%n) {
// 		ckmax(ans, abs2(P[i]-P[ind]));
// 		if (cross(P[j]-P[i],P[(ind+1)%n]-P[ind]) <= 0) break;
// 	}
// 	return ans;
// }
// unchecked
double diameter2(vector<pi> v) {
	int n = v.size(), ind = 1; double ans = 0;
	if (n > 1) for(int i=0;i<n;i++) for (int j = (i+1)%n;;ind = (ind+1)%n) {
        if(dist(v[i],v[ind]) > ans){
            ans = dist(v[i],v[ind]);
        }
		if (cross(v[j]-v[i],v[(ind+1)%n]-v[ind]) <= 0) break;
	}
	return ans;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif

    
}
