#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10ll*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=50000+5;
const int MAXM=100000+5;

namespace Basis{
	const int MAXLOG2A=63;
	ll p[MAXLOG2A];
	inline void insert(reg ll x){
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if(((x>>i)&1)){
				if(!p[i]){
					p[i]=x;
					break;
				}
				x^=p[i];
			}
		return;
	}
	inline ll query(reg ll x){
		reg ll res=x;
		for(reg int i=MAXLOG2A-1;i>=0;--i)
			if((res^p[i])>res)
				res^=p[i];
		return res;
	}
}

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
ll w[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
ll dis[MAXN];

inline void DFS(reg int u,reg ll d){
	vis[u]=true;
	dis[u]=d;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v])
			DFS(v,d^w[i]);
		else
			Basis::insert(d^w[i]^dis[v]);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int s,t;
		static ll d;
		s=read(),t=read(),d=read();
		Add_Edge(s,t,d);
		Add_Edge(t,s,d);
	}
	DFS(1,0);
	printf("%lld\n",Basis::query(dis[n]));
	return 0;
}