#include <bits/stdc++.h>
using namespace std;
template <class T> struct SegTree { // cmb(ID,b) = b
	const T ID{0};
	T cmb(T a, T b) { }
	int n; vector<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2; 
		seg.assign(2*n,ID); 
    }
	void pull(int p) { 
        seg[p] = cmb(seg[2*p],seg[2*p+1]); 
    }
	void upd(int p, T val) { // set val at position p
		seg[p += n] += val; 
        for (p /= 2; p; p /= 2) pull(p); 
        }
	T query(int l, int r) {	// zero-indexed, inclusive
		T ra = ID, rb = ID;
		for (l += n, r += n+1; l < r; l /= 2, r /= 2) {
			if (l&1) ra = cmb(ra,seg[l++]);
			if (r&1) rb = cmb(seg[--r],rb);
		}
		return cmb(ra,rb);
	}

	int bSearch(int target){
		int p = 1;
		if(seg[p] < target) return 0;
		while(p < n){
			if(seg[2*p] < target){
				p = 2*p+1;
			} else {
				p = 2*p;
			}
		}
		return p-n+1;
	}
	// int first_at_least(int lo, int val, int ind, int l, int r) { // if seg stores max across range
	// 	if (r < lo || val > seg[ind]) return -1;
	// 	if (l == r) return l;
	// 	int m = (l+r)/2;
	// 	int res = first_at_least(lo,val,2*ind,l,m); if (res != -1) return res;
	// 	return first_at_least(lo,val,2*ind+1,m+1,r);
	// }
};
