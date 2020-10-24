#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	char ch=getchar();
	int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=5e5+5;
const int MAXM=5e5+5;
const int MAXC=600;

struct Edge{
	int u,v,w;
	inline void Read(void){
		u=read(),v=read(),w=read();
		return;
	}
	inline bool operator<(const Edge& a)const{
		return w<a.w;
	}
};

namespace UnionFind{
	int fa[MAXN];
	bitset<MAXC> B[MAXN];
	inline void Init(int n,int c[]){
		for(int i=1;i<=n;++i){
			fa[i]=i;
			B[i][c[i]-1]=true;
		}
		return;
	}
	inline int find(int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(int a,int b){
		int ra=find(a),rb=find(b);
		if(ra!=rb){
			fa[rb]=ra;
			B[ra]|=B[rb];
		}
		return;
	}
	inline bool search(int a,int b){
		return find(a)==find(b);
	}
	inline int siz(int a){
		return B[find(a)].count();
	}
}

int n,m,q,x,opt;
ll M;
int c[MAXN];
Edge E[MAXM];
int val[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int ans[MAXN];
ll sum[MAXN];

inline void Add_Edge(int u,int v,int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline ll solve(const ll& l,const ll& r){
	int p=upper_bound(val+1,val+n+1,l)-(val+1),q=upper_bound(val+1,val+n+1,r)-(val+1);
	if(p==q)
		return 1ll*(r-l+1)*ans[p];
	else
		return (sum[q-1]-sum[p])+1ll*(val[p+1]-l)*ans[p]+1ll*(r-val[q]+1)*ans[q];
}

int main(void){
	n=read(),m=read(),q=read(),x=read(),opt=read();
	if(opt)M=read();
	for(int i=1;i<=n;++i)
		c[i]=read();
	for(int i=1;i<=m;++i)
		E[i].Read();
	sort(E+1,E+m+1);
	UnionFind::Init(n,c);
	ans[1]=1;
	for(int i=1,cnt=1;i<=m&&cnt<n;++i)
		if(!UnionFind::search(E[i].u,E[i].v)){
			UnionFind::merge(E[i].u,E[i].v);
			val[++cnt]=E[i].w;
			ans[cnt]=UnionFind::siz(x);
		}
	for(int i=1;i<n;++i)
		sum[i]=sum[i-1]+1ll*ans[i]*(val[i+1]-val[i]);
	ll lastans=0;
	while(q--){
		static ll l,r;
		l=read(),r=read();
		if(opt)l=(l^lastans)%M+1,r=(r^lastans)%M+1;
		if(l>r)swap(l,r);
		printf("%lld\n",lastans=solve(l,r));
	}
	return 0;
}