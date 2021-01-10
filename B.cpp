#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline ll read(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ll*res+(ch^'0'),ch=getchar();
	return res;
}

clock_t st,ed;

const int MAXK=15+5;
const int MAXQ=5e5+5;

int K;
ll n,b;
int q;
ll P[MAXQ],Q[MAXQ];

namespace Subtask2{
	const int MAXB=1e4+5;
	int a[MAXB],sum[MAXB];
	inline bool check(void){
		for(reg int i=1;i<=b;++i)
			sum[i]=sum[i-1]+a[i];
		for(reg int i=1;i<=q;++i)
			if(sum[P[i]]!=Q[i])
				return false;
		return true;
	}
	inline void dfs(reg int x){
		if(x==K){
			if(check()){
				puts("Clever squirrel!");
				exit(0);
				return;
			}
			ed=clock();
			if((double)(ed-st)/CLOCKS_PER_SEC>0.8){
				puts("Boo!");
				exit(0);
			}
			return;
		}
		for(reg int i=x;i<=b;i+=K){
			if(i){
				++a[i];
				dfs(x+1);
				--a[i];
			}
		}
		return;
	}
	inline void Solve(void){
		dfs(0);
		puts("Boo!");
		exit(0);
		return;
	}
}

namespace Subtask3{
	const int MAXB=1e4+5;
	const int MAXCNT=1e4+5;
	const int MAXV=MAXB*2;
	const int MAXE=MAXB+2*MAXQ+2*MAXB;
	int cnt,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
		return;
	}
	bool inque[MAXB];
	int dis[MAXB];
	int in[MAXB];
	queue<int> Qu;
	inline bool spfa(int s){
		memset(in,0,sizeof(in));
		memset(dis,0x3f,sizeof(dis));
		inque[s]=true,dis[s]=0,in[s]=1,Qu.push(s);
		while(!Qu.empty()){
			reg int u=Qu.front();
			Qu.pop();
			inque[u]=false;
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dis[v]>dis[u]+w[i]){
					dis[v]=dis[u]+w[i];
					if(!inque[v]){
						inque[v]=true;
						++in[v];
						if(in[v]>MAXCNT)
							return false;
						Qu.push(v);
					}
				}
			}
		}
		return true;
	}
	inline void Solve(void){
		reg int zero=0;
		for(reg int i=1;i<=b;++i)
			Add_Edge(i-1,i,1);
		Add_Edge(zero,b,n);
		Add_Edge(b,zero,-n);
		for(reg int i=1;i<=q;++i){
			Add_Edge(zero,P[i],Q[i]);
			Add_Edge(P[i],zero,-Q[i]);
		}
		reg bool ans=spfa(zero);
		if(ans)
			puts("Clever squirrel!");
		else
			puts("Boo!");
		return;
	}
}

int main(void){
	st=clock();
	K=read(),n=read(),b=read(),q=read();
	for(reg int i=1;i<=q;++i)
		P[i]=read(),Q[i]=read();
	if(K==n)
		Subtask2::Solve();
	else if(b<=1e4)
		Subtask3::Solve();
	return 0;
}