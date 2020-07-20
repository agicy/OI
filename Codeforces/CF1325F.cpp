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

const int MAXN=100000+5;
const int MAXM=200000+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];
int fa[MAXN],dep[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tot;
int Q[MAXN];
bool vis[MAXN];

inline void DFS(reg int ID){
	Q[++tot]=ID;
	dep[ID]=dep[fa[ID]]+1;
	for(reg int i=head[ID];i;i=Next[i])
		if(!dep[to[i]]){
			fa[to[i]]=ID;
			DFS(to[i]);
		}
		else if(dep[to[i]]<dep[ID]){
			reg int l=dep[ID]-dep[to[i]]+1;
			if(l*l>=n){
				printf("2\n%d\n",l);
				for(reg int j=ID;j;j=fa[j]){
					printf("%d%c",j,j==to[i]?'\n':' ');
					if(j==to[i])
						break;
				}
				exit(0);
			}
		}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v);
		Add_Edge(v,u);
	}
	DFS(1);
	reg int l=1;
	for(;l*l<n;++l);
	reg int rem=l;
	puts("1");
	for(reg int i=n;i>=1;--i){
		reg int x=Q[i];
		if(vis[x])
			continue;
		--rem;
		printf("%d%c",x,rem?' ':'\n');
		if(!rem)
			exit(0);
		for(reg int j=0;j<=l-2;++j){
			vis[x]=true;
			x=fa[x];
		}
	}
	return 0;
}
