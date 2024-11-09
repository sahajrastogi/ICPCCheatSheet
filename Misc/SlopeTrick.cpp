/*
From the latter link (modified):

Slope trick is a way to represent a function that satisfies the following conditions:

It can be divided into multiple sections, where each section is a linear function (usually) with an integer slope.
It is a convex/concave function. In other words, the slope of each section is non-decreasing or non-increasing when scanning the function from left to right.
It's generally applicable as a DP optimization.
Let $dp[i][j]$ denote the maximum amount of money you can have on day $i$ if you
have exactly $j$ shares of stock on that day. The final answer will be
$dp[N][0]$. This solution runs in $\mathcal{O}(N^2)$ time.

Copyvector<vl> dp = {{0}};int N;
int main() {	re(N);	F0R(i, N) {		int x;		re(x);		dp.pb(vl(i + 2, -INF));		F0R(j, i + 1) {

If we run this on the first sample case, then we get the following table:

Input:

9
10 5 4 7 9 12 6 2 10

Output:

dp[0] = {  0}
dp[1] = {  0, -10}
dp[2] = {  0,  -5, -15}
dp[3] = {  0,  -4,  -9, -19}
dp[4] = {  3,  -2,  -9, -16, -26}
dp[5] = {  7,   0,  -7, -16, -25, -35}
dp[6] = { 12,   5,  -4, -13, -23, -35, -47}
dp[7] = { 12,   6,  -1, -10, -19, -29, -41, -53}
dp[8] = { 12,  10,   4,  -3, -12, -21, -31, -43, -55}
dp[9] = { 20,  14,   7,  -2, -11, -21, -31, -41, -53, -65}

However, the DP values look quite special! Specifically, let

$$dif[i][j]=dp[i][j]-dp[i][j+1]\ge 0.$$

Then $dif[i][j]\le dif[i][j+1]$ for all $j\ge 0$. In other words, $dp[i][j]$ as
a function of $j$ is concave down.

Full Solution

We'll process the shares in order. Suppose that we are currently considering the
$i$-th day, where shares are worth $p_i$. We can replace (buy or sell a share)
in the statement with (buy, then sell somewhere between 0 and 2 shares).


If we currently have $j$ shares and overall balance $b$, then after buying,
$j$ increases by one and $b$ decreases by $p_i$. So we set
$dp[i][j]=dp[i-1][j-1]-p_i$ for all $j$. Note that the differences between
every two consecutive elements of $dp[i]$ have not changed.


If we choose to sell a share, this is equivalent to setting
$dp[i][j]=\max(dp[i][j],dp[i][j+1]+p_i)$ for all $j$ at the same time. By the
concavity condition, $dp[i][j]=dp[i][j+1]+p_i$ will hold for all $j$ less than
a certain threshold while $dp[i][j]$ will remain unchanged for all others. So
this is equivalent to inserting $p_i$ into the list of differences while
maintaining the condition that the differences are in sorted order.


So choosing to sell between 0 and 2 shares is represented by adding $p_i$ to
the list of differences two times. After that, we should pop the smallest
difference in the list because we can't end up with a negative amount of
shares.



Example

The implementation is quite simple; maintain a priority queue representing
$dif[i]$ that allows you to pop the minimum element. After adding $i$ elements,
$ans$ stores the current value of $dp[i][i]$. At the end, you add all the
differences in $dif[N]$ to go from $dp[N][N]$ to $dp[N][0]$.

Copy#include <bits/stdc++.h>using namespace std;
int main() {	int N;	cin >> N;	priority_queue<int, vector<int>, greater<int>> pq;	long long ans = 0;	for (int i = 0; i < N; ++i) {		int p;

Extension

Stock Trading (USACO Camp): What if your amount of shares can go negative, but
you can never have more than $L$ shares or less than $-L$?

Potatoes & Fertilizers

2019 - Potatoes & FertilizersLMiO - NormalFocus Problem – try your best to solve this problem before continuing!

Simplifying the Problem

Instead of saying that moving fertilizer from segment $i$ to segment $j$ costs
$|i-j|$, we'll say that it costs $1$ to move fertilizer from a segment to an
adjacent segment.

Let the values of $a_1,a_2,\ldots,a_N$ after all the transfers be
$a_1',a_2',\ldots,a_N'$. If we know this final sequence, how much did the
transfers cost (in the best case scenario)? It turns out that this is just

$$C=\sum_{i=1}^{N-1}\left|\sum_{j=1}^i(a_j-a_j')\right|.$$

We can show that this is a lower bound and that it's attainable. The term
$D=\sum_{j=1}^i(a_j-a_j')$ denotes the number of units of fertilizer that move
from segment $i$ to segment $i+1$. Namely, if $D$ is positive then $D$ units of
fertilizer moved from segment $i$ to segment $i+1$; otherwise, $-D$ units of
fertilizer moved in the opposite direction. Note that it is never optimal to
have fertilizer moving in both directions.

Let $dif_i=a_i-b_i$ and define $d_j=\sum_{i=1}^jdif_i$ for each $0\le j\le N$.
Similarly, define $dif_i'=a_i'-b_i$ and $d_j'=\sum_{i=1}^jdif_i'$. Since we want
$dif_i'\ge 0$ for all $i$, we should have
$d_0=d_0'\le d_1'\le \cdots\le d_N'=d_N.$ Conversely, every sequence
$(d_0',d_1',\ldots,d_N')$ that satisfies this property corresponds to a valid
way to assign values of $(a_1',a_2',\ldots,a_N')$.

Now you can verify that $C=\sum_{i=1}^{N-1}|d_i-d_i'|$. This makes sense since
moving one unit of fertilizer one position is equivalent to changing one of the
$d_i$ by one (although $d_0,d_N$ always remain the same).

Slow Solution

For each $0\le i\le N$ and $0\le j\le d_N$, let $dp[i][j]$ be the minimum cost
to determine $d_0',d_1',\ldots,d_i'$ such that $d_i'\le j$. Note that by
definition, $dp[i][j]\ge dp[i][j+1]$. We can easily calculate these values in
$\mathcal{O}(N\cdot d_N)$ time.

Full Solution

Similar to before, this DP is concave up for a fixed $i$! Given a piecewise
linear function $f_i(x)$ that takes as input $x$ and outputs $dp[i][x]$, we need
to support the following two operations to transform this function into
$f_{i+1}$.

Add $|x-k|$ to the function for some $k$
Set $f(x)=\min(f(x),f(x-1))$ for all $x$


Again, these can be done with a priority queue. Instead of storing the
consecutive differences, we store the points where the slope of the piecewise
linear function changes by one.

The first operation corresponds to inserting $k$ into the priority queue two
times because the slope increases by two at $x=k$.
The latter operation just corresponds to removing the greatest element of the
priority queue.


This solution runs in $\mathcal{O}(N\log N)$ time.

Copy#include <bits/stdc++.h>using namespace std;
typedef long long ll;
int N;ll fst = 0;                 // value of DP function at 0priority_queue<ll> points;  // points where DP function changes slope
int main() {


*/

vector<vl> dp = {{0}};
int N;

int main() {
	re(N);
	F0R(i, N) {
		int x;
		re(x);
		dp.pb(vl(i + 2, -INF));
		F0R(j, i + 1) {
			ckmax(dp.bk[j + 1], dp[sz(dp) - 2][j] - x);
			ckmax(dp.bk[j], dp[sz(dp) - 2][j]);
			if (j) ckmax(dp.bk[j - 1], dp[sz(dp) - 2][j] + x);
		}
	}
	int cnt = 0;
	trav(t, dp) {
		pr("dp[", cnt++, "] = ");
		pr('{');
		F0R(i, sz(t)) {
			if (i) cout << ", ";
			cout << setw(3) << t[i];
		}
		ps('}');
	}
}