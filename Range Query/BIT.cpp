
#include <bits/stdc++.h>
using namespace std;
int sum(int i, vector<int> &bit){
    int res = 0; while(i>=0) {res+=bit[i]; i=((i+1)&i)-1;} return res;
}
void upd(int i, int wt, vector<int> &bit){
    while(i<bit.size()) {bit[i]+=wt; i=(i+1)|i;}
}
int range(int a, int b,vector<int>&bit){
    if(a == 0) return sum(b,bit); // care for indexing
    return sum(b,bit) - sum(a-1,bit);
}


