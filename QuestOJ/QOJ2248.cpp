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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline void Err(reg bool f){
	if(!f)
		exit(0);
	return;
}

const int MAXN=2e5+10;
const int MAXM=2e5+10;

int p;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=mul(res,x);
		x=mul(x,x);
		exp>>=1;
	}
	return res;
}

namespace UnionFind{
	int fa[MAXN];
	inline void Init(reg int n){
		for(reg int i=1;i<=n;++i)
			fa[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==fa[x])
			return x;
		else
			return fa[x]=find(fa[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			fa[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
}

int n,m;
int deg[MAXN];
int fac[MAXN],invfac[MAXN];
int cnt,head[MAXN],to[MAXM],Next[MAXM];
int siz[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int dfs(reg int u){
	siz[u]=1;
	reg int res=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		reg int t=dfs(v);
		siz[u]+=siz[v];
		res=mul(res,mul(t,invfac[siz[v]]));
	}
	Err(1<=siz[u]&&siz[u]<=n+1);
	return mul(res,fac[siz[u]-1]);
}

int main(void){
	freopen("photo.in","r",stdin);
	freopen("photo.out","w",stdout);

	reg int t=read();
	while(t--){
		cnt=0,memset(head,0,sizeof(head));
		memset(deg,0,sizeof(deg));
		n=read(),m=read(),p=read();
		fac[0]=1;
		for(reg int i=1;i<=n+1;++i)
			fac[i]=mul(fac[i-1],i);
		invfac[n+1]=fpow(fac[n+1],p-2);
		for(reg int i=n;i>=0;--i)
			invfac[i]=mul(invfac[i+1],i+1);

		reg bool flag=false;
		UnionFind::Init(n+1);
		for(reg int i=1;i<=m;++i){
			static int x,y;
			x=read(),y=read();
			Err(1<=x&&x<=n);
			Err(1<=y&&y<=n);
			if(UnionFind::search(x,y))
				flag=true;
			if(!flag){
				++deg[x];
				Add_Edge(y,x);
				UnionFind::merge(x,y);
			}
		}
		if(!flag){
			reg int rt=n+1;
			for(reg int i=1;i<=n;++i)
				if(!deg[i])
					Add_Edge(rt,i);
			printf("%d\n",dfs(rt));
		}
		else
			puts("0");
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}