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

const int MAXN=1000+5;
const int MAXM=25000+5;

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool vis[MAXN];
ll dis[MAXN];
queue<int> Q;

inline void BFS(int s){
	memset(vis,false,sizeof(vis));
	memset(dis,0X3F,sizeof(dis));
	while(!Q.empty())Q.pop();
	vis[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		vis[ID]=true;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+1){
				dis[to[i]]=dis[ID]+1;
				Q.push(to[i]);
			}
	}
	return;
}

int main(void){
	while(n=read(),m=read(),n!=0&&m!=0){
		cnt=0;
		memset(head,0,sizeof(head));
		for(reg int i=1;i<=m;++i){
			static int a,b;
			a=read(),b=read();
			Add_Edge(a,b);
			Add_Edge(b,a);
		}
		ll ans=0;
		for(reg int i=1;i<=n;++i){
			BFS(i);
			ll Max=0;
			for(reg int j=1;j<=n;++j)
				if(vis[j])
				    Max=max(Max,dis[j]);
            ans=max(ans,Max);
		}
		printf("%lld\n",ans*100ll);
	}
	return 0;
}
