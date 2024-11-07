#include <bits/stdc++.h>

typedef long long ll;
using namespace std;
#define pb push_back
#define int ll
#define pi pair<int,int>

vector<int> primes;
int sieve[1000005] = {0};
int phi[1000005];
signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
    sieve[0] =0; sieve[1] = 1;
    cout << sieve[5];
    for(int i=2;i<100000;i++){
        if(sieve[i]) continue;
        primes.pb(i);
        for(int j=i*i;j<100000;j+=i){
            sieve[j] = i;
        }
    }   
    for(int i=1;i<1000000;i++) phi[i] = i; 
    for(int i=1;i<1000000;i++){
        if(sieve[i]) continue;
        for(int j=i;j<1000000;j+=i){
            phi[j] -= phi[j]/i;
        }
    }
}
