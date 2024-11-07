#include <bits/stdc++.h>
using namespace std;
#define f first
#define s second
#define pi pair<int,int>
pair<pi, int> get_line(pi a, pi b) {
	pi z = {b.f - a.f, b.s - a.s};
	swap(z.f, z.s);

	z.f *= -1;
	int g = __gcd(z.f, z.s);
	z.f /= g;
	z.s /= g;

	z = max(z, {-z.f, -z.s});
	return {z, z.f * a.f + z.s * a.s};
}
