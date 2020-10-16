#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
    reg char ch=getchar();
    reg int res=0;
    while(ch<'0'||'9'<ch)ch=getchar();
    while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
    return res;
}

const int MAXN=50+5;
const int MAXV=MAXN;
const int MAXE=MAXN*MAXN;

int n;
int stu[MAXN],bac[MAXN];
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int mat[MAXV];

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
	reg int T=read();
	while(T--){
		cnt=0,memset(head,0,sizeof(head));
		n=read();
		for(reg int i=1;i<=n;++i)
			stu[i]=read();
		for(reg int i=1;i<=n;++i){
			bac[i]=read();
			if(stu[i]&&!bac[i])
				Add_Edge(i,i);
		}
		reg int tot=0;
		for(reg int i=1;i<=n;++i)
			if(!stu[i]||(stu[i]&&!bac[i]))
				++tot;
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=n;++j){
				static int x;
				x=read();
				if(x&&stu[j])
					Add_Edge(i,j);
			}
		memset(mat,0,sizeof(mat));
		reg int ans=0;
		for(reg int i=1;i<=n;++i)
			if((stu[i]&&!bac[i])||!stu[i]){
				memset(vis,false,sizeof(vis));
				if(dfs(i))
					++ans;
			}
		puts(ans==tot?"^_^":"T_T");
	}
	return 0;
}