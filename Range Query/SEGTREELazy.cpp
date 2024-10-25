
#include <bits/stdc++.h>
struct Node{
	bool isID = false;
	int sum =0;
	Node(bool x, int s) : isID(x), sum(s){}

};

struct lNode{
	bool isID = false;
	int m=1;
	int c=0;
	lNode(bool x) : isID(x){}
};

Node idnode(true,0);
lNode lazynode(true);
template <class T, class Q> struct SegTree { // cmb(ID,b) = b
	const T ID{idnode}; const Q IDQ{lazynode};
	T cmb(T a, T b) { 
        // if(a.isID) return b;
		// if(b.isID) return a;
		Node res(false,0);
		res.sum = (a.sum+b.sum)%mod;
		return res;
    }

	Q lazycmb(Q a, Q b){
		if(a.isID) return b;
		if(b.isID) return a;
		lNode res(false); 
		res.m=(a.m*b.m)%mod;
		res.c=(a.m*b.c + a.c)%mod;
		return res;
	}

	// void cmbTQ(T a, Q b){
	// 	if(b.isID) return;
	// 	if(a.isID) {

	// 	}
	// }
	int n; vector<T> seg; vector<Q> lazy;
	void init(int _n) { // upd, query also work if n = _n
		for (n = 1; n < _n; ) n *= 2; 
		seg.assign(2*n,ID); 
		lazy.assign(2*n,IDQ); 
    }

		 
	void printTree(){
		for(int i=1;i<2*n;i++){
			cout << seg[i].sum << " ";
		}
		cout << "\n";
	}
	void push(int node, int l, int r){
		seg[node].sum = ((seg[node].sum*lazy[node].m)%mod + (lazy[node].c*(r-l+1))%mod)%mod; // operation dependent
		if(l != r){
			lazy[2*node] = lazycmb(lazy[node],lazy[2*node]);
			lazy[2*node+1] = lazycmb(lazy[node],lazy[2*node+1]);
		}
		lazy[node] = IDQ;
	}
	void pull(int p) { 
        seg[p] = cmb(seg[2*p],seg[2*p+1]); 
    }

	void upd(int l, int r, Q val){
		upd(l,r,val,0,n-1,1);
	}

	void upd(int l, int r, Q val, int start, int end, int node) { 
		push(node,start,end);
		if(r < start  || l > end) return; // maybe not needed

		if(l <= start && end <= r){
			lazy[node] = val; 
			push(node,start,end);
			return; 
		}
		int mid = (start + end)/2;
		//if(start <=l && r <= mid){
			upd(l,r,val,start,mid,2*node);
		//} else {
			upd(l,r,val,mid+1,end,2*node+1);
		//}
		pull(node);
    }

	T query(int l, int r){
		return query(l,r,0,n-1,1);
	}
	T query(int l, int r, int start, int end, int node) {	// zero-indexed, inclusive
		push(node,start,end);
		if(r < start || l > end){
			return ID;
		}
		if(l <= start && end <= r){
			return seg[node];
		} else {
			int mid = (start + end)/2;
			T x = query(l,r, start, mid,2*node);
			T y = query(l,r, mid+1, end,2*node+1);
			return cmb(x,y);
		}
	}
};

