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

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

inline void Err(void){
	puts("-1");
	exit(0);
	return;
}

const int MAXN=1e5+5;
const int MAXK=1e5+5;
const int MAXV=MAXN;
const int MAXE=2*MAXK;

int n,k;
int x[MAXK],a[MAXK],b[MAXK];
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void Add_Edge(reg int u,reg int v,reg bool f){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=f;
	head[u]=cnt;
	return;
}

bool vis[MAXV];
int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int scc_cnt,col[MAXV],siz[MAXV];

inline void tarjan(reg int u){
	vis[u]=true;
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
		}
		else if(vis[v])
			cMin(low[u],dfn[v]);
	}
	if(dfn[u]==low[u]){
		reg int v;
		++scc_cnt;
		do{
			v=S[top--];
			vis[v]=false;
			++siz[scc_cnt];
			col[v]=scc_cnt;
		}while(v!=u);
	}
	return;
}

int inDeg[MAXV];
int f[MAXV];
queue<int> Q;

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=k;++i){
		x[i]=read(),a[i]=read(),b[i]=read();
		switch(x[i]){
			case 1:{
				Add_Edge(a[i],b[i]);
				Add_Edge(b[i],a[i]);
				break;
			}
			case 3:{
				Add_Edge(b[i],a[i]);
				break;
			}
			case 5:{
				Add_Edge(a[i],b[i]);
				break;
			}
		}
	}
	for(reg int i=1;i<=n;++i)
		if(!dfn[i])
			tarjan(i);
	cnt=0,memset(head,0,sizeof(head));
	for(reg int i=1;i<=k;++i){
		switch(x[i]){
			case 2:{
				if(col[a[i]]==col[b[i]])
					Err();
				Add_Edge(col[a[i]],col[b[i]],true);
				++inDeg[col[b[i]]];
				break;
			}
			case 3:{
				if(col[a[i]]!=col[b[i]]){
					Add_Edge(col[b[i]],col[a[i]],false);
					++inDeg[col[a[i]]];
				}
				break;
			}
			case 4:{
				if(col[b[i]]==col[a[i]])
					Err();
				Add_Edge(col[b[i]],col[a[i]],true);
				++inDeg[col[a[i]]];
				break;
			}
			case 5:{
				if(col[a[i]]!=col[b[i]]){
					++inDeg[col[b[i]]];
					Add_Edge(col[a[i]],col[b[i]],false);
				}
				break;
			}
		}
	}
	for(int i=1;i<=scc_cnt;++i)
		if(!inDeg[i])
			f[i]=1,Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			--inDeg[v];
			if(w[i])
				cMax(f[v],f[u]+1);
			else
				cMax(f[v],f[u]);
			if(!inDeg[v])
				Q.push(v);
		}
	}
	reg ll ans=0;
	for(reg int i=1;i<=scc_cnt;++i){
		if(inDeg[i])
			Err();
		ans+=1ll*f[i]*siz[i];
	}
	printf("%lld\n",ans);
	return 0;
}