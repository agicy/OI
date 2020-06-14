#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
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

const int MAXN=100000+5;

int n,K;

namespace Graph{
	int cnt=1,head[MAXN],to[MAXN<<1],w[MAXN<<1],Next[MAXN<<1];
	inline void Add_Edge(reg int u,reg int vis,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=vis;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	int pre[MAXN];
	int dis[MAXN];
	queue<int> Q;
	inline int BFS(int s){
		memset(dis,0X3F,sizeof(dis));
		while(!Q.empty())Q.pop();
		pre[s]=dis[s]=0,Q.push(s);
		while(!Q.empty()){
			reg int ID=Q.front();
			Q.pop();
			for(reg int i=head[ID];i;i=Next[i])
				if(dis[to[i]]==INF){
					dis[to[i]]=dis[ID]+w[i];
					pre[to[i]]=i;
					Q.push(to[i]);
				}
		}
		reg int p=1;
		for(reg int i=1;i<=n;++i)
			if(dis[i]>dis[p])
				p=i;
		return p;
	}
	inline int GetD(void){
		reg int p=BFS(1);
		p=BFS(p);
		return p;
	}
	inline void Update(reg int s){
		for(reg int p=s;pre[p];p=to[pre[p]^1])
			w[pre[p]]=w[pre[p]^1]=-1;
		return;
	}
	bool vis[MAXN];
	int f[MAXN];
	inline void dp(reg int ID,reg int &ans){
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(!vis[to[i]]){
				dp(to[i],ans);
				ans=max(ans,f[to[i]]+f[ID]+w[i]);
				f[ID]=max(f[ID],f[to[i]]+w[i]);
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
		reg int p=GetD();
		ans=(n<<1)-dis[p]-1;
	}
	if(K==2){
		reg int p=GetD();
		Update(p);
		int temp=0;
		dp(1,temp);
		ans=(n<<1)-dis[p]-temp;
	}
	printf("%d\n",ans);
	return 0;
}
