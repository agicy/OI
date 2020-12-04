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

const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m;
int t[MAXM],x[MAXM],y[MAXM];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int indeg[MAXN];
int dfn[MAXN];
queue<int> Q;

inline void topo(void){
	for(reg int i=1;i<=n;++i)
		if(!indeg[i])
			Q.push(i);
	reg int tim=0;
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		dfn[u]=++tim;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--indeg[v];
			if(!indeg[v])
				Q.push(v);
		}
	}
	reg bool flag=false;
	for(reg int i=1;i<=n;++i)
		if(indeg[i]){
			flag=true;
			break;
		}
	if(flag)
		puts("NO");
	else{
		puts("YES");
		for(reg int i=1;i<=m;++i)
			if(t[i])
				printf("%d %d\n",x[i],y[i]);
			else{
				reg int u=x[i],v=y[i];
				if(dfn[u]<dfn[v])
					printf("%d %d\n",u,v);
				else
					printf("%d %d\n",v,u);
			}
	}
	return;
}

int main(void){
	reg int T=read();
	while(T--){
		n=read(),m=read();
		cnt=0,fill(head+1,head+n+1,0);
		fill(indeg+1,indeg+n+1,0);
		reg int tot=0;
		for(reg int i=1;i<=m;++i){
			t[i]=read(),x[i]=read(),y[i]=read();
			if(t[i]){
				Add_Edge(x[i],y[i]);
				++indeg[y[i]];
			}
		}
		topo();
	}
	return 0;
}