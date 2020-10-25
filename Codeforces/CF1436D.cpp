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
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

inline void cMax(reg ll& a,reg ll b){
	if(a<b)
		a=b;
	return;
}

const int MAXN=2e5+5;

int n;
int a[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline ll myceil(reg ll a,reg ll b){
	if(!(a%b))
		return a/b;
	else
		return a/b+1;
}

ll ans=-1;
ll sum[MAXN];

inline int dfs(reg int u){
	int cnt;
	if(!head[u])
		cnt=1;
	else
		cnt=0;
	sum[u]=a[u];
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		cnt+=dfs(v);
		sum[u]+=sum[v];
	}
	cMax(ans,myceil(sum[u],cnt));
	return cnt;
}

int main(void){
	n=read();
	for(reg int i=2;i<=n;++i){
		static int p;
		p=read();
		Add_Edge(p,i);
	}
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	dfs(1);
	printf("%lld\n",ans);
	return 0;
}