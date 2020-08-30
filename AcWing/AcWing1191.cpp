#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=100+5;
const int MAXE=MAXN*MAXN;

int n;
int inDeg[MAXN];
int cnt,head[MAXN],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

queue<int> Q;

int main(void){
	scanf("%d",&n);
	for(reg int i=1;i<=n;++i){
		static int x;
		do{
			scanf("%d",&x);
			if(x){
				Add_Edge(i,x);
				++inDeg[x];
			}
		}while(x);
	}
	for(reg int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		printf("%d ",u);
		for(reg int i=head[u];i;i=Next[i]){
			reg int v=to[i];
			--inDeg[v];
			if(!inDeg[v])
				Q.push(v);
		}
	}
	putchar('\n');
	return 0;
}