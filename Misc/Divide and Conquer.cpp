/*
Consider a dynamic programming problem with the following formula

$$dp(i,j) = \min_{0\leq k \leq j} ( dp(i-1, k-1) + C(k,j)),$$

where $C(i,j)$ is a cost function and you can compute it in $O(1)$ time.
Furthermore, $dp(i,j) =0$ for $j<0$.

The straightforward implementation gives a runtime of $O(MN^2)$ if $0\leq i < M$ and $0\leq j < N$.
Divide & Conquer DP allows this to be optimized to $O(M N \log N)$.

For each $i,j$, let $\text{opt}(i,j)$ be the value of $k$ that minimizes the right hand side of the equation.
Divide & Conquer DP only applies if

$$\text{opt}(i,j) \leq \text{opt}(i,j+1).$$

Often, proving this with the given cost function is challenging,
but if the cost function satisfies the quadrangle inequality, the condition holds.

We can then apply the idea behind Divide & Conquer.
Fix a given $i$. First, compute $\text{opt}(i,n/2)$.
Then compute $\text{opt}(i, n/4)$ using the fact that it is less than or equal to $\text{opt}(i, n/2)$.
Similarly, we can compute $\text{opt}(i, 3n/4)$ and recursively split the ranges in half, keeping track on the lower and upper bounds.

Since each possible value of $\text{opt}(i, j)$ appears $O(\log n)$ times, this gives a final runtime of $O(mn \log n)$.*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

const int MAX_N = 1000;
const int MAX_K = 7;

// calc[i][j] stores the # of steps to get all cows distance j away to door i
// to make implementing a cyclic array easier, we double the size
vector<vector<ll>> calc(2 * MAX_N, vector<ll>(MAX_N + 1, 0));
// dp[i][j] stores the answer for doors 0,1,.., j and i doors open
vector<vector<ll>> dp(MAX_K + 1, vector<ll>(MAX_N + 1, INT64_MAX));

int rot;

void compdp(int k, int begin, int end, int rl, int rr) {
	// fixed k, begin and end are the ends of the array, rl and rr are the
	// bounds on the last door used
	int mid = (begin + end) / 2;

	ll best = INT64_MAX;
	int best_last = -1;
	// best is min amount moved, last is the last door used
	for (int last = rl; last <= min(mid, rr); last++) {
		ll cost = dp[k - 1][last - 1] + calc[last + rot][mid - last + 1];
		if (cost < best) {
			best = cost;
			best_last = last;
		} else if (cost == best && last < best_last) {
			best_last = last;
		}
	}
	dp[k][mid] = best;
	if (begin == end) { return; }
	compdp(k, begin, mid, rl, best_last);
	compdp(k, mid + 1, end, best_last, rr);
}

int main() {
	freopen("cbarn.in", "r", stdin);
	int n, k;
	cin >> n >> k;

	vector<int> a(2 * n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
		a[i + n] = a[i];
	}

	for (int i = 0; i < n; i++) {
		for (int j = 1; j <= n; j++) {
			calc[i][j] = calc[i + n][j] = calc[i][j - 1] + (ll)a[i + j - 1] * (j - 1);
		}
	}

	// rotate stores where we start in the linear representation
	ll ans = INT64_MAX;
	for (rot = 0; rot < n; rot++) {
		for (int i = 0; i < n; i++) { dp[0][i] = calc[rot][i + 1]; }
		for (int i = 1; i < k; i++) {
			for (int j = 0; j < n; j++) { dp[i][j] = INT64_MAX; }
			compdp(i, i, n - 1, i, n - 1);
		}
		ans = min(ans, dp[k - 1][n - 1]);
	}

	freopen("cbarn.out", "w", stdout);
	cout << ans << endl;
}

void divide(int lo, int hi, int L, int R) {
    if (lo > hi) return;
    int mid = (lo+hi)/2;
    pair<ll,int> tmp = {1e18,-1};
    FOR(i,max(mid+1,L),R+1) 
    	tmp = min(tmp,{calc(0,mid)+calc(mid+1,i)
    		+calc(i+1,n),i}); // find lowest optimal index
    ans = min(ans,tmp.f);
    divide(lo,mid-1,L,tmp.s); // assume optimal index is non-decreasing
    divide(mid+1,hi,tmp.s,R);
}