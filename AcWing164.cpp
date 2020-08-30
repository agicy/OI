#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=3e4+5;
const int MAXM=3e4+5;

int n,m;
int inDeg[MAXN];
int cnt,head[MAXN],to[MAXM],Next[MAXM];

inline void Add_Edge(int u,int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,id[MAXN],rnk[MAXN];
queue<int> Q;

inline void topo(void){
	for(int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i),id[i]=++tim,rnk[tim]=i;
	while(!Q.empty()){
		int u=Q.front();
		Q.pop();
		for(int i=head[u];i;i=Next[i]){
			int v=to[i];
			--inDeg[v];
			if(!inDeg[v]){
				id[v]=++tim,rnk[tim]=v;
				Q.push(v);
			}
		}
	}
	return;
}

bitset<MAXN> A[MAXN];

int main(void){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i){
		static int x,y;
		scanf("%d%d",&x,&y);
		++inDeg[y];
		Add_Edge(x,y);
	}
	for(int i=1;i<=n;++i)
		A[i][i]=true;
	topo();
	for(int i=tim;i>=1;--i)
		for(int j=head[rnk[i]];j;j=Next[j])
			A[rnk[i]]|=A[to[j]];
	for(int i=1;i<=n;++i)
		printf("%d\n",A[i].count());
	return 0;
}