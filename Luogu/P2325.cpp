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

const int MAXN=1e3+5;

int n,B;
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int top,S[MAXN];
int tot,rt[MAXN],col[MAXN];

inline void dfs(reg int u,reg int father){
	reg int tmp=top;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			dfs(v,u);
			if(top-tmp>=B){
				rt[++tot]=u;
				while(top>tmp)
					col[S[top--]]=tot;
			}
		}
	}
	S[++top]=u;
	return;
}

int main(void){
	n=read(),B=read();
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	dfs(1,0);
	if(!tot)
		rt[++tot]=1;
	while(top)
		col[S[top--]]=tot;
	printf("%d\n",tot);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",col[i],i==n?'\n':' ');
	for(reg int i=1;i<=tot;++i)
		printf("%d%c",rt[i],i==tot?'\n':' ');
	return 0;
}