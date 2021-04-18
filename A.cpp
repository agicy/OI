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

const int MAXN=3e5+5;
const int mod=998244353;
const int inv1e4=796898467;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum,tMul;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
		#define tMul(x) unit[(x)].tMul
	};
	const int MAXSIZE=40*MAXN;
	int tot;
	Node unit[MAXSIZE];
	int top,S[MAXSIZE];
	inline int getId(void){
		if(top)
			return S[top--];
		else
			return ++tot;
	}
	inline int New(void){
		reg int p=getId();
		lson(p)=rson(p)=sum(p)=0,tMul(p)=1;
		return p;
	}
	inline void del(reg int p){
		lson(p)=rson(p)=sum(p)=0;
		tMul(p)=1;
		S[++top]=p;
		return;
	}
	inline void pushup(reg int p){
		sum(p)=add(sum(lson(p)),sum(rson(p)));
		return;
	}
	inline void mul(reg int p,reg int val){
		sum(p)=1ll*sum(p)*val%mod,tMul(p)=1ll*tMul(p)*val%mod;
		return;
	}
	inline void pushdown(reg int p){
		if(tMul(p)!=1){
			if(lson(p))
				mul(lson(p),tMul(p));
			if(rson(p))
				mul(rson(p),tMul(p));
			tMul(p)=1;
		}
		return;
	}
	inline void update(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=New();
		if(l==r){
			sum(p)=add(sum(p),val);
			return;
		}
		pushdown(p);
		if(pos<=mid)
			update(lson(p),l,mid,pos,val);
		else
			update(rson(p),mid+1,r,pos,val);
		pushup(p);
		return;
	}
	inline int merge(reg int x,reg int y,reg int l,reg int r,reg int xmul,reg int ymul,reg int val){
		if(!x&&!y)
			return 0;
		else if(!x){
			mul(y,ymul);
			return y;
		}
		else if(!y){
			mul(x,xmul);
			return x;
		}
		else{
			pushdown(x),pushdown(y);
			reg int p=New();
			reg int lsumx=sum(lson(x)),lsumy=sum(lson(y)),rsumx=sum(rson(x)),rsumy=sum(rson(y));
			lson(p)=merge(lson(x),lson(y),l,mid,add(xmul,1ll*rsumy*add(1,mod-val)%mod),add(ymul,1ll*rsumx*add(1,mod-val)%mod),val);
			rson(p)=merge(rson(x),rson(y),mid+1,r,add(xmul,1ll*lsumy*val%mod),add(ymul,1ll*lsumx*val%mod),val);
			pushup(p);
			del(x),del(y);
			return p;
		}
	}
	int cnt,T[MAXN];
	inline void query(reg int p,reg int l,reg int r){
		if(l==r){
			T[++cnt]=1ll*sum(p)*sum(p)%mod;
			return;
		}
		pushdown(p);
		if(lson(p)) query(lson(p),l,mid);
		if(rson(p)) query(rson(p),mid+1,r);
		return;
	}
	#undef mid
	#undef lson
	#undef rson
	#undef sum
	#undef tMul
}

int n,m;
int deg[MAXN],ch[MAXN][2];
int p[MAXN];
vector<int> V;
int rt[MAXN];

inline void dfs(reg int u){
	switch(deg[u]){
		case 0:{
			SegmentTree::update(rt[u],1,m,p[u],1);
			break;
		}
		case 1:{
			dfs(ch[u][0]);
			rt[u]=rt[ch[u][0]];
			break;
		}
		case 2:{
			dfs(ch[u][0]),dfs(ch[u][1]);
			rt[u]=SegmentTree::merge(rt[ch[u][0]],rt[ch[u][1]],1,m,0,0,p[u]);
			break;
		}
	}
	return;
}

int main(void){
	n=read(),read();
	for(reg int i=2;i<=n;++i){
		static int fa;
		fa=read();
		ch[fa][deg[fa]++]=i;
	}
	for(reg int i=1;i<=n;++i){
		p[i]=read();
		if(deg[i])
			p[i]=1ll*p[i]*inv1e4%mod;
		else
			V.push_back(p[i]);
	}
	sort(V.begin(),V.end()),V.erase(unique(V.begin(),V.end()),V.end());
	m=V.size();
	for(reg int i=1;i<=n;++i)
		if(!deg[i])
			p[i]=lower_bound(V.begin(),V.end(),p[i])-V.begin()+1;
	dfs(1);
	SegmentTree::query(rt[1],1,m);
	reg int ans=0;
	for(reg int i=1;i<=SegmentTree::cnt;++i)
		ans=add(ans,1ll*i*V[i-1]%mod*SegmentTree::T[i]%mod);
	printf("%d\n",ans);
	return 0;
}