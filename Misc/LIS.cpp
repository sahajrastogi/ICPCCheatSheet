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
#define pi pair<int,int>
#define f first
#define s second
#define int int64_t



//bool visited[200005];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    int t; cin>>t;
    while(t--){
        int n; int m; cin>>n>> m;
        vector<int> a(n);
        vector<int> b(m);
        for(int i=0;i<n;i++) cin>>a[i];
        for(int i=0;i<m;i++) cin>>b[i];
        vector<int> dp(n+5);
        vector<int> res(n);
        fill(dp.begin(),dp.end(),-1);
        dp[0]= INT_MAX;
        for(int i=n-1;i>=0;i--){
            int idx = (upper_bound(dp.begin(),dp.end(), a[i], greater<int>())-dp.begin())-1;
            if (dp[idx] == a[i]) idx--;
            res[i]=idx+1;
            dp[idx+1]=max(a[i], dp[idx+1]);
        }
        int ma = 0;
        for(int i=0;i<n;i++) ma=max(ma, res[i]);
        vector<int> inds;
        for(int i=0;i<n;i++) if(res[i]==ma) inds.pb(i);
        inds.pb(n);
        a.pb(-1);
        sort(b.begin(), b.end(), greater<int>());
        int j = 0;
        for(int i=0;i<inds.size();i++){
            while(j<m && b[j]>=a[inds[i]]){
                cout<< b[j]<<" ";
                j++;
            }
            if(i!=inds.size()-1){for(int k=inds[i];k<inds[i+1];k++){
                if(a[k] != -1) cout<< a[k]<<" ";
            }}
        }
        cout<< "\n";

    }

    
}
