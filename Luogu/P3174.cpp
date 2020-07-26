#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=300000+5;
const int MAXM=MAXN;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
int Deg[MAXN];
int f[MAXN];

inline void Read(void);
inline void Work(void);
inline void Add_Edge(reg int,reg int);
inline void DFS(reg int,reg int);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int a,b;
		a=read(),b=read();
		++Deg[a],++Deg[b];
		Add_Edge(a,b);
		Add_Edge(b,a);
	}
	return;
}

inline void Work(void){
	for(reg int i=1;i<=n;++i)
		--Deg[i];
	DFS(1,0);
	int Max=0,pos=0;
	for(reg int i=1;i<=n;++i)
		if(f[i]>Max){
			Max=f[i];
			pos=i;
		}
	memset(f,0,sizeof(f));
	DFS(pos,0);
	for(reg int i=1;i<=n;++i)
		Max=max(Max,f[i]);
	printf("%d\n",Max+2);
	return;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID,reg int father){
	f[ID]=f[father]+Deg[ID];
	for(reg int i=head[ID];i;i=Next[i])
		if(to[i]!=father)
			DFS(to[i],ID);
	return;
}