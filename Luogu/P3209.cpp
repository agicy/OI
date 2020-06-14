#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

const int MAXN=200+5;
const int MAXM=10000+5;

const int MAXV=MAXM*3;
const int MAXE=2000000+5;

int n,m;
int u[MAXV],v[MAXV];
int Cir[MAXN],rnk[MAXN];
bool G[MAXN][MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		if(u[i]>v[i])
			swap(u[i],v[i]);
	}
	for(reg int i=1;i<=n;++i){
		rnk[Cir[i]=read()]=i;
		if(i>1){
			reg int x=Cir[i-1],y=Cir[i];
			if(x<y)
				G[x][y]=1;
			else
				G[y][x]=1;
		}
	}
	reg int x=Cir[n],y=Cir[1];
	((x<y)?G[x][y]:G[y][x])=1;
	return;
}

int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXV],low[MAXV];
bool vis[MAXV];
int top,S[MAXV];
int Tarjan_cnt,color[MAXV];

inline void Tarjan(reg int ID){
	dfn[ID]=low[ID]=++tim;
	vis[ID]=true;
	S[++top]=ID;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	if(dfn[ID]==low[ID]){
		reg int To;
		++Tarjan_cnt;
		do{
			To=S[top--];
			vis[To]=false;
			color[To]=Tarjan_cnt;
		}while(To!=ID);
	}
	return;
}

inline bool check(void){
	for(reg int i=1;i<=(m<<1);++i)
		if(!dfn[i])
			Tarjan(i);
	for(reg int i=1;i<=m;++i)
		if(color[i]==color[i+m])
			return false;
	return true;
}

int X[MAXV],Y[MAXV];

inline void Work(void){
	if(m>3*n-6){
		puts("NO");
		return;
	}
	reg int tot=0;
	for(reg int i=1;i<=m;++i){
		if(G[u[i]][v[i]])
			continue;
		X[++tot]=u[i];
		Y[tot]=v[i];
	}
	m=tot;
	for(reg int i=1;i<=m;++i)
		for(reg int j=i+1;j<=m;++j){
			int u=rnk[X[i]],v=rnk[Y[i]];
			int x=rnk[X[j]],y=rnk[Y[j]];
			if(u>v)
				swap(u,v);
			if(x>y)
				swap(x,y);
			if((u<x&&v>x&&v<y)||(u>x&&u<y&&v>y)){
				Add_Edge(i,j+m);
				Add_Edge(i+m,j);
				Add_Edge(j,i+m);
				Add_Edge(j+m,i);
		}
	}
	puts(check()?"YES":"NO");
	return;
}

inline void Init(void){
	cnt=tim=Tarjan_cnt=top=0;
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	memset(color,0,sizeof(color));
	memset(G,false,sizeof(G));
	return;
}