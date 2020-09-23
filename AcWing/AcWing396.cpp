#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

inline void cMax(reg int &a,reg int b){
	if(a<b)
		a=b;
	return;
}

inline void cMin(reg int &a,reg int b){
	if(a>b)
		a=b;
	return;
}

const int MAXN=500+5;
const int MAXV=2*MAXN;
const int MAXE=2*MAXN;

int n,m;
int cnt,head[MAXV],to[MAXE],Next[MAXE];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

int tim,dfn[MAXV],low[MAXV];
int top,S[MAXV];
int vDcc_cnt;
vector<int> vDcc[MAXV];
bool cut[MAXV];
int root;

inline void tarjan(int u){
	dfn[u]=low[u]=++tim;
	S[++top]=u;
	if(u==root&&!head[u]){
		vDcc[++vDcc_cnt].push_back(u);
		return;
	}
	reg int flag=0;
	for(reg int i=head[u];i;i=Next[i]){
		reg int v=to[i];
		if(!dfn[v]){
			tarjan(v);
			cMin(low[u],low[v]);
			if(dfn[u]<=low[v]){
				++flag;
				if(u!=root||flag>1)
					cut[u]=true;
				++vDcc_cnt;
				int tmp;
				do{
					tmp=S[top--];
					vDcc[vDcc_cnt].push_back(tmp);
				}while(tmp!=v);
				vDcc[vDcc_cnt].push_back(u);
			}
		}
		else
			cMin(low[u],dfn[v]);
	}
	return;
}

bool vis[MAXV];

inline void Init(void){
	cnt=0,memset(head,0,sizeof(head));
	tim=top=0,memset(dfn,0,sizeof(dfn));
	memset(cut,false,sizeof(cut));
	for(reg int i=1;i<=vDcc_cnt;++i)
		vDcc[i].clear();
	vDcc_cnt=0;
	memset(vis,false,sizeof(vis));
	return;
}

int main(void){
	reg int Case=0;
	while(scanf("%d",&n)!=EOF&&n!=0){
		Init();
		int Max=0;
		for(reg int i=1;i<=n;++i){
			static int s,t;
			scanf("%d%d",&s,&t);
			vis[s]=vis[t]=true;
			Add_Edge(s,t);
			Add_Edge(t,s);
			cMax(Max,s);
			cMax(Max,t);
		}
		n=Max;
		reg int ans1=0;
		reg ll ans2=1;
		for(root=1;root<=n;++root)
			if(!dfn[root]&&vis[root])
				tarjan(root);
			else if(!vis[root])
				++ans1;
		for(reg int i=1;i<=vDcc_cnt;++i){
			reg int sum=0,siz=vDcc[i].size();
			for(reg int j=0;j<siz;++j)
				sum+=cut[vDcc[i][j]];
			if(!sum)
				ans1+=2,ans2*=siz*(siz-1)/2;
			else if(sum==1)
				++ans1,ans2*=siz-1;
		}
		printf("Case %d: %d %lld\n",++Case,ans1,ans2);
	}
	return 0;
}