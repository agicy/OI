#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=1e4+5;
const int MAXM=100+5;
const int MAXK=1e7+5;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],nxt[MAXN<<1];
int k[MAXM];
bool ans[MAXK];

inline void Add_Edge(reg int u,reg int v,reg int len){
	nxt[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

bool del[MAXN];
int rt,MaxPart,sum;
int siz[MAXN];

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]&&v!=father){
			getRt(v,u);
			Max=max(Max,siz[v]);
			siz[u]+=siz[v];
		}
	}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

bool inV[MAXK];
int tot,V[MAXN];
int tmp,sonV[MAXN];

inline void dfs(reg int u,reg int father,reg int dis){
	if(dis>=MAXK)
		return;
	for(reg int i=1;i<=m;++i)
		if(0<=k[i]-dis&&k[i]-dis<MAXK&&inV[k[i]-dis])
			ans[i]=true;
	sonV[++tmp]=dis;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]&&v!=father)
			dfs(v,u,dis+w[i]);
	}
	return;
}

inline void calc(reg int u){
	inV[0]=true,V[++tot]=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]){
			dfs(v,0,w[i]);
			while(tmp){
				if(sonV[tmp]<MAXK&&!inV[sonV[tmp]])
					inV[sonV[tmp]]=true,V[++tot]=sonV[tmp];
				--tmp;
			}
		}
	}
	while(tot)
		inV[V[tot--]]=false;
	return;
}

inline void solve(reg int u){
	del[u]=true;
	calc(u);
	reg int las=sum;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]){
			reg int s=siz[v];
			if(s>siz[u])
				s=las-siz[u];
			rt=-1,MaxPart=inf,sum=s;
			getRt(v,0),solve(rt);
		}
	}
	return;
}

bool ed;

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=m;++i)
		k[i]=read();
	rt=-1,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	for(reg int i=1;i<=m;++i)
		puts(ans[i]?"AYE":"NAY");
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}