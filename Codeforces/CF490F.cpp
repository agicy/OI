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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=6e3+5;

int n;
int w[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
int ans;

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

namespace SegmentTree{
	const int MAXSIZE=MAXN*40;
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int lson,rson;
		int lis,lds;
		#define lson(x) unit[(x)].lson
		#define rson(x) unit[(x)].rson
		#define lis(x) unit[(x)].lis
		#define lds(x) unit[(x)].lds
	};
	int tot;
	Node unit[MAXSIZE];
	inline void updateLis(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		lis(p)=max(lis(p),val);
		if(l!=r){
			if(pos<=mid)
				updateLis(lson(p),l,mid,pos,val);
			else
				updateLis(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	inline void updateLds(reg int &p,reg int l,reg int r,reg int pos,reg int val){
		if(!p)
			p=++tot;
		lds(p)=max(lds(p),val);
		if(l!=r){
			if(pos<=mid)
				updateLds(lson(p),l,mid,pos,val);
			else
				updateLds(rson(p),mid+1,r,pos,val);
		}
		return;
	}
	inline int queryLis(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return lis(p);
		if(L<=mid&&mid<R)
			return max(queryLis(lson(p),l,mid,L,R),queryLis(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return queryLis(lson(p),l,mid,L,R);
		else
			return queryLis(rson(p),mid+1,r,L,R);
	}
	inline int queryLds(reg int p,reg int l,reg int r,reg int L,reg int R){
		if(!p)
			return 0;
		if(L<=l&&r<=R)
			return lds(p);
		if(L<=mid&&mid<R)
			return max(queryLds(lson(p),l,mid,L,R),queryLds(rson(p),mid+1,r,L,R));
		else if(L<=mid)
			return queryLds(lson(p),l,mid,L,R);
		else
			return queryLds(rson(p),mid+1,r,L,R);
	}
	inline int merge(reg int x,reg int y){
		if(!x||!y)
			return x|y;
		lis(x)=max(lis(x),lis(y)),lds(x)=max(lds(x),lds(y));
		ans=max(ans,max(lis(lson(x))+lds(rson(y)),lds(rson(x))+lis(lson(y))));
		lson(x)=merge(lson(x),lson(y)),rson(x)=merge(rson(x),rson(y));
		return x;
	}
	#undef mid
}

vector<int> V;
int rt[MAXN];

inline void dfs(reg int u,reg int father){
	reg int Maxi=0,Maxd=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			reg int tLis=SegmentTree::queryLis(rt[v],1,V.size(),1,w[u]-1),tLds=SegmentTree::queryLds(rt[v],1,V.size(),w[u]+1,V.size());
			rt[u]=SegmentTree::merge(rt[u],rt[v]);
			ans=max(ans,max(tLis+Maxd,tLds+Maxi)+1);
			Maxi=max(Maxi,tLis),Maxd=max(Maxd,tLds);
		}
	}
	SegmentTree::updateLis(rt[u],1,V.size(),w[u],Maxi+1),SegmentTree::updateLds(rt[u],1,V.size(),w[u],Maxd+1);
	return;
}

int main(void){
	n=read();
	V.resize(n);
	for(reg int i=1;i<=n;++i)
		V[i-1]=w[i]=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b),Add_Edge(b,a);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		w[i]=lower_bound(V.begin(),V.end(),w[i])-V.begin()+1;
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}