#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define INF 0X3F3F3F3F
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=100+5;
const int MAXM=100+5;
const int MAXSIZE=MAXN*MAXM;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

int n,m,s,t;
char M[MAXN][MAXM];
int cnt=1,head[MAXSIZE],to[MAXSIZE*8],w[MAXSIZE*8],Next[MAXSIZE*8];

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
	n=read(),m=read(),s=0,t=n*m+1;
    for(reg int i=1;i<=n;++i)
    	scanf("%s",M[i]+1);
	return;
}

int dep[MAXSIZE];
queue<int> Q;

inline bool BFS(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	while(!Q.empty())Q.pop();
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		for(reg int i=head[ID];i;i=Next[i])
			if(dep[to[i]]==-1&&w[i]>0){
				dep[to[i]]=dep[ID]+1;
				Q.push(to[i]);
			}
	}
	return dep[t]!=-1;
}

int cur[MAXSIZE];

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

inline int GetID(reg int i,reg int j){
	return (i-1)*m+j;
}

int tot;
bool bel[MAXSIZE];
bool vis[MAXSIZE];
bool ans[MAXSIZE];

inline void GetAns(reg int ID,reg bool lim){
	if(vis[ID])
		return;
	vis[ID]=true;
	if(bel[ID]==lim){
		++tot;
		ans[ID]=true;
	}
	for(reg int i=head[ID];i;i=Next[i])
		if((bool)w[i]==lim)
			GetAns(to[i],lim);
	return;
}

inline void Work(void){
	const int dx[]={-1,0,0,1};
	const int dy[]={0,-1,1,0};
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j){
			reg int now=GetID(i,j);
			if(((i^j)&1)&&M[i][j]!='#'){
				bel[now]=true;
				Add_Tube(s,now,1);
				for(reg int k=0;k<4;++k){
					reg int fx=i+dx[k],fy=j+dy[k];
					if(1<=fx&&fx<=n&&1<=fy&&fy<=m&&M[fx][fy]!='#')
						Add_Tube(now,GetID(fx,fy),1);
				}
			}
			else if(!((i^j)&1)&&M[i][j]!='#')
				Add_Tube(now,t,1);
		}
	Dinic(s,t);
	GetAns(s,1);
	memset(vis,false,sizeof(vis));
	GetAns(t,0);
	vector<pair<int,int>/**/> V;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=m;++j)
			if(ans[GetID(i,j)])
				V.push_back(make_pair(i,j));
	printf("%d\n",(int)V.size());
	for(reg int i=0;i<(int)V.size();++i)
		printf("%d %d\n",V[i].first,V[i].second);
	return;
}
