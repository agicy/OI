#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;

int n,d;
ll a[MAXN];

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int Max,pos;
		#define Max(x) unit[(x)].Max
		#define pos(x) unit[(x)].pos
	};
	inline Node operator+(const Node& a,const Node& b){
		if(a.Max>=b.Max)
			return a;
		else
			return b;
	}
	Node unit[(MAXN*3)<<2];
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val,reg int id){
		if(l==r){
			if(Max(k)<val)
				Max(k)=val,pos(k)=id;
			return;
		}
		if(pos<=mid)
			update(lson,l,mid,pos,val,id);
		else
			update(rson,mid+1,r,pos,val,id);
		pushup(k);
		return;
	}
	inline Node query(reg int k,reg int l,reg int r,reg int L,reg int R){
		if(L<=l&&r<=R)
			return unit[k];
		if(L<=mid&&mid<R)
			return query(lson,l,mid,L,R)+query(rson,mid+1,r,L,R);
		else if(L<=mid)
			return query(lson,l,mid,L,R);
		else
			return query(rson,mid+1,r,L,R);
	}
	#undef lson
	#undef rson
	#undef mid
}

vector<ll> V;
int f[MAXN],from[MAXN];

int main(void){
	n=read(),d=read();
	V.resize(3*n);
	reg int p=0;
	for(reg int i=1;i<=n;++i){
		a[i]=readll();
		V[p++]=a[i]-d,V[p++]=a[i],V[p++]=a[i]+d;
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	reg int m=V.size();
	reg int ans=-1,ptr;
	for(reg int i=1,pos,L,R;i<=n;++i){
		pos=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1,L=lower_bound(V.begin(),V.end(),a[i]-d)-V.begin()+1,R=lower_bound(V.begin(),V.end(),a[i]+d)-V.begin()+1;
		SegmentTree::Node res=SegmentTree::query(1,1,m,1,L)+SegmentTree::query(1,1,m,R,m);
		f[i]=res.Max+1,from[i]=res.pos;
		if(ans<f[i])
			ans=f[i],ptr=i;
		SegmentTree::update(1,1,m,pos,f[i],i);
	}
	reg int tot=0;
	static int S[MAXN];
	while(ptr)
		S[++tot]=ptr,ptr=from[ptr];
	printf("%d\n",tot);
	for(reg int i=tot;i>=1;--i)
		printf("%d%c",S[i],i==1?'\n':' ');
	return 0;
}