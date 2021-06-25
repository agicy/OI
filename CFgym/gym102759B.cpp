#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXLOG2N=18+1;
const int inf=0x3f3f3f3f;

int n,m;
int a[MAXN],b[MAXM];
int Maxb,Minb;
int preMaxb[MAXM],preMinb[MAXM];
int sufMaxb[MAXM],sufMinb[MAXM];

namespace ST{
	int lg[MAXN];
	int Max[MAXLOG2N][MAXN];
	inline void Init(reg int n,reg int a[]){
		lg[0]=-1;
		for(reg int i=1;i<=n;++i){
			lg[i]=lg[i>>1]+1;
			Max[0][i]=a[i];
		}
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				Max[j][i]=max(Max[j-1][i],Max[j-1][i+(1<<(j-1))]);
		return;
	}
	inline int queryMax(reg int l,reg int r){
		reg int k=lg[r-l+1];
		return max(Max[k][l],Max[k][r-(1<<k)+1]);
	}
}

struct Event{
	int x,l,r,val;
	inline Event(reg int x=0,reg int l=0,reg int r=0,reg int val=0):x(x),l(l),r(r),val(val){
		return;
	}
	inline bool operator<(const Event& a)const{
		return x<a.x;
	}
};

struct Interval{
	int l,r;
	inline Interval(reg int l=0,reg int r=0):l(l),r(r){
		return;
	}
};

vector<Event> Eadd,Edel;

inline void solve(reg int ln,reg int rn){
	if(ln>rn)
		return;
	reg int Mina=min_element(a+ln,a+rn+1)-a;
	if(a[Mina]+b[Maxb]<0)
		solve(ln,Mina-1),solve(Mina+1,rn);
	else{
		vector<Interval> V;
		reg int las=-1;
		for(reg int i=ln;i<=rn;++i)
			if(a[i]+b[Minb]<0&&las==-1)
				las=i;
			else if(a[i]+b[Minb]>=0&&las!=-1)
				V.push_back(Interval(las,i-1)),las=-1;
		if(las!=-1)
			V.push_back(Interval(las,rn));
		reg int ptr=0,lim=0;
		for(reg int i=ln;i<=rn;++i){
			while(ptr<(int)V.size()&&V[ptr].l<=i)
				lim=V[ptr++].r+1;
			Eadd.push_back(Event(i,max(lim,i),rn+1,1)),Eadd.push_back(Event(i+1,max(lim,i),rn+1,-1));
		}
	}
	return;
}

vector<int> V;

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int len,cnt,tag;
		#define len(x) unit[(x)].len
		#define cnt(x) unit[(x)].cnt
		#define tag(x) unit[(x)].tag
	};
	Node unit[MAXN<<2];
	inline void pushup(reg int k,reg int l,reg int r){
		if(tag(k))
			cnt(k)=len(k);
		else if(l!=r)
			cnt(k)=cnt(lson)+cnt(rson);
		else
			cnt(k)=0;
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		len(k)=V[r+1]-V[l];
		cnt(k)=tag(k)=0;
		if(l==r)
			return;
		build(lson,l,mid),build(rson,mid+1,r);
		return;
	}
	int L,R,val;
	inline void update(reg int k,reg int l,reg int r){
		if(L<=l&&r<=R){
			tag(k)+=val;
			pushup(k,l,r);
			return;
		}
		if(L<=mid)
			update(lson,l,mid);
		if(R>mid)
			update(rson,mid+1,r);
		pushup(k,l,r);
		return;
	}
	#undef lson
	#undef rson
	#undef mid
	#undef len
	#undef cnt
	#undef tag
}

inline ll sweepLine(vector<Event> E){
	sort(E.begin(),E.end());
	for(reg int i=0,siz=E.size();i<siz;++i)
		V.push_back(E[i].l),V.push_back(E[i].r);
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=0,siz=E.size();i<siz;++i){
		E[i].l=lower_bound(V.begin(),V.end(),E[i].l)-V.begin();
		E[i].r=lower_bound(V.begin(),V.end(),E[i].r)-V.begin();
	}
	reg ll res=0;
	SegmentTree::build(1,0,V.size()-2);
	for(reg int i=0,siz=E.size();i<siz;++i){
		if(i)
			res+=1ll*SegmentTree::unit[1].cnt*(E[i].x-E[i-1].x);
		SegmentTree::L=E[i].l,SegmentTree::R=E[i].r-1,SegmentTree::val=E[i].val;
		SegmentTree::update(1,0,V.size()-2);
	}
	return res;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	ST::Init(n,a);
	for(reg int j=1;j<=m;++j)
		b[j]=read();
	preMaxb[0]=-inf,preMinb[0]=inf;
	for(reg int j=1;j<=m;++j){
		preMaxb[j]=max(preMaxb[j-1],b[j]);
		preMinb[j]=min(preMinb[j-1],b[j]);
	}
	sufMaxb[m+1]=-inf,sufMinb[m+1]=inf;
	for(reg int j=m;j>=1;--j){
		sufMaxb[j]=max(sufMaxb[j+1],b[j]);
		sufMinb[j]=min(sufMinb[j+1],b[j]);
	}
	Maxb=max_element(b+1,b+m+1)-b,Minb=min_element(b+1,b+m+1)-b;
	Eadd.reserve(n*6),Edel.reserve(n*4);
	solve(1,n);
	for(reg int i=1;i<=n;++i){
		if(a[i]+b[1]>=0)
			continue;
		else{
			reg int _l,_r,_mid;
			_l=1,_r=m;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(a[i]+preMaxb[_mid+1]<0)
					_l=_mid+1;
				else
					_r=_mid;
			}
			reg int j=_l;
			_l=1,_r=j;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(preMinb[_mid]==preMinb[j])
					_r=_mid;
				else
					_l=_mid+1;
			}
			reg int k=_l;
			_l=1,_r=i;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(ST::queryMax(_mid,i)+b[k]<0)
					_r=_mid;
				else
					_l=_mid+1;
			}
			reg int up=_l;
			Eadd.push_back(Event(up,1,n+1,1)),Eadd.push_back(Event(i+1,1,n+1,-1));
			Edel.push_back(Event(up,1,n+1,1)),Edel.push_back(Event(i+1,1,n+1,-1));
		}
	}
	for(reg int i=n;i>=1;--i){
		if(a[i]+b[m]>=0)
			continue;
		else{

			reg int _l,_r,_mid;
			_l=1,_r=m;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(a[i]+sufMaxb[_mid]<0)
					_r=_mid;
				else
					_l=_mid+1;
			}
			reg int j=_l;
			_l=j,_r=m;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(sufMinb[_mid+1]==sufMinb[j])
					_l=_mid+1;
				else
					_r=_mid;
			}
			reg int k=_l;
			_l=i,_r=n;
			while(_l<_r){
				_mid=(_l+_r)>>1;
				if(ST::queryMax(i,_mid+1)+b[k]<0)
					_l=_mid+1;
				else
					_r=_mid;
			}
			reg int dn=_l;
			Eadd.push_back(Event(1,i,dn+1,1)),Eadd.push_back(Event(n+1,i,dn+1,-1));
			Edel.push_back(Event(1,i,dn+1,1)),Edel.push_back(Event(n+1,i,dn+1,-1));
		}
	}
	printf("%lld\n",sweepLine(Eadd)-sweepLine(Edel));
	return 0;
}