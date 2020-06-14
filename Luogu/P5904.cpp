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

int n;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int dep[MAXN];
int Maxdep[MAXN],son[MAXN];

inline void DFS1(reg int ID,reg int father){
	dep[ID]=dep[father]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father){
			DFS1(to[i],ID);
			if(Maxdep[son[ID]]<Maxdep[to[i]])
				son[ID]=to[i];
		}
	Maxdep[ID]=Maxdep[son[ID]]+1;
	return;
}

ll ans;
ll *f[MAXN],*g[MAXN],p[MAXN<<2],*o=p;

inline void DFS2(reg int ID,reg int father){
	if(son[ID]){
		f[son[ID]]=f[ID]+1;
		g[son[ID]]=g[ID]-1;
		DFS2(son[ID],ID);
	}
	f[ID][0]=1;
	ans+=g[ID][0];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father&&to[i]!=son[ID]){
			f[to[i]]=o,o+=Maxdep[to[i]]<<1;
			g[to[i]]=o,o+=Maxdep[to[i]]<<1;
			DFS2(to[i],ID);
			for(reg int j=0;j<Maxdep[to[i]];++j){
				if(j)
					ans+=f[ID][j-1]*g[to[i]][j];
				ans+=g[ID][j+1]*f[to[i]][j];
			}
			for(reg int j=0;j<Maxdep[to[i]];++j){
				g[ID][j+1]+=f[ID][j+1]*f[to[i]][j];
				if(j)
					g[ID][j-1]+=g[to[i]][j];
				f[ID][j+1]+=f[to[i]][j];
			}
		}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	DFS1(1,0);
	f[1]=o,o+=Maxdep[1]<<1;
	g[1]=o,o+=Maxdep[1]<<1;
	DFS2(1,0);
	printf("%lld\n",ans);
	return 0;
}