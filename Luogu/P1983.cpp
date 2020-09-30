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

const int MAXN=1e3+5;
const int MAXM=1e3+5;
const int MAXE=MAXN*MAXN;

int n,m;
bool vis[MAXN];
bool G[MAXN][MAXN];
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int inDeg[MAXN],f[MAXN];
queue<int> Q;

inline void topo(void){
	for(int i=1;i<=n;++i){
		f[i]=1;
		if(!inDeg[i])
			Q.push(i);
	}
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			f[v]=max(f[v],f[u]+1);
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
		}
	}
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int s,p[MAXN];
		s=read();
		for(reg int j=1;j<=s;++j){
			p[j]=read();
			vis[p[j]]=true;
		}
		for(reg int k=p[1];k<=p[s];++k)
			if(!vis[k])
				for(reg int j=1;j<=s;++j)
					if(!G[k][p[j]]){
						G[k][p[j]]=true;
						++inDeg[p[j]];
						Add_Edge(k,p[j]);
					}
		for(reg int j=1;j<=s;++j)
			vis[p[j]]=false;
	}
	topo();
	int ans=1;
	for(reg int i=1;i<=n;++i)
		ans=max(ans,f[i]);
	printf("%d\n",ans);
	return 0;
}