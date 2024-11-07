#include <bits/stdc++.h>
using namespace std;
#define int long long
//tested very little
void ext_euclid(int a, int  b, int &x, int &y, int &g) {
    x = 0, y = 1, g = b;
    int m, n, q, r;
    for (int u = 1, v = 0; a != 0; g = a, a = r) {
    q = g / a, r = g % a;
    m = x- u * q, n = y- v * q;
    x = u, y = v, u = m, v = n;
    }
 }
int mod_inv(int n, int m) {
    int x, y, gcd;
    ext_euclid(n, m, x, y, gcd);
    if (gcd != 1)
    return 0;
    return (x + m) % m;
}

