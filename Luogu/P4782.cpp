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

const int MAXN=1000000+5;
const int MAXM=1000000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m;
int cnt,head[MAXN<<1],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline int GetID(reg int x,reg int v){
	return v?x:x+n;
}

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int xi,a,xj,b;
		xi=read(),a=read(),xj=read(),b=read();
		Add_Edge(GetID(xi,!a),GetID(xj,b));
		Add_Edge(GetID(xj,!b),GetID(xi,a));
	}
	return;
}

int tim,dfn[MAXN<<1],low[MAXN<<1];
bool vis[MAXN<<1];
int top,S[MAXN<<1];
int Tarjan_cnt,color[MAXN<<1];

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

inline void Work(void){
	for(reg int i=1;i<=2*n;++i)
		if(!dfn[i])
			Tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(color[GetID(i,0)]==color[GetID(i,1)]){
			puts("IMPOSSIBLE");
			return;
		}
	puts("POSSIBLE");
	for(reg int i=1;i<=n;++i)
		printf("%d%c",color[GetID(i,0)]<color[GetID(i,1)]?0:1,i==n?'\n':' ');
	return;
}
