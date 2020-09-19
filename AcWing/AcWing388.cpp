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

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

inline int lowbit(reg int x){
	return x&(-x);
}

const int MAXN=16;
const int MAXM=MAXN*(MAXN-1)/2;
const int inf=0x3f3f3f3f;

struct Edge{
	int u,v,w;
	inline Edge(reg int u=0,reg int v=0,reg int w=0):u(u),v(v),w(w){
		return;
	}
	inline bool operator<(const Edge &a)const{
		return w<a.w;
	}
};

int n,m;
int a[MAXN];
Edge E[MAXM];
int fa[MAXN];
int Lg[1<<MAXN],sum[1<<MAXN],val[1<<MAXN];
int dp[1<<MAXN];

inline int find(reg int x){
	if(x==fa[x])
		return x;
	else
		return fa[x]=find(fa[x]);
}

inline int Kruskal(reg int S){
	reg int tot=0,sum=0;
	for(reg int i=S;i;i^=lowbit(i)){
		reg int x=Lg[lowbit(i)];
		++tot;
		fa[x]=x;
	}
	reg int cnt=tot;
	for(reg int i=0;i<m&&cnt>1;++i)
		if(((S>>E[i].u)&1)&&((S>>E[i].v)&1)){
			reg int ra=find(E[i].u),rb=find(E[i].v);
			if(ra!=rb){
				--cnt;
				sum+=E[i].w;
				fa[rb]=ra;
			}
		}
	if(cnt==1)
		return sum;
	else
		return -1;
}

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i)
		a[i]=read();
	for(reg int i=0;i<m;++i)
		E[i].u=read(),E[i].v=read(),E[i].w=read();
	sort(E,E+m);
	reg int U=(1<<n)-1;
	Lg[0]=-1;
	for(reg int i=1;i<=U;++i)
		Lg[i]=Lg[i>>1]+1;
	for(reg int S=0;S<=U;++S)
		for(reg int i=S;i;i^=lowbit(i)){
			reg int x=Lg[lowbit(i)];
			sum[S]+=a[x];
		}
	for(reg int S=0;S<=U;++S)
		if(!sum[S])
			val[S]=Kruskal(S);
		else
			val[S]=-1;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;
	for(reg int S=0;S<=U;++S)
		if(!sum[S]){
			if(val[S]!=-1)
				dp[S]=val[S];
			for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
				if(val[S^sub]!=-1)
					cMin(dp[S],dp[sub]+val[S^sub]);
		}
	if(dp[U]==inf)
		puts("Impossible");
	else
		printf("%d\n",dp[U]);
	return 0;
}