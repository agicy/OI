#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=2e3+5;
const int MAXM=1e4+5;

int n,m;
int cnt,head[MAXN],to[MAXM],w[MAXM],Next[MAXM];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
int in[MAXN];
int dis[MAXN];
queue<int> Q;

inline bool spfa(reg int s){
	memset(inque,false,sizeof(inque));
	memset(in,0,sizeof(in));
	//memset(dis,0x3f,sizeof(dis));
	inque[s]=true,in[s]=1,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true;
					++in[v];
					if(in[v]>n)
						return false;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int main(void){
	scanf("%d%d",&n,&m);
	for(reg int i=1;i<=m;++i){
		static int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		Add_Edge(x,y,z);
	}
	memset(dis,0x3f,sizeof(dis));
	for(reg int i=1;i<=n;++i)
		if(dis[i]==0x3f3f3f3f){
			reg bool flag=spfa(i);
			if(!flag){
				puts("Yes");
				return 0;
			}
		}
	puts("No");
	return 0;
}