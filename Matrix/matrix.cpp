
#include <bits/stdc++.h>
using namespace std;
#define int int64_t
#define f first
#define s second
const int MN = 505;
const int mod = 998244353;


int power(int b, int e, int m){
    if(e >= 1){
        int p = power(b, e / 2, m) % m;
        if(e%2==0){
            return (p*p)%m;
        } else {
            return (b*((p*p)%m)%m);
        }
    } else if(e == 1) {
        return (b%m);
    } else {
        return 1; 
    }
}
int inv(int b, int m){
    return power(b,m-2,m);
}
struct matrix {
    int r, c;
    double m[MN][MN];
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

    matrix operator *(const matrix &b){
        matrix res(r, b.c);
        if(c!=b.r) cout<< "bad matrix multiplication";
        for(int i=0;i<r;i++){
            for(int j=0;j<b.c;j++){
                for(int k=0;k<c;k++){
                    res.m[i][j]+=m[i][k]*b.m[k][j];
                    //res.m[i][j]%=mod;
                }
            }
        }
        return res;
    }

    void operator *=(const matrix &b){
        *this = *this * b;
        //return *this;
    }

    matrix operator ^(int e){
        matrix res(r,r);
        //matrix id(r,r);
        matrix b = *this;
        for (int i = 0; i < r; ++i)
            res.m[i][i] = 1;
        if (e == 0) return res;
        while (true) {
            if (e & 1) res *= b;
            if ((e >>= 1) == 0) break;
            b *= b;
        }
        return res;
    }

    void operator ^=(int e){
        *this = *this ^ e;
        //return *this;
    }

};
int getRow(vector<vector<int>>& m, int R, int i, int nex) {
	for(int j =nex; j<R;j++) if (m[j][i] != 0) return j;
	return -1; }
int getRow(vector<vector<double>>& m, int R, int i, int nex) {
	pair<double,int> bes{0,-1}; // find row with max abs value
	for(int j = nex; j< R;j++) bes = max(bes,{abs(m[j][i]),j}); 
	return bes.f < 1e-9 ? -1 : bes.s; }

//for determinant and rank
pair<int,int> gauss(vector<vector<int>> &m) { // convert to reduced row echelon form
	if (!m.size()) return {1,0};
	int R = m.size(), C = m[0].size(), rank = 0, nex = 0;
	int det = 1; // determinant
	for(int i=0;i<C;i++) {
		int row = getRow(m,R,i,nex);
		if (row == -1) { det = 0; continue; }
		if (row != nex) det *= -1, swap(m[row],m[nex]);
		det *= m[nex][i]; rank++;
        det %= mod;
        //det = fmod(det,mod);
        //while(det < 0) det+= mod;
		int x = inv(m[nex][i],mod); for(int k = i;k < C;k++){
            m[nex][k] *= x;
            m[nex][k] %= mod;
        }
		for(int j=0;j < R;j++) if (j != nex) {
			int v = m[j][i]; if (v == 0) continue;
			for(int k=i;k<C;k++){
                m[j][k] -= v*m[nex][k];
                m[j][k] %= mod;
                //m[j][k] = fmod(m[j][k],mod);
            } 
		}
		nex++;
	}
    // for(int i = 0; i<R;i++){
    //     for(int j=0;j<C;j++){
    //         if(m[i][j] != 0){
    //             //rank++;
    //             break;
    //         }
    //     }
    // }
	return {det,rank};
}

//for system of linear equations with in double form
void slae(vector<vector<double>> &m) { // convert to reduced row echelon form
	if (!m.size()) return;
	int R = m.size(), C = m[0].size(), nex = 0;
	for(int i=0;i<C;i++) {
		int row = getRow(m,R,i,nex);
		if (row == -1) { continue; }
		if (row != nex) swap(m[row],m[nex]);
		double x = 1/m[nex][i]; 
        for(int k = i;k < C;k++){
            m[nex][k] *= x;
        }
		for(int j=0;j < R;j++) if (j != nex) {
			double v = m[j][i]; if (v == 0) continue;
			for(int k=i;k<C;k++){
                m[j][k] -= v*m[nex][k];
            } 
		}
		nex++;
	}
}

//returns -1 for no soln, 0 for 1 soln, and 1 for infinite
int checkSoln(vector<vector<double>> &m){
    int r = m.size(); int c= m[0].size();
    int cnt = 0; bool imp = false; bool broke = false;
    for(int i = 0;i<r;i++){
        broke = false;
        for(int j = 0;j<c-1;j++){
            if(abs(m[i][j]) > 1e-9) {
                cnt++;  broke = true; break;
            }
        }
        if(!broke && abs(m[i][c-1]) > 1e-9) imp = true;
    }
    //cout << m[r-1][c-1] << "! ";
    //cout << cnt << "? ";

    if(imp) return -1;
    if(cnt < c-1) return 1;
    return 0;
}
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    while(true){
        int n; cin >> n; if(n==0)break;
        
        vector<vector<double>>mat(n,vector<double>(n+1,0));
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                cin >> mat[i][j];
            }
        }
        for(int i=0;i<n;i++){
            cin >> mat[i][n];
        }
        slae(mat);

        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n+1;j++){
        //         cout << mat[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
        //cout << checkSoln(mat); cout << "\n";
        if(checkSoln(mat) == -1){
            cout << "inconsistent";
        } else if (checkSoln(mat) == 1){
            cout << "multiple";
        } else {
            for(int i=0;i<n;i++){
                cout << mat[i][n] << " ";
            }
        }
        cout << "\n";
    }

}