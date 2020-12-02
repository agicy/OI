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

const int MAXN=1e6+5;
const int MAXV=1e4+5;
const int MAXE=2*MAXN;

int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int id;
int vis[MAXN],mat[MAXN];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(vis[v]!=id){
			vis[v]=id;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	reg int n=read();
	for(reg int i=1;i<=n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,i);
		Add_Edge(b,i);
	}
	reg int ans=0;
	for(reg int i=1;i<=1e4;++i){
		id=i;
		if(dfs(i))
			++ans;
		else
			break;
	}
	printf("%d\n",ans);
	return 0;
}