#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e5+5;
const int mod=998244353;

struct modInt{
	int x;
	inline modInt(void){
		return;
	}
	inline modInt(reg int x):x(x){
		//assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*30;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		modInt sum,tMul;
		#define lson(p) unit[p].lson
		#define rson(p) unit[p].rson
		#define sum(p) unit[p].sum
		#define tMul(p) unit[p].tMul
	};
	int tot;
	Node unit[MAXSIZE];
	inline void pushup(reg int p){
		sum(p)=sum(lson(p))+sum(rson(p));
		return;
	}
	inline void mul(reg int p,modInt val){
		if(p)
			tMul(p)*=val,sum(p)*=val;
		return;
	}
	inline void pushdown(reg int p){
		if(tMul(p).x!=1){
			mul(lson(p),tMul(p)),mul(rson(p),tMul(p));
			tMul(p)=1;
		}
		return;
	}
	inline modInt query(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return sum(p);
		pushdown(p);
		if(L<=mid&&mid<R)
			return query(lson(p),l,mid,L,R)+query(rson(p),mid+1,r,L,R);
		else if(L<=mid)
			return query(lson(p),l,mid,L,R);
		else
			return query(rson(p),mid+1,r,L,R);
	}
	inline void update(reg int &p,reg int l,reg int r,const int& pos,const modInt& val){
		if(!p)
			p=++tot,sum(p)=0,tMul(p)=1;
		if(l==r){
			sum(p)=val;
			return;
		}
		if(pos<=mid)
			update(lson(p),l,mid,pos,val);
		else
			update(rson(p),mid+1,r,pos,val);
		pushup(p);
		return;
	}
	inline int merge(reg int x,reg int y,reg int l,reg int r,modInt& val1,modInt& val2){
		if(!x||!y){
			val1+=sum(y),val2+=sum(x);
			mul(x,val1),mul(y,val2);
			return x|y;
		}
		if(l==r){
			val1+=sum(y),val2+=sum(x);
			sum(x)=sum(x)*val1+sum(y)*val2-sum(x)*sum(y);
			return x;
		}
		pushdown(x),pushdown(y);
		lson(x)=merge(lson(x),lson(y),l,mid,val1,val2);
		rson(x)=merge(rson(x),rson(y),mid+1,r,val1,val2);
		pushup(x);
		return x;
	}
}

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];

inline void dfs1(reg int u,reg int father){
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father)
			dfs1(v,u);
	}
	return;
}

int Maxd[MAXN];
int rt[MAXN];

inline void dfs2(reg int u,reg int father){
	SegmentTree::update(rt[u],0,n,Maxd[u],1);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs2(v,u);
			modInt tmp1=SegmentTree::query(rt[v],0,n,0,dep[u]),tmp2=0;
			rt[u]=SegmentTree::merge(rt[u],rt[v],0,n,tmp1,tmp2);
		}
	}
	return;
}

bool ed;

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y),Add_Edge(y,x);
	}
	dfs1(1,0);
	m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Maxd[v]=max(Maxd[v],dep[u]);
	}
	dfs2(1,0);
	printf("%d\n",SegmentTree::query(rt[1],0,n,0,0).x);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}