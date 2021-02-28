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

const int MAXN=1e5+5;
const int MAXA=1e9;
const int mod=1e9+7;
const int inf=0x3f3f3f3f;

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

inline int inv(reg int x){
	return fpow(x,mod-2);
}

struct Data{
	int cnt,pod;
	inline Data(reg int cnt=0,reg int pod=1):cnt(cnt),pod(pod){
		return;
	}
};

inline Data operator+(const Data& a,const Data& b){
	Data res;
	res.cnt=a.cnt+b.cnt;
	res.pod=1ll*a.pod*b.pod%mod;
	return res;
}

namespace BIT{
	namespace SegmentTree{
		const int MAXSIZE=MAXN*200;
		#define mid ( ( (l) + (r) ) >> 1 )
		struct Node{
			int lson,rson;
			Data dat;
			#define lson(x) unit[(x)].lson
			#define rson(x) unit[(x)].rson
			#define dat(x) unit[(x)].dat
		};
		int tot;
		Node unit[MAXSIZE];
		inline void Init(void){
			dat(0)=Data(0,1);
			return;
		}
		inline int New(void){
			reg int p=++tot;
			dat(p)=Data(0,1);
			return p;
		}
		inline void pushup(reg int p){
			dat(p)=dat(lson(p))+dat(rson(p));
			return;
		}
		inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
			if(!p)
				p=New();
			if(l==r){
				dat(p).cnt+=val;
				dat(p).pod=fpow(l,dat(p).cnt);
				return;
			}
			else{
				if(pos<=mid)
					update(lson(p),l,mid,pos,val);
				else
					update(rson(p),mid+1,r,pos,val);
			}
			pushup(p);
			return;
		}
		inline int queryCnt(reg int p,reg int l,reg int r,reg int pos){
			if(!p)
				return 0;
			if(l==r)
				return dat(p).cnt;
			if(pos<=mid)
				return queryCnt(lson(p),l,mid,pos);
			else
				return dat(lson(p)).cnt+queryCnt(rson(p),mid+1,r,pos);
		}
		inline int queryPod(reg int p,reg int l,reg int r,reg int pos){
			if(!p)
				return 1;
			if(l==r)
				return dat(p).pod;
			if(pos<=mid)
				return queryPod(lson(p),l,mid,pos);
			else
				return 1ll*dat(lson(p)).pod*queryPod(rson(p),mid+1,r,pos)%mod;
		}
		#undef lson
		#undef rson
		#undef dat
		#undef mid
	}
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n,rt[MAXN];
	inline void Init(reg int s){
		n=s;
		SegmentTree::Init();
		memset(rt,0,sizeof(rt));
		return;
	}
	inline void update(reg int id,reg int pos,reg int val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			SegmentTree::update(rt[i],1,MAXA,pos,val);
		return;
	}
	inline int queryCnt(reg int id,reg int pos){
		reg int res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res=res+SegmentTree::queryCnt(rt[i],1,MAXA,pos);
		return res;
	}
	inline int queryPod(reg int id,reg int pos){
		reg int res=1;
		for(reg int i=id;i;i^=lowbit(i))
			res=1ll*res*SegmentTree::queryPod(rt[i],1,MAXA,pos)%mod;
		return res;
	}
	inline int queryCnt(reg int l,reg int r,reg int pos){
		return queryCnt(r,pos)-queryCnt(l-1,pos);
	}
	inline int queryPod(reg int l,reg int r,reg int pos){
		return 1ll*queryPod(r,pos)*inv(queryPod(l-1,pos))%mod;
	}
	inline int queryPod(reg int l,reg int r,reg int L,reg int R){
		return 1ll*queryPod(l,r,R)*inv(queryPod(l,r,L-1))%mod;
	}
}

int n,q;
int a[MAXN],b[MAXN],c[MAXN];
int ans=1;

struct Node{
	int l,r,val;
	inline Node(reg int l=0,reg int r=0,reg int val=0):l(l),r(r),val(val){
		return;
	}
};

int tot;
Node S[MAXN];

inline void update(reg int x,reg int y,const Node& a){
	if(y==a.val)
		return;
	reg int len=a.r-a.l+1;
	reg int cnt=BIT::queryCnt(a.l,a.r,a.val);
	ans=1ll*ans*fpow(fpow(a.val,len-cnt),mod-2);
	reg int pod=BIT::queryPod(a.l,a.r,a.val+1,y);
	ans=1ll*ans*pod%mod;
	reg int cntN=BIT::queryCnt(a.l,a.r,y);
	ans=1ll*ans*fpow(y,len-cntN)%mod;
	return;
}

inline void updateA(reg int x,reg int y){
	reg int l=1,r=tot+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(S[mid].val>y)
			r=mid;
		else
			l=mid+1;
	}
	reg int R=l-1;
	l=1,r=tot;
	while(l<r){
		mid=(l+r)>>1;
		if(S[mid].l<x)
			l=mid+1;
		else
			r=mid;
	}
	reg int L=l;
	if(S[L].l==x){
		for(reg int i=L;i<=R;++i)
			update(x,y,S[i]);
		S[L].r=S[R].r;
		S[L].val=y;
		for(reg int i=R+1;i<=tot;++i)
			S[i-R+L]=S[i];
		tot-=R-L;
		S[tot+1]=Node(inf,inf,inf);
	}
	else{
		update(x,y,Node(x,S[L].r,S[L].val));
		for(reg int i=L+1;i<=R;++i)
			update(x,y,S[i]);
		S[L].r=x-1;
		S[L+1].l=x;
		S[L+1].r=S[R].r;
		S[L+1].val=y;
		for(reg int i=R+1;i<=tot;++i)
			S[i-R+1+L]=S[i];
		tot-=R-L-1;
		S[tot+1]=Node(inf,inf,inf);
	}
	return;
}

inline void updateB(reg int x,reg int y){
	if(b[x]==y)
		return;
	reg int l=1,r=tot+1,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(S[mid+1].l<=x)
			l=mid+1;
		else
			r=mid;
	}
	reg int id=l,val=S[id].val;
	if(val<=b[x])
		ans=1ll*ans*inv(val)%mod;
	else
		ans=1ll*ans*inv(b[x])%mod;
	BIT::update(x,b[x],-1);
	b[x]=y;
	if(val<=b[x])
		ans=1ll*ans*val%mod;
	else
		ans=1ll*ans*b[x]%mod;
	BIT::update(x,b[x],1);
	return;
}

int main(void){
	//printf("%.1lf MiB\n",sizeof(BIT::SegmentTree::unit)/1048576.0);
	n=read(),q=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		if(!tot||S[tot].val<a[i])
			S[++tot]=Node(i,i,a[i]);
		else
			++S[tot].r;
		c[i]=max(c[i-1],a[i]);
	}
	S[tot+1]=Node(inf,inf,inf);
	BIT::Init(n);
	for(reg int i=1;i<=n;++i){
		b[i]=read();
		ans=1ll*ans*min(b[i],c[i])%mod;
		BIT::update(i,b[i],1);
	}
	for(reg int i=1;i<=q;++i){
		static int opt,x,y;
		opt=read();
		switch(opt){
			case 0:{
				x=read(),y=read();
				updateA(x,y);
				break;
			}
			case 1:{
				x=read(),y=read();
				updateB(x,y);
				break;
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}