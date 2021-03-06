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
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e3+5;
const int MAXM=5e3+5;
const int MAXV=MAXN;
const int MAXE=MAXN+MAXM;
const int inf=0x3f3f3f3f;

int n,m;
int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v,w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXV];
int dis[MAXV];
int in[MAXV];
queue<int> Q;

inline bool spfa(int s){
	memset(dis,0x3f,sizeof(dis));
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true;
					++in[v];
					if(in[v]>=n)
						return false;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(v,u,w);
	}
	reg int s=0;
	for(reg int i=1;i<=n;++i)
		Add_Edge(s,i,0);
	reg bool res=spfa(s);
	if(res){
		reg int Min=inf;
		for(reg int i=1;i<=n;++i)
			Min=min(Min,dis[i]);
		for(reg int i=1;i<=n;++i)
			printf("%d\n",dis[i]-Min);
	}
	else
		puts("NO SOLUTION");
	return 0;
}