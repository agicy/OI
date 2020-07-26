#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X7FFFFFFF
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
const int MAXLOG2N=8+1;
const int MAXM=30000+5;

inline void Read(void);
inline void Work(void);

int main(void){
	reg int T=read();
	while(T--){
		Read();
		Work();
		putchar('\n');
	}
	return 0;
}

struct Graph{
	int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
	inline void Init(void){
		cnt=1;
		memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(reg int u,reg int v,reg int len){
		Next[++cnt]=head[u];
		to[cnt]=v;
		w[cnt]=len;
		head[u]=cnt;
	}
	inline void Add_Tube(reg int u,reg int v,reg int len){
		Add_Edge(u,v,len);
		Add_Edge(v,u,len);
		return;
	}
};

int n,m;
Graph G,T;

inline void Read(void){
	n=read(),m=read();
	G.Init();
	for(reg int i=1;i<=m;++i){
		static int u,v,c;
		u=read(),v=read(),c=read();
		G.Add_Tube(u,v,c);
	}
	return;
}

int dep[MAXN];
queue<int> Q;

inline bool BFS(int s,reg int t,Graph& G){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=G.head[ID];i;i=G.Next[i])
			if(dep[G.to[i]]==-1&&G.w[i]>0){
				dep[G.to[i]]=dep[ID]+1;
				Q.push(G.to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXN];

inline int DFS(reg int ID,reg int t,reg int lim,Graph& G){
	if(ID==t)
		return lim;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=G.Next[i])
		if(dep[G.to[i]]==dep[ID]+1&&G.w[i]>0){
			reg int f=DFS(G.to[i],t,min(lim-flow,G.w[i]),G);
			if(f){
				flow+=f;
				G.w[i]-=f;
				G.w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	return flow;
}

inline int Dinic(reg int s,reg int t,Graph& G){
	reg int res=0;
	while(BFS(s,t,G)){
		memcpy(cur,G.head,sizeof(G.head));
		res+=DFS(s,t,INF,G);
	}
	return res;
}

int W[MAXM<<1];
bool vis[MAXN];
int p[MAXN];

inline void DFS(reg int ID,Graph& G){
	vis[ID]=true;
	for(reg int i=G.head[ID];i;i=G.Next[i])
		if(!vis[G.to[i]]&&G.w[i]>0)
			DFS(G.to[i],G);
	return;
}

int fa[MAXN][MAXLOG2N];
int Min[MAXN][MAXLOG2N];

inline void DFS(reg int ID,reg int father,Graph& T){
	fa[ID][0]=father;
	dep[ID]=dep[father]+1;
	for(reg int i=1;i<MAXLOG2N;++i){
		fa[ID][i]=fa[fa[ID][i-1]][i-1];
		Min[ID][i]=min(Min[ID][i-1],Min[fa[ID][i-1]][i-1]);
	}
	for(reg int i=T.head[ID];i;i=T.Next[i])
		if(T.to[i]!=father){
			Min[T.to[i]][0]=T.w[i];
			DFS(T.to[i],ID,T);
		}
	return;
}

inline pair<int,int> LCA(int x,int y){
	if(dep[x]>dep[y])
		swap(x,y);
	int res_Min=INF;
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(dep[fa[y][i]]>=dep[x]){
			res_Min=min(res_Min,Min[y][i]);
			y=fa[y][i];
		}
	if(x==y)
		return make_pair(x,res_Min);
	for(reg int i=MAXLOG2N-1;i>=0;--i)
		if(fa[x][i]!=fa[y][i]){
			res_Min=min(res_Min,min(Min[x][i],Min[y][i]));
			x=fa[x][i],y=fa[y][i];
		}
	return make_pair(fa[x][0],min(res_Min,min(Min[x][0],Min[y][0])));
}

struct TreeArray{
	#define lowbit(x) ( (x) & ( - (x) ) )
	int n,unit[MAXM];
	inline void Init(reg int size){
		n=size;
		memset(unit,0,sizeof(unit));
		return;
	}
	inline void Update(reg int ID,reg int val){
		for(reg int i=ID;i<=n;i+=lowbit(i))
			unit[i]+=val;
		return;
	}
	inline int Query(reg int ID){
		reg int res=0;
		for(reg int i=ID;i;i-=lowbit(i))
			res+=unit[i];
		return res;
	}
	#undef lowbit
};

vector<int> V;
TreeArray TA;

inline void Work(void){
	V.push_back(0);
	for(reg int i=2;i<=G.cnt;++i){
		W[i]=G.w[i];
		V.push_back(W[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=2;i<=G.cnt;++i)
		W[i]=lower_bound(V.begin(),V.end(),W[i])-V.begin();
	T.Init();
	TA.Init(V.size());
	for(reg int i=2;i<=n;++i)
		p[i]=1;
	for(reg int i=2;i<=n;++i){
		reg int s=i,t=p[i];
		for(reg int j=1;j<=G.cnt;++j)
			G.w[j]=W[j];
		reg int ans=Dinic(s,t,G);
		memset(vis,false,sizeof(vis));
		DFS(s,G);
		T.Add_Tube(s,t,ans);
		for(reg int j=i;j<=n;++j)
			if(vis[j]&&p[j]==t)
				p[j]=s;
	}
	DFS(1,0,T);
	reg int zero=0;
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j){
			reg int cut=LCA(i,j).second;
			if(cut)
				TA.Update(cut,1);
			else
				++zero;
		}
	reg int q=read();
	while(q--){
		reg int ans;
		int x=read();
		x=upper_bound(V.begin(),V.end(),x)-V.begin();
		if(x!=0)
			ans=TA.Query(x-1)+zero;
		else
			ans=0;
		printf("%d\n",ans);
	}
	return;
}
