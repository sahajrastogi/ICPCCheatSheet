#include <bits/stdc++.h>
#include <unordered_set>

using namespace std;
#define pb push_back
#define f first
#define s second
#define int int64_t
#define pi pair<int,int>

//area is signed
int twiceArea(vector<pi>pts){
    int ans = 0;
    for(int i=0;i<pts.size()-1;i++){
        ans += pts[i].f * pts[i+1].s - pts[i].s * pts[i+1].f;
    }
    ans += pts.back().f *pts[0].s - pts.back().s * pts[0].f;
    return ans;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    int n; cin >> n;
    vector<pi> pts;
    for(int i=0;i<n;i++){
        int a; int b; cin >> a >> b; pts.pb({a,b});
    }
    cout << abs(twiceArea(pts)); // maybe use labs here
}
