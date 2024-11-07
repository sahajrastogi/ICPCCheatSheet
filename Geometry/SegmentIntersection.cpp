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
int cross(const pi &p, const pi &a, const pi &b) {   // cross product
	return cross(a - p, b - p);
}

int sn(int x){
    if (x == 0) return 0;
    return x/abs(x);
}
bool rect_int(pi p1, pi p2, pi p3, pi p4) {
	int x1, x2, x3, x4, y1, y2, y3, y4;
	x1 = min(p1.f, p2.f), x2 = max(p1.f, p2.f);
	y1 = min(p1.s, p2.s), y2 = max(p1.s, p2.s);
	x3 = min(p3.f, p4.f), x4 = max(p3.f, p4.f);
	y3 = min(p3.s, p4.s), y4 = max(p3.s, p4.s);
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
