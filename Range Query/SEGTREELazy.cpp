
#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
#define pb push_back
#define f first
#define s second
#define int ll
#define pi pair<int,int>

struct Node{
	bool isID = false;
	int sum =0;
	Node(bool x) : isID(x){}
	Node(bool x, int s) : isID(x), sum(s){}
};

struct lNode{
	bool isID = false;
	int set = -1;
	int inc = 0;
	lNode(bool x) : isID(x){}
	lNode(bool x, int a, int b): isID(x), set(a), inc(b){}
};

Node idnode(true,0);
lNode lazynode(true);
template <class T, class Q> struct SegTree { // cmb(ID,b) = b
	const T ID{idnode}; const Q IDQ{lazynode};
	T cmb(T a, T b) { 
        if(a.isID) return b;
		if(b.isID) return a;
		Node res(false,0);
		res.sum = (a.sum+b.sum);
		return res;
    }

	Q lazycmb(Q a, Q b){
		if(a.isID) return b;
		if(b.isID) return a;
		lNode res(false); 
		if(a.set != -1) return a;
		res.set = b.set;
		res.inc = b.inc + a.inc;
		return res;
	}

	T cmbTQ(T a, Q b,int l,int r){
		if(b.isID) return a;
		Node res(false);
		if(a.isID) {
			res.sum = 0;
		} else {
			res.sum = a.sum;
		}
		if(b.set != -1) res.sum = b.set*(r-l+1);
		res.sum += b.inc*(r-l+1);
		return res;
	}
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
		//seg[node].sum = ((seg[node].sum*lazy[node].m)%mod + (lazy[node].c*(r-l+1))%mod)%mod; // operation dependent
		seg[node] = cmbTQ(seg[node],lazy[node], l,  r);
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

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    #ifndef ONLINE_JUDGE
    freopen("file.txt", "r", stdin);
    #endif
	int n; int q; cin >> n >> q;
	SegTree<Node,lNode> seg;
	seg.init(n+5);
	for(int i=0;i<n;i++){
		int x; cin >> x; seg.upd(i,i,lNode(false,x,0));
	}
	// for(int i=0;i<n;i++){
	// 	cout << seg.seg[0].sum;
	// }
	for(int i=0;i<q;i++){
		int k; cin >> k;
		if(k==1){
			int a; int b; int x; cin >> a >> b >>x;a--;b--;
			seg.upd(a,b,lNode(false, -1 , x));
		} else if(k==2){
			int a; int b; int x; cin >> a >> b >>x;a--;b--;
			seg.upd(a,b,lNode(false, x , 0));
		} else {
			int a; int b; cin >> a >> b;a--;b--;
			cout << seg.query(a,b).sum << "\n";
		}
	}	
    
}
