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

const int MAXN=1e5+5;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline ll dfs(reg int u){
	reg ll res=a[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		res^=dfs(v)+1;
	}
	return res;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		cnt=0,fill(head+1,head+n+1,0);
		for(reg int i=2;i<=n;++i){
			static int p;
			p=read();
			Add_Edge(p,i);
		}
		for(reg int i=1;i<=n;++i)
			a[i]=read();
		puts(dfs(1)?"Alice":"Bob");
	}
	return 0;
}