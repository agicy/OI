#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXM=2e5+5;
const int p=100003;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

int n,m;
int cnt,head[MAXN],to[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
int dis[MAXN];
queue<int> Q;
int f[MAXN];

inline void spfa(reg int s){
	memset(dis,0x3f,sizeof(dis));
	inque[s]=true,dis[s]=0,f[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+1){
				dis[v]=dis[u]+1;
				f[v]=f[u];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
			else if(dis[v]==dis[u]+1)
				f[v]=add(f[v],f[u]);
		}
	}
	return;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		Add_Edge(x,y);
		Add_Edge(y,x);
	}
	spfa(1);
	for(reg int i=1;i<=n;++i)
		printf("%d\n",f[i]);
	return 0;
}