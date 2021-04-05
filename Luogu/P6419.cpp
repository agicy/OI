#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg ll x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=5e5+5;

int n,k;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int Max){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=Max;
	head[u]=cnt;
	return;
}

int siz[MAXN];
int id[MAXN];
ll Max[MAXN],cMax[MAXN];
ll f[MAXN];

inline void dfs1(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs1(v,u);
			if(siz[v]){
				f[u]+=f[v]+2*w[i];
				if(Max[v]+w[i]>=Max[u]){
					cMax[u]=Max[u],Max[u]=Max[v]+w[i];
					id[u]=v;
				}
				else if(Max[v]+w[i]>cMax[u])
					cMax[u]=Max[v]+w[i];
			}
			siz[u]+=siz[v];
		}
	}
	return;
}

ll g[MAXN];

inline void dfs2(reg int u,reg int father){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(!siz[v])
				g[v]=g[u]+2*w[i],Max[v]=Max[u]+w[i];
			else if(k-siz[v]){
				g[v]=g[u];
				if(id[u]!=v&&Max[v]<Max[u]+w[i])
					cMax[v]=Max[v],Max[v]=Max[u]+w[i],id[v]=u;
				else if(Max[v]<cMax[u]+w[i])
					cMax[v]=Max[v],Max[v]=cMax[u]+w[i],id[v]=1;
				else if(cMax[v]<Max[u]+w[i]&&id[u]!=v)
					cMax[v]=Max[u]+w[i];
				else if(cMax[v]<cMax[u]+w[i])
					cMax[v]=cMax[u]+w[i];
			}
			else
				g[v]=f[v];
			dfs2(v,u);
		}
	}
	return;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=k;++i)
		++siz[read()];
	dfs1(1,0);
	g[1]=f[1];
	dfs2(1,0);
	for(reg int i=1;i<=n;++i)
		writeln(g[i]-Max[i]);
	flush();
	return 0;
}