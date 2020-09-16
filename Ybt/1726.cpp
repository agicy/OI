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
const int MAXM=1e3+5;
const int MAXK=1e3+5;
const int MAXV=MAXN+MAXM;
const int MAXE=MAXK*2;
const int inf=0x3f3f3f3f;

int n,m,k;
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool flag;
bool vis[MAXV];
int f[MAXV];

inline void spfa(reg int u){
	if(flag)
		return;
	vis[u]=true;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(f[v]>f[u]+w[i]){
			if(vis[v]){
				flag=true;
				vis[u]=false;
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
		n=read(),m=read(),k=read();
		for(reg int i=1;i<=k;++i){
			static int x,y,c;
			x=read(),y=read(),c=read();
			Add_Edge(y+n,x,c);
			Add_Edge(x,y+n,-c);
		}
		flag=false;
		memset(f,0x3f,sizeof(f));
		for(reg int i=1;i<=n+m;++i)
			if(f[i]==inf)
				spfa(i);
		puts(flag?"No":"Yes");
	}
	return 0;
}