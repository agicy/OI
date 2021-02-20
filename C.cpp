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

const int MAXN=2e3+5;
const int mod=998244353;

int n,t;
int u[MAXN],v[MAXN];
int deg[MAXN];

namespace Subtask1{
	const int MAXN=10+5;
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dfs1(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=son[u]&&v!=father)
				dfs2(v,u,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline int getDis(reg int x,reg int y){
		reg int lca=LCA(x,y);
		return dep[x]+dep[y]-(dep[lca]<<1);
	}
	int p[MAXN];
	bool vis[MAXN];
	int Max=-1,Cnt=0;
	inline void check(void){
		reg int sum=0;
		for(reg int i=1;i<=n;++i)
			sum+=getDis(i,p[i]);
		if(Max<sum)
			Max=sum,Cnt=1;
		else if(Max==sum)
			++Cnt;
		return;
	}
	inline void dfs(reg int dep){
		if(dep==n+1){
			check();
			return;
		}
		for(reg int i=1;i<=n;++i)
			if(!vis[i]){
				vis[i]=true;
				p[dep]=i;
				dfs(dep+1);
				vis[i]=false;
			}
		return;
	}
	inline void Solve(void){
		for(reg int i=1;i<n;++i){
			Add_Edge(u[i],v[i]);
			Add_Edge(v[i],u[i]);
		}
		dfs1(1,0);
		dfs2(1,0,1);
		dfs(1);
		printf("%d\n",Max);
		if(t==2)
			printf("%d\n",Cnt);
		return;
	}
}

namespace Subtask2{
	inline int getFac(reg int x){
		reg int res=1;
		for(reg int i=1;i<=x;++i)
			res=1ll*res*i%mod;
		return res;
	}
	inline void Solve(void){
		reg int ans1=0,ans2=0;
		if(n&1){
			reg int x=(n-1)>>1;
			ans1=2ll*x%mod*(x+1)%mod;
			reg int y=(n-1)>>1,tmp=getFac(y);
			ans2=1ll*tmp*tmp%mod*n%mod;
		}
		else{
			reg int x=(n-2)>>1;
			ans1=2ll*x*(x+1)%mod;
			ans1=(ans1+n)%mod;
			reg int y=n>>1,tmp=getFac(y);
			ans2=1ll*tmp*tmp%mod;
		}
		printf("%d\n",ans1);
		if(t==2)
			printf("%d\n",ans2);
		return;
	}
}

namespace Subtask3{
	int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v){
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	int fa[MAXN],dep[MAXN];
	int siz[MAXN],son[MAXN];
	inline void dfs1(reg int u,reg int father){
		siz[u]=1;
		fa[u]=father;
		dep[u]=dep[father]+1;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				dfs1(v,u);
				siz[u]+=siz[v];
				if(siz[son[u]]<siz[v])
					son[u]=v;
			}
		}
		return;
	}
	int top[MAXN];
	inline void dfs2(reg int u,reg int father,reg int topf){
		top[u]=topf;
		if(!son[u])
			return;
		dfs2(son[u],u,topf);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=son[u]&&v!=father)
				dfs2(v,u,v);
		}
		return;
	}
	inline int LCA(reg int x,reg int y){
		while(top[x]!=top[y])
			if(dep[top[x]]>dep[top[y]])
				x=fa[top[x]];
			else
				y=fa[top[y]];
		return dep[x]<dep[y]?x:y;
	}
	inline int getDis(reg int x,reg int y){
		reg int lca=LCA(x,y);
		return dep[x]+dep[y]-(dep[lca]<<1);
	}
	int p[MAXN];
	inline ll getVal(void){
		reg ll res=0;
		for(reg int i=1;i<=n;++i)
			res+=getDis(i,p[i]);
		return -res;
	}
	inline void Solve(void){
		for(reg int i=1;i<n;++i){
			Add_Edge(u[i],v[i]);
			Add_Edge(v[i],u[i]);
		}
		dfs1(1,0);
		dfs2(1,0,1);
		for(reg int i=1;i<=n;++i)
			p[i]=i;
        random_shuffle(p+1,p+n+1);

		reg ll ans=getVal();
		const double delta=0.9982;
		const double eps=1e-6;
		srand(time(0));
		clock_t st=clock();
		while(true){
			if((clock()-st)>0.75*CLOCKS_PER_SEC)
				break;
			for(reg double T=1e4;T>eps;T*=delta){
				reg int x=rand()%n+1,y=rand()%n+1;
				swap(p[x],p[y]);
				reg ll tmp=getVal(),Del=tmp-ans;
				if(Del<0)
					ans=tmp;
				else if(exp(-Del/T)*RAND_MAX<=rand())
					swap(p[x],p[y]);
			}
			if((clock()-st)>0.75*CLOCKS_PER_SEC)
				break;
		}
		printf("%lld\n",-ans);
		return;
	}
}

int main(void){
	n=read(),t=read();
	reg bool subtask2flag=true;
	for(reg int i=1;i<n;++i){
		u[i]=read(),v[i]=read();
		++deg[u[i]],++deg[v[i]];
	}
	for(reg int i=1;i<=n;++i)
		if(deg[i]>2)
			subtask2flag=false;
	if(n<=10)
		Subtask1::Solve();
	else if(subtask2flag)
		Subtask2::Solve();
	else if(t==1)
		Subtask3::Solve();
	return 0;
}