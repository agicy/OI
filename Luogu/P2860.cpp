#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void cMin(reg int &a,reg int b){
	if(a>b) a=b;
	return;
}

const int MAXF=5e3+5;
const int MAXR=1e4+5;

int f,r;
int u[MAXR],v[MAXR];
int deg[MAXF];
int cnt=1,head[MAXF],to[MAXR<<1],Next[MAXR<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXF];
int tim,dfn[MAXF],low[MAXF];
int top,S[MAXF];
int eDcc_cnt,col[MAXF];

inline void tarjan(reg int u,reg int id){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		if(i==id)
			continue;
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v,i^1);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++eDcc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			col[v]=eDcc_cnt;
		}while(u!=v);
	}
	return;
}

int main(void){
	f=read(),r=read();
	for(reg int i=1;i<=r;++i){
		u[i]=read(),v[i]=read();
		Add_Edge(u[i],v[i]);
		Add_Edge(v[i],u[i]);
	}
	for(reg int i=1;i<=f;++i)
		if(!dfn[i])
			tarjan(i,0);
	for(reg int i=1;i<=r;++i)
		if(col[u[i]]!=col[v[i]])
			++deg[col[u[i]]],++deg[col[v[i]]];
	reg int ans=0;
	for(reg int i=1;i<=eDcc_cnt;++i)
		if(deg[i]==1)
			++ans;
	printf("%d\n",(ans+1)>>1);
	return 0;
}