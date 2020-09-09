#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500+5;

int n;
int cnt,head[MAXN<<1],to[MAXN<<1],Next[MAXN<<1];

inline int Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int main(void){
	while(scanf("%d",&n)!=EOF&&n!=0){
		cnt=0;
		memset(head,0,sizeof(head));
		int Max=0;
		for(reg int i=1;i<=n;++i){
			static int s,t;
			scanf("%d%d",&s,&t);
			Add_Edge(s,t);
			Add_Edge(t,s);
			Max=max(Max,max(s,t));
		}
		for(reg int i=1;i<=n;++i)
	}
	return 0;
}