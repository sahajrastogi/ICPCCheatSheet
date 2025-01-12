#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<bitset>
#include<unordered_map>
#include<algorithm>
#include<math.h>
#include<queue>
#include<iomanip>
#include<unordered_set>
#include<algorithm>
#include<numeric>
using namespace std;


#define ll long long
#define pb push_back	
#define mp make_pair
#define F first
#define S second
#define V vector
#define vi vector<int>
#define vl vector<long long>
#define vb vector<bool>
#define pi pair<int,int>
#define pl pair<long long, long long>
#define all(i) i.begin(),i.end()
#define REP(i,a,b) for(int i = a; i <= b; i++)
#define PER(i,a,b) for(int i = a; i >= b; i--)
#define sz(i) (int) i.size()

int INF = 1e8;

int tspShortestPath(const vector<vector<int> >& dist) {
    int n = dist.size();
    vector<vector<int> > dp(1 << n, vector<int>(n, INF));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = 0; 
    }
    for (int mask = 0; mask < (1 << n); mask++) {
        for (int i = 0; i < n; i++) {
            if ((mask & (1 << i)) == 0) continue;
            int currCost = dp[mask][i];
            if (currCost == INF) continue;
            for (int j = 0; j < n; j++) {
                if (mask & (1 << j)) continue;

                int nextMask = mask | (1 << j);
                int newCost  = currCost + dist[i][j];
                dp[nextMask][j] = min(dp[nextMask][j], newCost);
            }
        }
    }
    int fullMask = (1 << n) - 1;
    int ans = INF;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dp[fullMask][i]);
    }

    return ans;
}
