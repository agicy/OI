#include<bits/stdc++.h>
using namespace std;
#define reg register
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100000+5;
const int MAXM=100000+5;

inline void Init(void);
inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Init();
		Read();
		Work();
	}
	return 0;
}

int n,m;
int ans[MAXM];
vector<int> G[MAXN];
vector<pair<int,int>/**/> q[MAXN];

inline void Read(void){
	n=read(),m=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		G[a].push_back(b);
		G[b].push_back(a);
	}
	for(int i=1;i<=m;++i){
		static int x,k;
		x=read(),k=read();
		if(k==0)
			ans[i]=1;
		else{
			q[x].push_back(make_pair(i,k));
			ans[i]=0;
		}
	}
	return;
}

int tot,Min;
int root;
int size[MAXN];
bool vis[MAXN];

inline void find(reg int ID,reg int father){
	int Max=0;
	size[ID]=1;
	for(reg int i=0,S=G[ID].size();i<S;++i){
		reg int to=G[ID][i];
		if(to!=father&&!vis[to]){
			find(to,ID);
			size[ID]+=size[to];
			Max=max(Max,size[to]);
		}
	}
	Max=max(Max,tot-size[ID]);
	if(Max<Min){
		root=ID;
		Min=Max;
	}
	return;
}

int T[MAXN];

inline void Query(reg int ID,reg int father,reg int dep){
	for(reg int i=0,size=q[ID].size();i<size;++i){
		if(q[ID][i].second>=dep)
			ans[q[ID][i].first]+=T[q[ID][i].second-dep];
	}
	for(reg int i=0,size=G[ID].size();i<size;++i){
		reg int to=G[ID][i];
		if(to!=father&&!vis[to])
			Query(to,ID,dep+1);
	}
	return;
}

int top,S[MAXN];

inline void Update(reg int ID,reg int father,reg int dep){
	++T[dep],S[++top]=dep;
	for(reg int i=0,size=G[ID].size();i<size;++i){
		reg int to=G[ID][i];
		if(!vis[to]&&to!=father)
			Update(to,ID,dep+1);
	}
	return;
}

inline void Solve(reg int ID){
	vis[ID]=true;
	++T[0];
	S[++top]=0;
	for(reg int i=0,size=G[ID].size();i<size;++i){
		reg int to=G[ID][i];
		if(!vis[to]){
			Query(to,0,1);
			Update(to,0,1);
		}
	}
	while(top)
		T[S[top--]]=0;
	reverse(G[ID].begin(),G[ID].end());
	for(reg int i=0,size=G[ID].size();i<size;++i){
		reg int to=G[ID][i];
		if(!vis[to]){
			Query(to,0,1);
			Update(to,0,1);
		}
	}
	for(reg int i=0,size=q[ID].size();i<size;++i){
		ans[q[ID][i].first]+=T[q[ID][i].second];
	}
	while(top)
		T[S[top--]]=0;
	for(reg int i=0,S=G[ID].size();i<S;++i){
		reg int to=G[ID][i];
		if(!vis[to]){
			tot=size[to],Min=INF;
			find(to,0);
			Solve(root);
		}
	}
	return;
}

inline void Work(void){
	tot=n,Min=INF;
	find(1,0);
	Solve(root);
	for(reg int i=1;i<=m;++i)
		printf("%d%c",ans[i],i==m?'\n':' ');
	return;
}

inline void Init(void){
	for(reg int i=1;i<=n;++i)
		G[i].clear(),q[i].clear(),vis[i]=false;
	return;
}