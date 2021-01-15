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
const int MAXM=1e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

namespace Tree{
	int son[MAXN];
	double f[MAXN];
	inline void dfs1(reg int u,reg int father){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				++son[u];
				dfs1(v,u);
				f[u]+=f[v]+w[i];
			}
		}
		if(son[u])
			f[u]/=son[u];
		return;
	}
	double g[MAXN];
	inline void dfs2(reg int u,reg int father){
		reg double tmp=g[u]+f[u]*son[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father){
				if(u==1)
					if(son[u]==1)
						g[v]=w[i];
					else
						g[v]=w[i]+(tmp-f[v]-w[i])/(son[u]-1);
				else
					g[v]=w[i]+(tmp-f[v]-w[i])/son[u];
				dfs2(v,u);
			}
		}
		return;
	}
	inline void getG(void){
		dfs1(1,0),dfs2(1,0);
		reg double ans=f[1];
		for(reg int i=2;i<=n;++i)
			ans+=(f[i]*son[i]+g[i])/(son[i]+1);
		ans/=n;
		printf("%.5lf\n",ans);
		return;
	}
}

namespace gTree{
	bool tag[MAXN];
	int pre[MAXN];
	int tim,dfn[MAXN];
	inline bool dfs(reg int u){
		dfn[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=pre[u]){
				if(!dfn[v]){
					pre[v]=u;
					if(dfs(v))
						return true;
				}
				else if(dfn[v]<dfn[u]){
					for(reg int j=u;j!=v;j=pre[j])
						tag[j]=true;
					tag[v]=true;
					return true;
				}
			}
		}
		return false;
	}
	int son[MAXN];
	double f[MAXN];
	inline void dpF(reg int u,reg int father){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&!tag[v]){
				++son[u];
				dpF(v,u);
				f[u]+=f[v]+w[i];
			}
		}
		if(son[u])
			f[u]/=son[u];
		return;
	}
	inline double dfs(reg int u,reg int father,reg int rt){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&tag[v]){
				if(v==rt)
					return f[u];
				else
					return (dfs(v,u,rt)+w[i]+f[u]*son[u])/(son[u]+1);
			}
		}
		return 0;
	}
	double g[MAXN];
	inline void getG(reg int u){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(tag[v])
				g[u]+=dfs(v,u,u)+w[i];
		}
		g[u]*=0.5;
		return;
	}
	inline void dpG(reg int u,reg int father){
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=father&&!tag[v]){
				g[v]=w[i]+(g[u]*(tag[u]+1)+f[u]*son[u]-f[v]-w[i])/(son[u]+tag[u]);
				dpG(v,u);
			}
		}
		return;
	}
	inline void getG(void){
		dfs(1);
		for(reg int i=1;i<=n;++i)
			if(tag[i])
				dpF(i,0);
		for(reg int i=1;i<=n;++i)
			if(tag[i])
				getG(i);
		for(reg int i=1;i<=n;++i)
			if(tag[i])
				dpG(i,0);
		reg double ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=(f[i]*son[i]+g[i]*(tag[i]+1))/(son[i]+1+tag[i]);
		ans/=n;
		printf("%.5lf\n",ans);
		return;
	}
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int x,y,w;
		x=read(),y=read(),w=read();
		Add_Edge(x,y,w),Add_Edge(y,x,w);
	}
	if(n==m+1)
		Tree::getG();
	else
		gTree::getG();
	return 0;
}