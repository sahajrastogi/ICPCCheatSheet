
#include <bits/stdc++.h>
using namespace std;
const int MN = 111;
const int mod = 10000;

struct matrix {
    int r, c;
    int m[MN][MN];
    matrix (int _r, int _c) : r (_r), c (_c) {
        memset(m, 0, sizeof m);
    }
    void print() {
        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j)
                cout << m[i][j] << " ";
            cout << endl;
        }
    }
    //int x[MN][MN];
    // matrix & operator *= (const matrix &o) {
    //     memset(x, 0, sizeof x);
    //     for (int i = 0; i < r; ++i)
    //         for (int k = 0; k < c; ++k)
    //             if (m[i][k] != 0)
    //             for (int j = 0; j < c; ++j) {
    //                 x[i][j] = (x[i][j] + ((m[i][k] * o.m[k][j]) % mod))% mod;
    //             }
    //             memcpy(m, x, sizeof(m));
    //     return *this;
    // } //m*=n -> m=m*n

    matrix operator *(const matrix &b){
        matrix res(r, b.c);
        if(c!=b.r) cout<< "bad matrix multiplication";
        for(int i=0;i<r;i++){
            for(int j=0;j<b.c;j++){
                for(int k=0;k<c;k++){
                    res.m[i][j]+=m[i][k]*b.m[k][j];
                    res.m[i][j]%=mod;
                }
            }
        }
        return res;
    }

    matrix operator *=(const matrix &b){
        *this = *this * b;
        return *this;
    }
};
void matrix_pow(matrix b, long long e, matrix &res) {
    memset(res.m, 0, sizeof res.m);
    for (int i = 0; i < b.r; ++i)
        res.m[i][i] = 1;
    if (e == 0) return;
    while (true) {
        if (e & 1) res *= b;
        if ((e >>= 1) == 0) break;
        b *= b;
    }
}

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif

    
    
}
