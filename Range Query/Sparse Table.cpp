#include <bits/stdc++.h>
using namespace std;

int main(){
    vector<int> a;
    vector<vector<int>> Maxs(0, vector<int>(17, 0)); //arr.size, log2(arr.size);
    for(int i=(int)a.size()-1;i>=0;i--){
        Maxs[i][0] = 0; //fill in arr[i]
        for(int j=0; i+(1<<(j+1))-1 <a.size() ;j++){
            Maxs[i][j+1] = max(Maxs[i][j], Maxs[i+(1<<j)][j]);
        }
    }

    // int query(int l, int r) {
    // int k = log2(e- b + 1);
    // return max(Maxs[b][k], Maxs[e + 1- (1<<k)][k]);
    // }
};


