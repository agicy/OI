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

inline ll max(reg ll a,reg ll b){
	return a<b?b:a;
}

const int MAXN=1e5+5;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

ll Max[MAXN],cMax[MAXN],ccMax[MAXN];
ll f[MAXN],g[MAXN],h[MAXN];
ll ans;

inline void dfs1(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			f[u]=max(f[u],f[v]);
			ccMax[u]=max(ccMax[u],Max[v]+a[v]);
			if(ccMax[u]>cMax[u])
				swap(ccMax[u],cMax[u]);
			if(cMax[u]>Max[u])
				swap(Max[u],cMax[u]);
		}
	}
	f[u]=max(f[u],Max[u]+cMax[u]+a[u]);
	return;
}

inline void dfs2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(Max[v]+a[v]==Max[u])
				g[v]=cMax[u]+ccMax[u]+a[u];
			else if(Max[v]+a[v]==cMax[u])
				g[v]=Max[u]+ccMax[u]+a[u];
			else
				g[v]=Max[u]+cMax[u]+a[u];
			reg ll val;
			if(Max[v]+a[v]==Max[u])
				val=cMax[u]+a[u];
			else
				val=Max[u]+a[u];
			ccMax[v]=max(ccMax[v],val);
			if(ccMax[v]>cMax[v])
				swap(ccMax[v],cMax[v]);
			if(cMax[v]>Max[v])
				swap(Max[v],cMax[v]);
			dfs2(v,u);
		}
	}
	return;
}

inline void getAns(reg int u,reg int father){
	ans=max(ans,f[u]+h[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			cMax[u]=max(cMax[u],f[v]);
			if(cMax[u]>Max[u])
				swap(Max[u],cMax[u]);
		}
	}
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			reg ll val;
			if(f[v]!=Max[u])
				val=Max[u];
			else
				val=cMax[u];
			h[v]=max(val,max(h[u],g[v]));
			getAns(v,u);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int x,y;
		x=read(),y=read();
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	memset(Max,0,sizeof(Max));
	memset(cMax,0,sizeof(cMax));
	dfs1(1,0);
	dfs2(1,0);
	memset(Max,0,sizeof(Max));
	memset(cMax,0,sizeof(cMax));
	getAns(1,0);
	printf("%lld\n",ans);
	return 0;
}