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

inline void write(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0) putchar('0');
	else while(x) buf[++p]=(x%10)^'0',x/=10;
	while(~p) putchar(buf[p--]);
	return;
}

const int MAXN=5e5+5;
const int MAXC=22;

int n;
int cnt,head[MAXN],to[MAXN],w[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN],dep[MAXN],dis[MAXN];
int son[MAXN],siz[MAXN];
int tim,lef[MAXN],rig[MAXN],rnk[MAXN];

inline void dfs1(reg int u){
	siz[u]=1;
	dep[u]=dep[fa[u]]+1;
	rnk[lef[u]=++tim]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		dis[v]=dis[u]^w[i];
		dfs1(v);
		siz[u]+=siz[v];
		if(siz[son[u]]<siz[v])
			son[u]=v;
	}
	rig[u]=tim;
	return;
}

int T[1<<MAXC];
int ans[MAXN];

inline void dfs2(reg int u,reg bool flag){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=son[u]){
			dfs2(v,false);
			ans[u]=max(ans[u],ans[v]);
		}
	}
	if(son[u]){
		dfs2(son[u],true);
		ans[u]=max(ans[u],ans[son[u]]);
	}
	if(T[dis[u]])
		ans[u]=max(ans[u],T[dis[u]]-dep[u]);
	for(reg int i=0;i<MAXC;++i)
		if(T[dis[u]^(1<<i)])
			ans[u]=max(ans[u],T[dis[u]^(1<<i)]-dep[u]);
	T[dis[u]]=max(T[dis[u]],dep[u]);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=son[u]){
			for(reg int id=lef[v];id<=rig[v];++id){
				reg int p_id=rnk[id];
				if(T[dis[p_id]])
					ans[u]=max(ans[u],dep[p_id]+T[dis[p_id]]-(dep[u]<<1));
				for(reg int k=0;k<MAXC;++k)
					if(T[dis[p_id]^(1<<k)])
						ans[u]=max(ans[u],T[dis[p_id]^(1<<k)]+dep[p_id]-(dep[u]<<1));
			}
			for(reg int id=lef[v];id<=rig[v];++id)
				T[dis[rnk[id]]]=max(T[dis[rnk[id]]],dep[rnk[id]]);
		}
	}
	if(flag==false)
		for(reg int id=lef[u];id<=rig[u];++id)
			T[dis[rnk[id]]]=0;
	return;
}

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i){
		fa[i]=read();
		static char ch;
		do
			ch=getchar();
		while(!isalpha(ch));
		Add_Edge(fa[i],i,1<<(ch-'a'));
	}
	dfs1(1),dfs2(1,true);
	for(reg int i=1;i<=n;++i)
		write(ans[i]),putchar(i==n?'\n':' ');
	flush();
	return 0;
}