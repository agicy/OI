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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=1e5+5;
const int MAXM=5e5+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
bool cut[MAXN];
int tim,dfn[MAXN],low[MAXN];
int top,S[MAXN];
int siz[MAXN];
ll ans[MAXN];
int root;

inline void tarjan(reg int u){
	dfn[u]=low[u]=++tim;
	siz[u]=1;
	reg int flag=false,sum=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			siz[u]+=siz[v];
			cMin(low[u],low[v]);
			if(low[v]>=dfn[u]){
				++flag;
				ans[u]+=1ll*siz[v]*(n-siz[v]);
				sum+=siz[v];
				if(u!=root||flag>1)
					cut[u]=true;
			}
		}
		else
			cMin(low[u],dfn[v]);
	}
	if(cut[u])
		ans[u]+=1ll*(n-sum-1)*(sum+1)+(n-1);
	else
		ans[u]=2ll*(n-1);
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	root=1;
	tarjan(root);
	for(reg int i=1;i<=n;++i)
		printf("%lld\n",ans[i]);
	return 0;
}