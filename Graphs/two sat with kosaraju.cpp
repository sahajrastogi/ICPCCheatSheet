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
#define int int64_t
#define pi pair<int,int>
#define pf pair<float,float>


pi pts[1005];


vector<int> adj[2005];
vector<int> adjr[2005];
int visited[2005]={0};
vector<int> order;
vector<int> scc[2005];
int k = 0;

void dfs(int x){
    visited[x] = 1;
    for(auto nex : adj[x]){
        if(!visited[nex])dfs(nex);
    }
    order.push_back(x);
}

void dfsr(int x){
    visited[x] = k;
    scc[k].pb(x);
    for(auto nex : adjr[x]){
        if(!visited[nex]) dfsr(nex);
    }
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif

    int n; int r; int l; cin >> n >> r >> l;
    for(int i=0;i<l;i++){
        int a; int b; cin >> a >> b;
        pts[i] ={a,b};
    }

    for(int i=0;i<l;i++){
        for(int j=i+1;j<l;j++){
            if(pts[i].f == pts[j].f && abs(pts[j].s - pts[i].s) <= 2*r){
                adj[i+l].pb(j);
                //adj[j+l].pb(i);
                //adjr[i].pb(j+l);
                adjr[j].pb(i+l);
            }

            if(pts[i].s == pts[j].s && abs(pts[j].f - pts[i].f) <= 2*r){
                adj[i].pb(j+l);
                //adj[j].pb(i+l);
                //adjr[i+l].pb(j);
                adjr[j+l].pb(i);
            }
        } 
    }  
    


    for(int i=0;i<2*l;i++){
        if(!visited[i]) dfs(i);
    }

    reverse(order.begin(),order.end());
    for(int i=0;i<2*l;i++) visited[i]=0;

    for(int x : order){
        if(!visited[x]){
            k++;
            dfsr(x);
        }
    }

    bool good = true;
    for(int i=0;i<l;i++){
        if(visited[i] == visited[i+l]){
            good = false;
        }
    }
    if(good){
        cout << 1;
    } else {
        cout << 0;
    }
    
    // cout << k << "\n";
    // for(int i=1;i<=k;i++){
    //     cout << scc[i].size();
    //     for(auto x : scc[i]){
    //         cout << " "<<x;
    //     }
    //     if(i!=k) cout << "\n";
    // }




    
    
}
