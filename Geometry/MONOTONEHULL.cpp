#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;
#define pb push_back
#define pi pair<int,int>
#define f first
#define s second
#define int int64_t


pi operator-(const pi &l, const pi &r) { return {l.f - r.f, l.s - r.s}; }
int norm(const pi &p) { return (p.f*p.f) + (p.s*p.s); }  // x^2 + y^2

int cross(const pi &a, const pi &b) { return a.f * b.s - a.s * b.f; }  // cross product
int cross(const pi &p, const pi &a, const pi &b) {                      // cross product
	return cross(a - p, b - p);
}

vector<pi> hull;
vector<pi> points;
void monotone_chain() {
	// sort with respect to the x and y coordinates
	sort(points.begin(), points.end());
	// distinct the points
	points.erase(unique(points.begin(), points.end()), points.end());
	int n = points.size();

	// 1 or 2 points are always in the convex hull
	if (n < 3) {
		hull = points;
		return;
	}

	// lower hull
	for (int i = 0; i < n; i++) {
		// if with the new point points[i], a right turn will be formed,
		// then we remove the last point in the hull and test further
		while (hull.size() > 1 &&
		       cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0)

			hull.pop_back();
		// otherwise, add the point to the hull
		hull.push_back(points[i]);
	}

	// upper hull, following the same logic as the lower hull
	auto lower_hull_length = hull.size();
	for (int i = n - 2; i >= 0; i--) {
		// we can only remove a point if there are still points left in the
		// upper hull
		while (hull.size() > lower_hull_length &&
		       cross(hull[hull.size() - 2], hull.back(), points[i]) <= 0)
			hull.pop_back();
		hull.push_back(points[i]);
	}
	// delete point[0] that has been added twice
	hull.pop_back();
}


signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // #ifndef ONLINE_JUDGE
    // freopen("file.txt", "r", stdin);
    // #endif

    int t; cin >> t;
    while(t--){
        int n; cin >> n;
        points.clear();
        hull.clear();
        for(int i=0;i<n;i++){
            int a; int b; cin >> a >> b;
            points.pb({a,b});
        }

        monotone_chain();
        cout << hull.size() << "\n";
        for(pi i : hull){
            cout << i.f << " " << i.s << "\n";
        }
        //cout << "\n---------\n";
    }

    
}
