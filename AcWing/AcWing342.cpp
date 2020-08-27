#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXT=2.5e5+5;
const int MAXR=5e5+5;
const int MAXP=5e5+5;
const int MAXE=MAXR*2+MAXP;

int T,R,P,S;
int cnt,head[MAXT],to[MAXE],Next[MAXE];
ll w[MAXE];

inline void Add_Edge(reg int u,reg int v,reg ll len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

const ll inf=0x3f3f3f3f3f3f3f3fll;

bool inque[MAXT];
ll dis[MAXT];
deque<int> Q;

inline void spfa(reg int s){
	memset(inque,false,sizeof(inque));
	memset(dis,0x3f,sizeof(dis));
	reg int tot=0;
	reg ll sum=0;
	inque[s]=true,++tot,dis[s]=0,Q.push_back(s);
	while(!Q.empty()){
		reg int u=Q.front();
		while(dis[u]*tot>sum){
			Q.pop_front();
			Q.push_back(u);
			u=Q.front();
		}
		Q.pop_front();
		inque[u]=false,--tot,sum-=dis[u];
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]>dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					inque[v]=true,++tot,sum+=dis[v];
					if(!Q.empty()&&dis[v]<dis[Q.front()])
						Q.push_front(v);
					else
						Q.push_back(v);
				}
			}
		}
	}
	return;
}

int main(void){
	scanf("%d%d%d%d",&T,&R,&P,&S);
	for(reg int i=1;i<=R;++i){
		static int a,b;
		static ll c;
		scanf("%d%d%lld",&a,&b,&c);
		Add_Edge(a,b,c);
		Add_Edge(b,a,c);
	}
	for(reg int i=1;i<=P;++i){
		static int a,b;
		static ll c;
		scanf("%d%d%lld",&a,&b,&c);
		Add_Edge(a,b,c);
	}
	spfa(S);
	for(reg int i=1;i<=T;++i)
		if(dis[i]==inf)
			puts("NO PATH");
		else
			printf("%lld\n",dis[i]);
	return 0;
}