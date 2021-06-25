#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
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
	for(reg int i=head[u];i;i=Next[i]){
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

int top1,top2;
ll S1[MAXN],S2[MAXN];

inline void dfs(reg int u,reg int father,reg ll sum,reg ll ned,reg ll Min,reg int rt){
	if(!ned)
		S1[++top1]=sum;
	S2[++top2]=-Min;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father&&!del[v])
			dfs(v,u,sum-w[i]+a[v],min(0ll,ned-w[i]+a[v]),min(Min,sum-a[rt]-w[i]),rt);
	}
	return;
}

ll ans;

inline void calc(reg int u){
	top2=0;
	S1[top1=1]=a[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			reg int tmp1=top1+1,tmp2=top2+1;
			dfs(v,u,a[u]+a[v]-w[i],min(0,a[v]-w[i]),min(0,-w[i]),u);
			if(top1>=tmp1&&top2>=tmp2){
				sort(S1+tmp1,S1+top1+1),sort(S2+tmp2,S2+top2+1);
				for(reg int l=tmp1,r=tmp2;l<=top1;++l){
					while(r<=top2&&S1[l]>=S2[r])
						++r;
					ans-=r-tmp2;
				}
			}
		}
	}
	sort(S1+1,S1+top1+1),sort(S2+1,S2+top2+1);
	for(reg int l=1,r=1;l<=top1;++l){
		while(r<=top2&&S1[l]>=S2[r])
			++r;
		ans+=r-1;
	}
	ans+=top1-1;
	return;
}

inline void solve(reg int u){
	del[u]=true;
	calc(u);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!del[v]){
			rt=0,MaxPart=inf,sum=siz[v];
			getRt(v,u),solve(rt);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<n;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w),Add_Edge(v,u,w);
	}
	rt=0,MaxPart=inf,sum=n;
	getRt(1,0),solve(rt);
	printf("%lld\n",ans);
	return 0;
}