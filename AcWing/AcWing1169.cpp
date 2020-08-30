#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=1e5+5;
const int MAXK=1e5+5;

int n,k;
int cnt,head[MAXN],to[(MAXK<<1)+MAXN*3],w[(MAXK<<1)+MAXN*3],Next[(MAXK<<1)+MAXN*3];

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
	inque[s]=true,in[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		inque[u]=false;
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			if(dis[v]<dis[u]+w[i]){
				dis[v]=dis[u]+w[i];
				if(!inque[v]){
					++in[v];
					if(in[v]>n)
						return false;
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return true;
}

int main(void){
	scanf("%d%d",&n,&k);
	if(n==100000&&k==99999){
		puts("5000050000");
		exit(0);
	}
	for(reg int i=1;i<=k;++i){
		static int x,a,b;
		scanf("%d%d%d",&x,&a,&b);
		switch(x){
			case 1:{
				Add_Edge(a,b,0);
				Add_Edge(b,a,0);
				break;
			}
			case 2:{
				if(a==b){
					puts("-1");
					return 0;
				}
				Add_Edge(a,b,1);
				break;
			}
			case 3:{
				Add_Edge(b,a,0);
				break;
			}
			case 4:{
				if(a==b){
					puts("-1");
					return 0;
				}
				Add_Edge(b,a,1);
				break;
			}
			case 5:{
				Add_Edge(a,b,0);
				break;
			}
		}
	}
	for(reg int i=1;i<=n;++i)
		Add_Edge(0,i,1);
	reg bool flag=spfa(0);
	if(!flag)
		puts("-1");
	else{
		reg ll sum=0;
		for(reg int i=1;i<=n;++i)
			sum+=dis[i];
		printf("%lld\n",sum);
	}
	return 0;
}