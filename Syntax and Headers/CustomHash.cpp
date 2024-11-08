#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define f first 
#define s second
#define pl pair<ll, ll>
struct pair_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }
     size_t operator()(const pair<pl, ll>& p) const {
        auto hash1 = hash<ll>{}(p.f.f);
        auto hash2 = hash<ll>{}(p.f.s);
        auto hash3 = hash<ll>{}(p.s);
        return hash1 ^ (hash2 << 1) ^ (hash3 << 2);
        //return splitmix64(x);
    }
};
unordered_map<pair<pl,ll>, ll, pair_hash> dp;
