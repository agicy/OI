#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a<b?b:a;
}

const int MAXN=1e5+5;
const int MAXLOG2N=17+1;

int n,q;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int tim,rnk[MAXN],st[MAXN],ed[MAXN];
int bac_tim,pos[MAXN],bac[MAXN<<1];

inline void dfs(reg int u,reg int father){
	bac[pos[u]=++bac_tim]=u;
	rnk[st[u]=++tim]=u;
	dep[u]=dep[father]+1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			bac[++bac_tim]=u;
		}
	}
	ed[u]=tim;
	return;
}

namespace ST{
	const int MAXS=MAXN*2;
	const int MAXLOG=MAXLOG2N+1;
	int Lg[MAXS];
	int Min[MAXLOG][MAXS];
	int *c;
	inline void Init(reg int n,reg int a[],reg int cmp[]){
		c=cmp;
		Lg[0]=-1;
		for(reg int i=1;i<=n;++i){
			Lg[i]=Lg[i>>1]+1;
			Min[0][i]=a[i];
		}
		for(reg int j=1;j<MAXLOG;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i)
				if(cmp[Min[j-1][i]]<cmp[Min[j-1][i+(1<<(j-1))]])
					Min[j][i]=Min[j-1][i];
				else
					Min[j][i]=Min[j-1][i+(1<<(j-1))];
		return;
	}
	inline int query(reg int l,reg int r){
		reg int k=Lg[r-l+1];
		if(c[Min[k][l]]<c[Min[k][r-(1<<k)+1]])
			return Min[k][l];
		else
			return Min[k][r-(1<<k)+1];
	}
}

inline int lca(int u,int v){
	u=pos[u],v=pos[v];
	if(u>v)
		swap(u,v);
	return ST::query(u,v);
}

inline int getDis(reg int u,reg int v){
	return dep[u]+dep[v]-2*dep[lca(u,v)];
}

namespace SegmentTree{
	#define lson ( (k) << 1 )
	#define rson ( (k) << 1 | 1 )
	#define mid ( ( (l) + (r) ) >> 1 )
	struct Node{
		int p[2],len;
		inline Node(void){return;}
		inline Node(int a,int b,int c){p[0]=a,p[1]=b,len=c;}
	};
	Node unit[MAXN<<2];
	inline Node operator+(const Node &a,const Node& b){
		Node res=b;
		if(!a.p[0])
			return res;
		if(a.len>b.len)
			res=a;
		reg int len;
		len=getDis(a.p[0],b.p[0]);
		if(len>res.len)
			res=Node(a.p[0],b.p[0],len);
		len=getDis(a.p[0],b.p[1]);
		if(len>res.len)
			res=Node(a.p[0],b.p[1],len);
		len=getDis(a.p[1],b.p[0]);
		if(len>res.len)
			res=Node(a.p[1],b.p[0],len);
		len=getDis(a.p[1],b.p[1]);
		if(len>res.len)
			res=Node(a.p[1],b.p[1],len);
		return res;
	}
	inline void pushup(reg int k){
		unit[k]=unit[lson]+unit[rson];
		return;
	}
	inline void build(reg int k,reg int l,reg int r){
		if(l==r){
			unit[k]=Node(rnk[l],rnk[l],0);
			return;
		}
		build(lson,l,mid),build(rson,mid+1,r);
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

using namespace SegmentTree;

int main(void){
	n=read(),q=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	dfs(1,0);
	ST::Init(bac_tim,bac,dep);
	build(1,1,n);
	while(q--){
		static int u,v;
		static Node ans;
		u=read(),v=read();
		if(st[u]>st[v])
			swap(u,v);
		ans=Node(0,0,0);
		if(st[u]>1)
			ans=ans+query(1,1,n,1,st[u]-1);
		if(ed[u]+1<st[v])
			ans=ans+query(1,1,n,ed[u]+1,st[v]-1);
		if(max(ed[u],ed[v])<n)
			ans=ans+query(1,1,n,max(ed[u],ed[v])+1,n);
		printf("%d\n",ans.len);
	}
	return 0;
}