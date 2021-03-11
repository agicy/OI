#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=2e5+5;
const int MAXM=2e5+5;
const int MAXLOG2N=18+1;
const ll inf=0x3f3f3f3f3f3f3f3f;

struct querys{
	int opt,l,r;
	ll ans;
};

int n,m,rt;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
int a[MAXN];
querys q[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int fa[MAXN][MAXLOG2N],dep[MAXN];
ll dis[MAXN];
int Maxdep[MAXN],son[MAXN];
int Q[MAXN];

inline void bfs1(reg int s){
	reg int _head=0,_tail=0;
	fa[s][0]=s,dep[s]=1,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		Maxdep[u]=dep[u];
		for(reg int i=1;i<MAXLOG2N;++i)
			fa[u][i]=fa[fa[u][i-1]][i-1];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=fa[u][0]){
				fa[v][0]=u;
				dep[v]=dep[u]+1;
				dis[v]=dis[u]+w[i];
				Q[_tail++]=v;
			}
		}
	}
	for(reg int i=n-1;i>=0;--i){
		reg int u=Q[i];
		if(Maxdep[u]>Maxdep[fa[u][0]]){
			son[fa[u][0]]=u;
			Maxdep[fa[u][0]]=Maxdep[u];
		}
	}
	return;
}

vector<int> up[MAXN],dn[MAXN];
int top[MAXN];

inline void bfs2(reg int s){
	reg int _head=0,_tail=0;
	top[s]=s,Q[_tail++]=s;
	while(_head<_tail){
		reg int u=Q[_head++];
		if(u==top[u]){
			up[u].resize(Maxdep[u]-dep[u]+1),dn[u].resize(Maxdep[u]-dep[u]+1);
			reg int v;
			v=u;
			for(reg int i=0;i<=Maxdep[u]-dep[u];++i)
				up[u][i]=v,v=fa[v][0];
			v=u;
			for(reg int i=0;i<=Maxdep[u]-dep[u];++i)
				dn[u][i]=v,v=son[v];
		}
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(v!=fa[u][0]){
				top[v]=(v==son[u])?top[u]:v;
				Q[_tail++]=v;
			}
		}
	}
	return;
}

int v[MAXN];

inline int getFa(reg int u,reg int k){
	if(!k)
		return u;
	else{
		u=fa[u][v[k]-1];
		k-=(1<<(v[k]-1))+(dep[u]-dep[top[u]]);
		u=top[u];
		if(k>=0)
			if(up[u].size()-1>=k)
				return up[u][k];
			else
				return rt;
		else
			if(dn[u].size()-1>=-k)
				return dn[u][-k];
			else
				return rt;
	}
}

int lef[MAXN],rig[MAXN];
int delta[MAXN];
bool vis[MAXN];

inline void solve(reg int id){
	for(reg int i=1;i<=n;++i)
		vis[i]=false;
	reg int Delta=0;
	reg ll Ans=inf;
	reg int _head=0,_tail=0;
	for(reg int i=lef[id];i<=rig[id];++i){
		delta[i]=0;
		Ans=min(Ans,dis[a[i]]);
		if(!vis[a[i]]){
			vis[a[i]]=true;
			Q[_tail++]=a[i];
		}
	}
	for(reg int i=1;i<=m;++i)
		if(lef[id]<=q[i].r&&q[i].l<=rig[id]){
			reg int l=max(lef[id],q[i].l),r=min(rig[id],q[i].r);
			if(q[i].opt==2)
				if(l==lef[id]&&r==rig[id])
					q[i].ans=min(q[i].ans,Ans);
				else{
					reg ll res=inf;
					for(reg int j=l;j<=r;++j)
						res=min(res,dis[getFa(a[j],delta[j]+Delta)]);
					q[i].ans=min(q[i].ans,res);
				}
			else
				if(l==lef[id]&&r==rig[id]){
					++Delta;
					reg int top=0;
					static int S[MAXN];
					while(_head<_tail){
						reg int u=Q[_head++];
						u=fa[u][0];
						Ans=min(Ans,dis[u]);
						if(!vis[u]){
							vis[u]=true;
							S[++top]=u;
						}
					}
					for(reg int j=1;j<=top;++j)
						Q[_tail++]=S[j];
				}
				else
					for(reg int j=l;j<=r;++j){
						++delta[j];
						reg int u=getFa(a[j],delta[j]+Delta);
						Ans=min(Ans,dis[u]);
						if(!vis[u]){
							vis[u]=true;
							Q[_tail++]=u;
						}
					}
		}
	return;
}

int main(void){
	n=read(),m=read(),rt=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	reg int B=sqrt(n),tot=(n+B-1)/B;
	for(reg int i=1;i<=tot;++i)
		lef[i]=(i-1)*B+1,rig[i]=min(i*B,n);
	for(reg int i=1;i<=n;++i)
		v[i]=v[i>>1]+1;
	bfs1(rt),bfs2(rt);
	for(reg int i=1;i<=m;++i){
		q[i].opt=read(),q[i].l=read(),q[i].r=read();
		q[i].ans=inf;
	}
	for(reg int i=1;i<=tot;++i)
		solve(i);
	for(reg int i=1;i<=m;++i)
		if(q[i].opt==2)
			writeln(q[i].ans);
	flush();
	return 0;
}