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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

inline ll min(reg ll a,reg ll b){
	return a<b?a:b;
}

const int MAXN=1e5+5;

int n;
int cnt,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

int tot,cir[MAXN],dis[MAXN];
bool tag[MAXN];

struct Node{
	int id,len;
	inline Node(reg int id=0,reg int len=0):id(id),len(len){
		return;
	}
};

bool vis[MAXN];
int top;
Node S[MAXN];

inline bool dfs1(reg int u,reg int father,reg int len){
	vis[u]=true;
	S[++top]=Node(u,len);
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(v!=father){
			if(!vis[v]){
				if(dfs1(v,u,w[i]))
					return true;
			}
			else{
				while(S[top].id!=v){
					tag[S[top].id]=true;
					cir[++tot]=S[top].id,dis[tot]=S[top].len;
					--top;
				}
				tag[v]=true;
				cir[++tot]=v,dis[tot]=w[i];
				return true;
			}
		}
	}
	vis[u]=false;
	--top;
	return false;
}

ll ans1,ans2;
ll f[MAXN];

inline void dfs2(reg int u,reg int fa){
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!tag[v]&&v!=fa){
			dfs2(v,u);
			ans1=max(ans1,0ll+f[u]+f[v]+w[i]);
			f[u]=max(f[u],f[v]+w[i]);
		}
	}
	return;
}

ll A[MAXN],B[MAXN],C[MAXN],D[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int a,b,l;
		a=read(),b=read(),l=read();
		Add_Edge(a,b,l),Add_Edge(b,a,l);
	}
	dfs1(1,0,0);
	for(reg int i=1;i<=tot;++i)
		dfs2(cir[i],0);
	reg ll sum=0,Max=0;
	for(reg int i=1;i<=tot;++i){
		sum+=dis[i-1];
		A[i]=max(A[i-1],f[cir[i]]+sum);
		B[i]=max(B[i-1],sum+Max+f[cir[i]]);
		Max=max(Max,f[cir[i]]-sum);
	}
	sum=Max=0;
	reg int tmp=dis[tot];
	dis[tot]=0;
	for(reg int i=tot;i>=1;--i){
		sum+=dis[i];
		C[i]=max(C[i+1],f[cir[i]]+sum);
		D[i]=max(D[i+1],sum+Max+f[cir[i]]);
		Max=max(Max,f[cir[i]]-sum);
	}
	ans2=B[tot];
	for(reg int i=1;i<tot;++i)
		ans2=min(max(max(B[i],D[i+1]),A[i]+C[i+1]+tmp),ans2);
	printf("%.1lf\n",0.5*max(ans1,ans2));
	return 0;
}