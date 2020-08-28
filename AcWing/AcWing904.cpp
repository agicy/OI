#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;
const int MAXM=2.5e3+5;
const int MAXW=200+5;
const int MAXE=2*MAXM+MAXW;

int n,m,W;
int cnt,head[MAXN],to[MAXE],w[MAXE],Next[MAXE];

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
	while(!Q.empty())
		Q.pop();
	inque[s]=true,in[s]=1,Q.push(s);
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
	int F;
	scanf("%d",&F);
	while(F--){
		cnt=0,memset(head,0,sizeof(head));
		scanf("%d%d%d",&n,&m,&W);
		for(reg int i=1;i<=m;++i){
			static int s,e,t;
			scanf("%d%d%d",&s,&e,&t);
			Add_Edge(s,e,t);
			Add_Edge(e,s,t);
		}
		for(reg int i=1;i<=W;++i){
			static int s,e,t;
			scanf("%d%d%d",&s,&e,&t);
			Add_Edge(s,e,-t);
		}
		memset(inque,false,sizeof(inque));
		memset(in,0,sizeof(in));
		memset(dis,0x3f,sizeof(dis));
		reg bool ans=true;
		for(reg int i=1;i<=n;++i)
			if(dis[i]==0x3f3f3f3f){
				reg bool flag=spfa(i);
				if(!flag){
					ans=false;
					break;
				}
			}
		puts(ans?"NO":"YES");
	}
	return 0;
}