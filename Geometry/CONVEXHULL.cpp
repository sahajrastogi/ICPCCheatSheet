/*
ID: sahajrastogi
LANG: C++11
*/

#include <iostream>
#include <bits/stdc++.h>
#include <unordered_set>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

typedef long long ll;

using namespace std;
//using namespace __gnu_pbds;
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update>
#define pb push_back
#define f first
#define s second
//#define int int64_t
//#define float double
#define pi pair<int,int>
#define pf pair<float,float>


vector<pi> points;
vector<pi> hull;
int n;


int area(pi O, pi P, pi Q) {
	return (P.first - O.first) * (Q.second - O.second) -
	       (P.second - O.second) * (Q.first - O.first);
}

void convexHull(){
    sort(points.begin(), points.end());

    if(n <= 2) {
        hull = points;
        return;
    }
    for(int i=0;i<n;i++){
        while(hull.size() > 1 && area(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) < 0){
            hull.pop_back();
        }
        hull.pb(points[i]);
    }

    int x = hull.size();
    
    for(int i=n-2;i>=0;i++){

        while(hull.size() > x && area(hull[hull.size() - 2], hull[hull.size() - 1], points[i]) > 0){
            hull.pop_back();
        }
        hull.pb(points[i]);
    }
    hull.pop_back();
    
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    cin >> n;
    for(int i=0;i<n;i++){
        int a; int b; cin >> a >> b;
        points.pb({a,b});
    }

    convexHull();
    for(pi x : hull){
        cout << x.f << " " << x.s << "\n";
    }
    

    
}
