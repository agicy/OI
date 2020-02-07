#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
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

const int MAXN=100+5;
const int MAXM=MAXN*(MAXN-1);

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,a,b;
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Read(void){
	n=read();
	while(true){
		static int u,v;
		u=read(),v=read();
		if(u==0&&v==0)
			break;
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	a=read(),b=read();
	return;
}

bool vis[MAXN];
int DFN,dfn[MAXN],low[MAXN];
vector<int> V;

inline void Tarjan(int ID){
	vis[ID]=true;
	dfn[ID]=low[ID]=++DFN;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dfn[to[i]]){
			Tarjan(to[i]);
			low[ID]=min(low[ID],low[to[i]]);
			if(low[to[i]]>=dfn[ID]&&ID!=a&&dfn[b]>=dfn[to[i]])
				V.push_back(ID);
		}
		else if(vis[to[i]])
			low[ID]=min(low[ID],dfn[to[i]]);
	return;
}

inline void Work(void){
	Tarjan(a);
	if(V.size()){
		int Min=n+1;
		for(reg int i=0;i<(int)V.size();++i)
			Min=min(Min,V[i]);
		printf("%d\n",Min);
	}
	else
		puts("No solution");
	return;
}
