#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=150+5;
const int MAXM=6000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,s,t;
int cnt=1,head[MAXN<<1],to[((MAXN<<1)+MAXM)<<1],w[((MAXN<<1)+MAXM)<<1],Next[((MAXN<<1)+MAXM)<<1];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0);
	return;
}

inline void Read(void){
	n=read(),m=read();
	s=0,t=2*n+1;
	for(reg int i=1;i<=m;++i){
		static int u,v;
		u=read(),v=read();
		Add_Tube(u,v+n,1);
	}
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i,1);
		Add_Tube(i+n,t,1);
	}
	return;
}

int dep[MAXN<<1];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i]){
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXN<<1];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i]){
		if(dep[to[i]]==dep[ID]+1&&w[i]>0){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	}
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(BFS(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

struct UnionFind{
	int ID[MAXN<<1];
	inline void Init(reg int size){
		for(reg int i=1;i<=size;++i)
			ID[i]=i;
		return;
	}
	inline int find(reg int x){
		if(x==ID[x])
			return x;
		else
			return ID[x]=find(ID[x]);
	}
	inline void merge(reg int a,reg int b){
		reg int ra=find(a),rb=find(b);
		if(ra!=rb)
			ID[rb]=ra;
		return;
	}
	inline bool search(reg int a,reg int b){
		return find(a)==find(b);
	}
};

stack<int> S;
UnionFind U;

inline void DFS(int ID){
	for(reg int i=head[ID];i;i=Next[i])
		if(w[i]==0&&to[i]>n)
			DFS(to[i]-n);
	S.push(ID);
	return;
}

inline void Work(void){
	reg int ans=Dinic(s,t);
	U.Init(n);
	for(reg int i=1;i<=n;++i)
		for(reg int j=head[i];j;j=Next[j])
			if(n<to[j]&&to[j]<=2*n&&w[j]==0)
				U.merge(i,to[j]-n);
	for(reg int i=1;i<=n;++i)
		if(U.find(i)==i){
			DFS(i);
			for(reg int i=1,size=S.size();i<=size;++i){
				printf("%d%c",S.top(),i==size?'\n':' ');
				S.pop();
			}
		}
	printf("%d\n",n-ans);
	return;
}
