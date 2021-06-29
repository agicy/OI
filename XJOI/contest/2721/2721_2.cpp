#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

const int MAXN=200+5;

int n,A[3],U;
int v[MAXN];
int cnt,head[MAXN],to[MAXN<<1],nxt[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	nxt[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool del[MAXN];
int siz[MAXN];
int rt,MaxPart,sum;

inline void getRt(reg int u,reg int father){
	siz[u]=1;
	reg int Max=0;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father&&!del[v]){
			getRt(v,u);
			siz[u]+=siz[v];
			Max=max(Max,siz[v]);
		}
	}
	Max=max(Max,sum-siz[u]);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return;
}

int tim,rnk[MAXN];

inline void dfs(reg int u,reg int father){
	siz[u]=1;
	rnk[++tim]=u;
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(v!=father&&!del[v]){
			dfs(v,u);
			siz[u]+=siz[v];
		}
	}
	return;
}

int f[MAXN][42875];
int ans=0;
int BAS[3];

inline void solve(reg int u){
	del[u]=true;
	tim=0,dfs(u,0);
	for(reg int i=1;i<=tim+1;++i)
		memset(f[i],0,sizeof(int)*U);
	f[1][0]=1;
	for(reg int i=1;i<=tim;++i){
		static int a[3];
		reg int id=0;
		for(a[0]=0;a[0]<=A[0];++a[0])
			for(a[1]=0;a[1]<=A[1];++a[1])
				for(a[2]=0;a[2]<=A[2];++a[2]){
					f[i+siz[rnk[i]]][id]=add(f[i+siz[rnk[i]]][id],f[i][id]);
					if(a[v[rnk[i]]]!=A[v[rnk[i]]])
						f[i+1][id+BAS[v[rnk[i]]]]=add(f[i+1][id+BAS[v[rnk[i]]]],f[i][id]);
					++id;
				}
	}
	for(reg int i=1;i<U;++i)
		ans=add(ans,f[tim+1][i]);
	for(reg int i=head[u];i;i=nxt[i]){
		reg int v=to[i];
		if(!del[v]){
			rt=-1,MaxPart=n+1,sum=siz[v];
			getRt(v,0),solve(rt);
		}
	}
	return;
}

bool ed;

int main(void){
	scanf("%d%d%d%d",&n,&A[0],&A[1],&A[2]);
	U=(A[0]+1)*(A[1]+1)*(A[2]+1),BAS[0]=(A[1]+1)*(A[2]+1),BAS[1]=A[2]+1,BAS[2]=1;
	for(reg int i=1;i<=n;++i)
		scanf("%d",&v[i]);
	for(reg int i=1;i<n;++i){
		static int u,v;
		scanf("%d%d",&u,&v);
		Add_Edge(u,v),Add_Edge(v,u);
	}
	rt=-1,MaxPart=n+1,sum=n;
	getRt(1,0),solve(rt);
	printf("%d\n",ans);
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}