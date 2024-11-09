void sos (vi& dp, int x = 1) { // x = -1 reverses
    int SZ = 31-__builtin_clz(sz(dp));
    F0R(i,SZ) F0R(j,1<<SZ) if (j&(1<<i))
        dp[j^(1<<i)] += x*dp[j];
}

vi andConv(vi a, vi b) { // a[i]*b[j] contributes to result[i&j]
    sos(a), sos(b);
    F0R(i,sz(a)) a[i] *= b[i];
    sos(a,-1); return a;
}