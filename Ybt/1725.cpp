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
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1e3+5;
const int MAXM=2e3+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool flag;
bool vis[MAXN];
int f[MAXN];

inline void spfa(reg int u){
	if(flag)
		return;
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(f[v]>f[u]+w[i]){
			if(vis[v]){
				flag=true;
				return;
			}
			f[v]=f[u]+w[i];
			spfa(v);
		}
	}
	vis[u]=false;
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		memset(f,0,sizeof(f));
		memset(vis,false,sizeof(vis));
		n=read(),m=read();
		for(reg int i=1;i<=m;++i){
			static int x,y,w;
			x=read(),y=read(),w=read();
			Add_Edge(x-1,y,w);
			Add_Edge(y,x-1,-w);
		}
		flag=false;
		for(reg int i=0;i<=n;++i)
			if(!f[i])
				spfa(i);
		puts(flag?"false":"true");
	}
	return 0;
}