#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

const int MAXN=500000+5;

int n;
char val[MAXN];
int fa[MAXN];
int cnt,head[MAXN],to[MAXN],Next[MAXN];
ll f[MAXN];
ll sum[MAXN];
int top;
int S[MAXN];

inline void Add_Edge(reg int,reg int);
inline void DFS(reg int);

int main(void){
	scanf("%d\n%s",&n,val+1);
	for(reg int i=2;i<=n;++i){
		scanf("%d",&fa[i]);
		Add_Edge(fa[i],i);
	}
	DFS(1);
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans^=(ll)i*sum[i];
	printf("%lld\n",ans);
	return 0;
}

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

inline void DFS(reg int ID){
	int flag=0;
	if(val[ID]=='(')
		S[++top]=ID;
	else
		if(top){
			flag=S[top];
			f[ID]=f[fa[flag]]+1;
			--top;
		}
	sum[ID]=sum[fa[ID]]+f[ID];
	for(reg int i=head[ID];i;i=Next[i])
		DFS(to[i]);
	if(flag)
		S[++top]=flag;
	else if(top)
		--top;
	return;
}
