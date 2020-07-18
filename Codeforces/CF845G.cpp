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

const int MAXN=100000+5;
const int MAXM=100000+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int dis[MAXN];

namespace Basis{
	const int MAXLOG2W=27+1;
	int unit[MAXLOG2W];
	inline void insert(reg int x){
		for(reg int i=MAXLOG2W-1;i>=0;--i) 
			if((x>>i)&1){
				if(!unit[i]){
					unit[i]=x;
					break;
				}
				x^=unit[i];
			}
		return;
	}
	inline int query(int res){
		for(reg int i=MAXLOG2W-1;i>=0;--i)
			res=min(res,res^unit[i]);
		return res;
	}
}

inline void DFS(reg int u,reg int d){
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
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	DFS(1,0);
	printf("%d\n",Basis::query(dis[n]));
	return 0;
}
