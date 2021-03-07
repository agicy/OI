#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef unsigned int uint;
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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=5e3+5;
const int inf=0x3f3f3f3f;

int n;
char s[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int rt,MaxPart,sum;

inline int getRt(reg int u,reg int father){
	reg int siz=s[u]&1;
	reg int Max=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			reg int res=getRt(v,u);
			siz+=res;
			Max=max(Max,res);
		}
	}
	Max=max(Max,sum-siz);
	if(Max<MaxPart)
		rt=u,MaxPart=Max;
	return siz;
}

int siz[MAXN],pcnt[MAXN];
int cost[MAXN];

inline vector<int> dfs(reg int u,reg int father){
	vector<int> f;
	siz[u]=1,pcnt[u]=s[u]&1,cost[u]=0;
	f.resize(siz[u]+pcnt[u]+1,inf);
	f[pcnt[u]-1+siz[u]]=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			vector<int> res=dfs(v,u);
			if(pcnt[v]){
				vector<int> tmp;
				tmp.resize(siz[u]+siz[v]+pcnt[u]+pcnt[v]+1,inf);
				for(reg int i=-siz[u];i<=pcnt[u];++i)
					for(reg int j=-siz[v];j<=pcnt[v];++j)
						tmp[i+j+siz[u]+siz[v]]=min(tmp[i+j+siz[u]+siz[v]],f[i+siz[u]]+res[j+siz[v]]+abs(j));
				f=tmp;
				siz[u]+=siz[v],pcnt[u]+=pcnt[v],cost[u]+=pcnt[v]+cost[v];
			}
		}
	}
	f[pcnt[u]+siz[u]]=cost[u];
	return f;
}

int main(void){
	n=read(),read(s+1);
	for(reg int i=1;i<=n;++i)
		sum+=s[i]&1;
	for(reg int i=1;i<n;++i){
		static int u,v;
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	rt=0,MaxPart=inf;
	getRt(1,0);
	vector<int> ans=dfs(rt,0);
	printf("%d\n",ans[siz[rt]]);
	return 0;
}