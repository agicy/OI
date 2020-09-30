#include<bits/stdc++.h>
using namespace std;
#define reg register
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

const int MAXN=1e5+5;
const int inf=0x3f3f3f3f;

int n,K;

namespace Graph{
	int cnt=1,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int pre[MAXN];
	int dis[MAXN];
	queue<int> Q;
	inline int bfs(int s){
		memset(dis,0x3f,sizeof(dis));
		while(!Q.empty())Q.pop();
		pre[s]=dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dis[v]==inf){
					dis[v]=dis[u]+w[i];
					pre[v]=i;
					Q.push(v);
				}
			}
		}
		reg int p=1;
		for(reg int i=1;i<=n;++i)
			if(dis[i]>dis[p])
				p=i;
		return p;
	}
	inline int getD(void){
		reg int p=bfs(1);
		p=bfs(p);
		return p;
	}
	inline void update(reg int s){
		for(reg int p=s;pre[p];p=to[pre[p]^1])
			w[pre[p]]=w[pre[p]^1]=-1;
		return;
	}
	bool vis[MAXN];
	int f[MAXN];
	inline void dp(reg int u,reg int &ans){
		vis[u]=true;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(!vis[v]){
				dp(v,ans);
				cMax(ans,f[v]+f[u]+w[i]);
				cMax(f[u],f[v]+w[i]);
			}
		}
		return;
	}
};

using namespace Graph;

int main(void){
	n=read(),K=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		Add_Edge(a,b,1);
		Add_Edge(b,a,1);
	}
	reg int ans=0;
	if(K==1){
		reg int p=getD();
		ans=(n<<1)-dis[p]-1;
	}
	else if(K==2){
		reg int p=getD();
		update(p);
		int tmp=0;
		dp(1,tmp);
		ans=(n<<1)-dis[p]-tmp;
	}
	printf("%d\n",ans);
	return 0;
}