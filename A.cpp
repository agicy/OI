#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];

namespace Subtask1{
	const int MAXN=1e3+5;
	struct Node{
		ll sum,lMax,rMax,Max;
		inline Node(reg ll sum=0,reg ll lMax=0,reg ll rMax=0,reg ll Max=0):sum(sum),lMax(lMax),rMax(rMax),Max(Max){
			return;
		}
		inline Node operator+(const Node& a)const{
			Node res;
			res.sum=sum+a.sum,
			res.lMax=max(lMax,sum+a.lMax),
			res.rMax=max(a.rMax,a.sum+rMax),
			res.Max=max(max(Max,a.Max),rMax+a.lMax);
			return res;
		}
	};
	inline void Solve(void){
		reg ull ans=0;
		for(reg int i=1;i<=n;++i){
			Node tmp=Node(a[i],a[i],a[i],a[i]);
			ans+=a[i];
			for(reg int j=i+1;j<=n;++j){
				tmp=tmp+Node(a[j],a[j],a[j],a[j]);
				ans+=tmp.Max;
			}
		}
		printf("%llu\n",ans);
		return;
	}
}

namespace Subtask2{
	inline void Solve(void){
		reg ull ans=0;
		for(reg int i=1;i<=n;++i){
			reg int lef=i,rig=n-i+1;
			ans+=1ull*lef*rig*a[i];
		}
		printf("%llu\n",ans);
	}
}

namespace Subtask3{
	namespace SegmentTree{
		#define lson ( (k) << 1 )
		#define rson ( (k) << 1 | 1 )
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int plMax,prMax;
			int lef,rig;
			ll sum,lMax,rMax,Max;
			inline Node operator+(const Node& a)const{
				Node res;
				res.sum=sum+a.sum;
				if(lMax<sum+a.lMax)
					res.lMax=sum+a.lMax,res.plMax=a.plMax;
				else
					res.lMax=lMax,res.plMax=plMax;
				if(a.rMax<a.sum+rMax)
					res.rMax=a.sum+rMax,res.prMax=prMax;
				else
					res.rMax=a.rMax,res.prMax=a.prMax;
				res.Max=Max,res.lef=lef,res.rig=rig;
				if(res.Max<a.Max)
					res.Max=a.Max,res.lef=a.lef,res.rig=a.rig;
				if(res.Max<rMax+a.lMax)
					res.Max=rMax+a.lMax,res.lef=prMax,res.rig=a.plMax;
				return res;
			}
			#define sum(x) unit[(x)].sum
			#define lMax(x) unit[(x)].lMax
			#define rMax(x) unit[(x)].rMax
			#define Max(x) unit[(x)].Max
			#define lef(x) unit[(x)].lef
			#define rig(x) unit[(x)].rig
			#define plMax(x) unit[(x)].plMax
			#define prMax(x) unit[(x)].prMax
		};
		Node unit[MAXN<<2];
		inline void pushup(reg int k){
			unit[k]=unit[lson]+unit[rson];
			return;
		}
		inline void build(reg int k,reg int l,reg int r,reg int a[]){
			if(l==r){
				lef(k)=rig(k)=plMax(k)=prMax(k)=l;
				sum(k)=lMax(k)=rMax(k)=Max(k)=a[l];
				return;
			}
			build(lson,l,mid,a),build(rson,mid+1,r,a);
			pushup(k);
			return;
		}
		inline void update(reg int k,reg int l,reg int r,reg int pos,reg int val){
			if(l==r){
				lef(k)=rig(k)=plMax(k)=prMax(k)=l;
				sum(k)=lMax(k)=rMax(k)=Max(k)=val;
				return;
			}
			if(pos<=mid)
				update(lson,l,mid,pos,val);
			else
				update(rson,mid+1,r,pos,val);
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
		#undef sum
		#undef lMax
		#undef rMax
		#undef Max
	}
	ull ans=0;
	inline void solve(reg int l,reg int r){
		if(l>r)
			return;
		if(l==r){
			ans+=a[l];
			return;
		}
		SegmentTree::Node tmp=SegmentTree::query(1,1,n,l,r);
		reg int lef=tmp.lef,rig=tmp.rig;
		ans+=1ull*(lef-l+1)*(r-rig+1)*tmp.Max;
		solve(l,lef-1),solve(lef+1,rig-1),solve(rig+1,r);
		return;
	}
	inline void Solve(void){
		SegmentTree::build(1,1,n,a);
		solve(1,n);
		printf("%llu\n",ans);
		return;
	}
}

int main(void){
	n=read();
	reg bool f2=true;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(a[i]<0)
			f2=false;
	}
	if(n<=1000)
		Subtask1::Solve();
	else if(f2)
		Subtask2::Solve();
	else
		Subtask3::Solve();
	return 0;
}