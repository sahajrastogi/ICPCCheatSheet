#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second
#define pl pair<ll, ll>
struct pair_hash {
     size_t operator()(const pair<pl, ll>& p) const {
        auto hash1 = hash<ll>{}(p.f.f);
        auto hash2 = hash<ll>{}(p.f.s);
        auto hash3 = hash<ll>{}(p.s);
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
    }
};
unordered_map<pair<pl,ll>, ll, pair_hash> dp;
