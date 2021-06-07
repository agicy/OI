#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e5+5;
const int MAXLOG2T=60;
const int mod=1e9+7;
const int inv2=(mod+1)/2;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

struct Edge{
	int v;
	ll w;
	inline Edge(reg int v=0,reg ll w=0):v(v),w(w){
		return;
	}
};

namespace Basis{
	int cnt;
	ll unit[MAXLOG2T];
	inline void clear(void){
		cnt=0;
		fill(unit,unit+MAXLOG2T,0);
		return;
	}
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2T-1;i>=0;--i)
			if((x>>i)&1){
				if(!unit[i]){
					++cnt,unit[i]=x;
					break;
				}
				else
					x^=unit[i];
			}
		return;
	}
}

int n,m;
vector<Edge> G[MAXN];
int bas[MAXLOG2T];
bool vis[MAXN];
ll dis[MAXN];
int top;
ll S[MAXN];

inline void dfs(reg int u,reg ll val){
	vis[u]=true;
	dis[u]=val;
	S[++top]=dis[u];
	for(Edge e:G[u])
		if(vis[e.v])
			Basis::insert(dis[u]^dis[e.v]^e.w);
		else
			dfs(e.v,dis[u]^e.w);
	return;
}


int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		static ll t;
		u=read(),v=read(),t=readll();
		G[u].push_back(Edge(v,t)),G[v].push_back(Edge(u,t));
	}
	bas[0]=1;
	for(reg int i=1;i<MAXLOG2T;++i)
		bas[i]=add(bas[i-1],bas[i-1]);
	reg int ans=0;
	for(reg int i=1;i<=n;++i)
		if(!vis[i]){
			top=0;
			Basis::clear();
			dfs(i,0);
			for(reg int j=0;j<MAXLOG2T;++j){
				reg bool flag=false;
				for(reg int k=0;k<MAXLOG2T;++k)
					if((Basis::unit[k]>>j)&1){
						flag=true;
						break;
					}
				reg int sum=0;
				if(flag)
					sum=add(sum,1ll*top*(top-1)%mod*inv2%mod*bas[Basis::cnt-1]%mod);
				else {
					reg int cnt=0;
					for(reg int k=1;k<=top;++k)
						if((S[k]>>j)&1)
							++cnt;
					sum=add(sum,1ll*cnt*(top-cnt)%mod*bas[Basis::cnt]%mod);
				}
				ans=add(ans,1ll*sum*bas[j]%mod);
			}
		}
	printf("%d\n",ans);
	return 0;
}