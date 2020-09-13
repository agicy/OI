#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=1e3+5;
const int MAXM=1e6+5;
const int MAXV=2*MAXN;
const int MAXE=4*MAXM;

int n,m;
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int top,S[MAXV];
int tim,dfn[MAXV],low[MAXV];
int tarjan_cnt,col[MAXN];

inline void tarjan(reg int u){
	vis[u]=true;
	S[++top]=u;
	dfn[u]=low[u]=++tim;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			low[u]=min(low[u],low[v]);
		}
		else if(vis[v])
			low[u]=min(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++tarjan_cnt;
		do{
			v=S[top--];
			col[v]=tarjan_cnt;
			vis[v]=false;
		}while(v!=u);
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		static string op;
		u=read()+1,v=read()+1,c=read(),cin>>op;
		if(op=="AND")
			if(c)
				Add_Edge(u,u+n),Add_Edge(v,v+n);
			else
				Add_Edge(u+n,v),Add_Edge(v+n,u);
		else if(op=="OR")
			if(c)
				Add_Edge(u,v+n),Add_Edge(v,u+n);
			else
				Add_Edge(u+n,u),Add_Edge(v+n,v);
		else if(op=="XOR")
			if(c)
				Add_Edge(u,v+n),Add_Edge(u+n,v),Add_Edge(v,u+n),Add_Edge(v+n,u);
			else
				Add_Edge(u,v),Add_Edge(v,u),Add_Edge(u+n,v+n),Add_Edge(v+n,u+n);
		else{
			puts("NO");
			return 0;
		}
	}
	for(reg int i=1;i<=2*n;++i)
		if(!dfn[i])
			tarjan(i);
	for(reg int i=1;i<=n;++i)
		if(col[i]==col[i+n]){
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}