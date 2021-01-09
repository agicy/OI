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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2e5+5;

int n;
ll s[MAXN],dis[MAXN];
vector<int> head[MAXN];
vector<int> to[MAXN];

inline void Add_Edge(int u,int v){
	head[u].push_back(v);
	to[v].push_back(u);
	return;
}

bool inque[MAXN];

inline void spfa(void){
	queue<int> Q;
	for(int i=1;i<=n;++i){
		inque[i]=true;
		Q.push(i);
	}
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		reg ll tmp=s[u];
		for(int v:head[u])
			tmp+=dis[v];
		if(tmp>=dis[u])
			continue;
		dis[u]=tmp;
		for(int v:to[u])
			if(!inque[v]){
				inque[v]=true;
				Q.push(v);
			}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		static int r;
		s[i]=readll(),dis[i]=readll(),r=read();
		for(reg int j=1;j<=r;++j){
			static int x;
			x=read();
			Add_Edge(i,x);
		}
	}
	spfa();
	printf("%lld\n",dis[1]);
	return 0;
}