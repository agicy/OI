#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

inline int pow(reg int x,reg int exp,reg int mod){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%mod;
		x=1ll*x*x%mod;
		exp>>=1;
	}
	return res;
}

const int MAXN=3e5+5;
const int mod=998244353;
const int inv1e4=pow(1e4,mod-2,mod);

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=mod?sum-mod:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%mod;
}

int n,m;
int p[MAXN];
vector<int> V;
int root[MAXN];

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int sum;
		int tagM;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define sum(x) unit[(x)].sum
		#define tagM(x) unit[(x)].tagM
	};
	const int MAXSIZE=40*MAXN;
	int tot;
	Node unit[MAXSIZE];
	inline int New(void){
		reg int k=++tot;
		lson(k)=rson(k)=sum(k)=0;
		tagM(k)=1;
		return k;
	}
	inline void pushup(reg int k){
		sum(k)=add(sum(lson(k)),sum(rson(k)));
		return;
	}
	inline void Mul(reg int k,reg int val){
		sum(k)=mul(sum(k),val);
		tagM(k)=mul(tagM(k),val);
		return;
	}
	inline void pushdown(reg int k){
		if(tagM(k)!=1){
			if(lson(k))
				Mul(lson(k),tagM(k));
			if(rson(k))
				Mul(rson(k),tagM(k));
			tagM(k)=1;
		}
		return;
	}
	inline void update(reg int &k,reg int l,reg int r,reg int pos,reg int val){
		if(!k)
			k=New();
		if(l==r){
			sum(k)=add(sum(k),val);
			return;
		}
		pushdown(k);
		if(pos<=mid)
			update(lson(k),l,mid,pos,val);
		else
			update(rson(k),mid+1,r,pos,val);
		pushup(k);
		return;
	}
	inline int merge(reg int x,reg int y,reg int l,reg int r,reg int xmul,reg int ymul,const int& val){
		if(!x&&!y)
			return 0;
		else if(!x){
			Mul(y,ymul);
			return y;
		}
		else if(!y){
			Mul(x,xmul);
			return x;
		}
		else{
			pushdown(x),pushdown(y);
			reg int lsumx=sum(lson(x)),lsumy=sum(lson(y)),rsumx=sum(rson(x)),rsumy=sum(rson(y));
			lson(x)=merge(lson(x),lson(y),l,mid,add(xmul,mul(rsumy,add(1,mod-val))),add(ymul,mul(rsumx,add(1,mod-val))),val);
			rson(x)=merge(rson(x),rson(y),mid+1,r,add(xmul,mul(lsumy,val)),add(ymul,mul(lsumx,val)),val);
			pushup(x);
			return x;
		}
	}
	int T[MAXN];
	inline void query(reg int k,reg int l,reg int r){
		if(l==r){
			T[l]=mul(sum(k),sum(k));
			return;
		}
		pushdown(k);
		query(lson(k),l,mid),query(rson(k),mid+1,r);
		return;
	}
	#undef mid
}

int deg[MAXN];
int son[MAXN][2];

inline void dfs(reg int u){
	switch(deg[u]){
		case 0:{
			SegmentTree::update(root[u],1,m,p[u],1);
			break;
		}
		case 1:{
			dfs(son[u][0]);
			root[u]=root[son[u][0]];
			break;
		}
		case 2:{
			dfs(son[u][0]),dfs(son[u][1]);
			root[u]=SegmentTree::merge(root[son[u][0]],root[son[u][1]],1,m,0,0,p[u]);
			break;
		}
	}
	return;
}

int main(void){
	n=read(),read();
	for(reg int i=2;i<=n;++i){
		static int f;
		f=read();
		son[f][deg[f]++]=i;
	}
	for(reg int i=1;i<=n;++i){
		p[i]=read();
		if(deg[i])
			p[i]=mul(p[i],inv1e4);
		else
			V.push_back(p[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	m=V.size();
	for(reg int i=1;i<=n;++i)
		if(!deg[i])
			p[i]=lower_bound(V.begin(),V.end(),p[i])-V.begin()+1;
	dfs(1);
	SegmentTree::query(root[1],1,m);
	reg int ans=0;
	for(reg int i=1;i<=m;++i)
		ans=add(ans,mul(i,mul(V[i-1],SegmentTree::T[i])));
	printf("%d\n",ans);
	return 0;
}