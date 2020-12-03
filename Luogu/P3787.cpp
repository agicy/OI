#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const double eps=1e-5;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];
double w[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

double val[MAXN];
int rt[MAXN];

inline void dfs1(reg int u,reg int father,reg int root,reg double Val){
	rt[u]=root;
	val[u]=Val;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(fabs(w[i])<eps)
				dfs1(v,u,v,1.0);
			else
				dfs1(v,u,root,Val*w[i]);
		}
	}
	return;
}

int siz[MAXN];
int tim,dfn[MAXN];

inline void dfs2(reg int u,reg int father){
	dfn[u]=++tim;
	siz[u]=1;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&fabs(w[i])>eps){
			dfs2(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

namespace BIT{
	inline int lowbit(reg int x){
		return x&(-x);
	}
	int n;
	double unit[MAXN];
	inline void Init(reg int s){
		n=s;
		return;
	}
	inline void update(reg int id,reg double val){
		for(reg int i=id;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline double query(reg int id){
		reg double res=0;
		for(reg int i=id;i;i^=lowbit(i))
			res+=unit[i];
		return res;
	}
}

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<n;++i){
		static int u,v;
		static double w;
		scanf("%d%d%lf",&u,&v,&w);
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	dfs1(1,0,1,1.0);
	for(reg int i=1;i<=n;++i)
		if(i==rt[i])
			dfs2(i,0);
	BIT::Init(n);
	scanf("%d",&m);
	while(m--){
		static int opt,i;
		static double x;
		scanf("%d%d",&opt,&i);
		switch(opt){
			case 1:{
				scanf("%lf",&x);
				x/=val[i];
				BIT::update(dfn[i],x),BIT::update(dfn[i]+siz[i],-x);
				break;
			}
			case 9:{
				reg double w=BIT::query(dfn[i]);
				printf("%.8lf\n",w*val[i]);
				break;
			}
		}
	}
	return 0;
}