#include <bits/stdc++.h>
using namespace std;
#define all(i) i.begin(),i.end()
#define ll long long
#define sz(x) ((ll) (x).size())
#define pb push_back
#define F first
#define S second
#define V vector
#define vi vector<int>
#define vl vector<long long>
#define pi pair<int,int>
#define pl pair<long long, long long>
#define smax(a,b) (a=std::max(a, b))
#define smin(a,b) (a=std::min(a, b))
#define REP(i,a,b) for(int i = a; i <= b; i++)
#define PER(i,a,b) for(int i = a; i >= b; i--)
#define indlb(v, x) (distance((v).begin(), lower_bound((v).begin(), (v).end(), (x))))
#define indub(v, x) (distance((v).begin(), upper_bound((v).begin(), (v).end(), (x))))
struct MergeTree { // cmb(ID,b) = b
	int n; V<vi> seg; //CHANGE vi TO vl IF NECESSARY

    void cmb(int p, int l, int r) {
        int i = 0, j = 0, n1 = sz(seg[l]), n2 = sz(seg[r]);
        while(i<n1 || j<n2){
            if(j==n2 || (i!=n1 && seg[l][i]<=seg[r][j])) seg[p].pb(seg[l][i++]);
            else seg[p].pb(seg[r][j++]);
        }
    }
	void init(vi &nums) { //CHANGE vi TO vl IF NECESSARY
		for (n = 1; n < sz(nums); ) n *= 2; 
		seg.resize(2*n);
        REP(i,0,sz(nums)-1) seg[n+i].pb(nums[i]);
        PER(i,n-1,1) cmb(i, 2*i, 2*i+1);
    }
    
	int query(int l, int r, int b) {	// zero-indexed, how many elements in range [l,r] are <= b
        int l1 = l, r1 = r;
        int res = 0;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) {
                //#define indub(v, x) (distance((v).begin(), upper_bound((v).begin(), (v).end(), (x))))
                res += indub(seg[l], b);
                l++;
            }
			if (r&1){
                r--;
                res += indub(seg[r], b);
            }
		}
		return res;
	}
};
