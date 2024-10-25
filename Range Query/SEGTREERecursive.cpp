#include <bits/stdc++.h>
template <class T> struct SegTree { // cmb(ID,b) = b
	const T ID{0}; T cmb(T a, T b) { 
        if(a == ID){
			return b;
		} 
		if(b == ID){
			return a;
		}
		return min(a,b);
    }

	int n; vector<T> seg;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2; 
		seg.assign(2*n,ID); 
    }
	void pull(int p) { 
        seg[p] = cmb(seg[2*p],seg[2*p+1]); 
    }
	void upd(int p,T val) upd(p, val,0,n-1,1);
	void upd(int p, T val, int start, int end, int node) { // set val at position p

		if(p < start  || p > end) return; // maybe not needed

		if(start == end){
			seg[node] = val;
			return;
		}

		int mid = (start + end)/2;
		if(start <=p && p <= mid){
			upd(p,val,start,mid,2*node);
		} else {
			upd(p,val,mid+1,end,2*node+1);
		}
		pull(node);
    }

	T query(int l, int r) query(l,r,1,0,n-1)
	T query(int l, int r, int node, int start, int end) {	// zero-indexed, inclusive

		if(r < start || l > end){
			return ID;
		}
		if(l <= start && end <= r){
			return seg[node];
		} else {
			int mid = (start + end)/2;
			T x = query(l,r,2*node, start, mid);
			T y = query(l,r,2*node+1, mid+1, end);
			return cmb(x,y);
		}
	}
};


