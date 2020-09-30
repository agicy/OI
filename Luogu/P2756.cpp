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

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXE=MAXN*MAXM;

int n,m;
int cnt,head[MAXM],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
int mat[MAXN];

inline bool dfs(reg int u){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!vis[v]){
			vis[v]=true;
			if(!mat[v]||dfs(mat[v])){
				mat[v]=u;
				return true;
			}
		}
	}
	return false;
}

int main(void){
	m=read(),n=read();
	while(true){
		static int u,v;
		u=read(),v=read();
		if(u==-1&&v==-1)
			break;
		Add_Edge(u,v-m);
	}
	reg int ans=0;
	for(reg int i=1;i<=m;++i){
		memset(vis,false,sizeof(vis));
		if(dfs(i))
			++ans;
	}
	printf("%d\n",ans);
	for(reg int i=1;i<=n-m;++i)
		if(mat[i])
			printf("%d %d\n",mat[i],i+m);
	return 0;
}