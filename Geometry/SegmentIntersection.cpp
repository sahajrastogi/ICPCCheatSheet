#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;
#define pb push_back
#define F first
#define S second
#define int int64_t
#define pi pair<int,int>


pi operator-(const pi &l, const pi &r) { return {l.F - r.F, l.S - r.S}; }
int norm(const pi &p) { return (p.F*p.F) + (p.S*p.S); }  // x^2 + y^2
int cross(const pi &a, const pi &b) { return a.F * b.S - a.S * b.F; }  // cross product
int cross(const pi &p, const pi &a, const pi &b) {   // cross product
	return cross(a - p, b - p);
}

int sn(int x){
    if (x == 0) return 0;
    return x/abs(x);
}
bool rect_int(pi p1, pi p2, pi p3, pi p4) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = min(p1.F, p2.F), x2 = max(p1.F, p2.F);
	y1 = min(p1.S, p2.S), y2 = max(p1.S, p2.S);
	x3 = min(p3.F, p4.F), x4 = max(p3.F, p4.F);
	y3 = min(p3.S, p4.S), y4 = max(p3.S, p4.S);
	return !(x2 < x3 || x4 < x1 || y2 < y3 || y4 < y1);
}

bool segmentIntersect(pi p1, pi p2, pi p3, pi p4){
    return (rect_int(p1,p2,p3,p4) && sn(cross(p1,p2,p4)) * sn(cross(p1,p2,p3)) <= 0 && sn(cross(p3,p4,p1)) * sn(cross(p3,p4,p2)) <= 0);
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    int t; cin >> t;
    while(t--){
        int x1; int y1; int x2; int y2; int x3; int y3; int x4; int y4;
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4; 
        if(segmentIntersect({x1,y1},{x2,y2},{x3,y3},{x4,y4})){
            cout << "YES";
        } else {
            cout << "NO";
        }
        cout <<"\n";

    }

    
}
