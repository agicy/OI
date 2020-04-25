#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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


const int MAXN=2000+5;
const int MAXM=800000+5;

int n,W,a[MAXN],rt[MAXN][2];

int cnt=1,head[MAXN<<5],to[MAXM<<1],w[MAXM<<1],p[MAXM<<1],Next[MAXM<<1];

inline void Add_Edge(reg int u,reg int v,reg int len,reg int val){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	p[cnt]=val;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg int len,reg int val){
	Add_Edge(u,v,len,val);
	Add_Edge(v,u,0,-val);
	return;
}

bool inque[MAXN<<5];
int dis[MAXN<<5];
queue<int> Q;

inline bool SPFA(int s,reg int t){
	memset(dis,0X3F,sizeof(dis));
    while(!Q.empty())Q.pop();
	inque[s]=true,dis[s]=0,Q.push(s);
	while(!Q.empty()){
		reg int ID=Q.front();
		Q.pop();
		inque[ID]=false;
		for(reg int i=head[ID];i;i=Next[i])
			if(dis[to[i]]>dis[ID]+p[i]&&w[i]>0){
				dis[to[i]]=dis[ID]+p[i];
				if(!inque[to[i]]){
					inque[to[i]]=true;
					Q.push(to[i]);
				}
			}
	}
	return dis[t]!=INF;
}

ll MinCost;
bool vis[MAXN<<5];
int cur[MAXN<<5];

inline int DFS(reg int ID,reg int t,reg int lim){
	if(ID==t){
		MinCost+=lim*dis[t];
		return lim;
	}
	vis[ID]=true;
	reg int flow=0;
	for(reg int &i=cur[ID];i;i=Next[i])
		if(dis[to[i]]==dis[ID]+p[i]&&w[i]>0&&!vis[to[i]]){
			reg int f=DFS(to[i],t,min(lim-flow,w[i]));
			if(f){
				flow+=f;
				w[i]-=f;
				w[i^1]+=f;
				if(flow==lim)
					break;
			}
		}
	vis[ID]=false;
	return flow;
}

inline int Dinic(reg int s,reg int t){
	reg int res=0;
	while(SPFA(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=DFS(s,t,INF);
	}
	return res;
}

vector<int> V;

namespace SegmentTree{
	#define mid ( ( (l) + (r) ) >> 1 )
	int tot,lson[MAXN<<5],rson[MAXN<<5],ID[MAXN<<5],id;
	inline void Build1(reg int &p,int pos,reg int l,reg int r,int pre,int to){
		p=++tot;
		lson[p]=lson[pre];
		rson[p]=rson[pre];
		ID[p]=++id;
		if(l==r){
			Add_Tube(ID[p],to,1,-V[l-1]);
			return;
		}
		if(pos<=mid)
			Build1(lson[p],pos,l,mid,lson[pre],to);
		else
			Build1(rson[p],pos,mid+1,r,rson[pre],to);
		if(lson[p])
			Add_Tube(ID[p],ID[lson[p]],INF,0);
		if(rson[p])
			Add_Tube(ID[p],ID[rson[p]],INF,0);
		return;
	}
	inline void Build2(reg int &p,int pos,int l,int r,int pre,int to){
		p=++tot;
		lson[p]=lson[pre];
		rson[p]=rson[pre];
		ID[p]=++id;
		if(l==r){
			Add_Tube(ID[p],to,1,V[l-1]);
			return;
		}
		if(pos<=mid)
			Build2(lson[p],pos,l,mid,lson[pre],to);
		else
			Build2(rson[p],pos,mid+1,r,rson[pre],to);
		if(lson[p])
			Add_Tube(ID[p],ID[lson[p]],INF,0);
		if(rson[p])
			Add_Tube(ID[p],ID[rson[p]],INF,0);
		return;
	}
	inline void Update1(int L,int R,int l,int r,int p,int from,int cost){
		if(!p)
			return;
		if(L<=l&&r<=R){
			Add_Tube(from,ID[p],1,cost);
			return;
		}
		if(L<=mid)
			Update1(L,R,l,mid,lson[p],from,cost);
		if(R>mid)
			Update1(L,R,mid+1,r,rson[p],from,cost);
		return;
	}
	inline void Update2(int L,int R,int l,int r,int p,int from,int cost){
		if(!p){
			return;
		}
		if(L<=l&&r<=R){
			Add_Tube(from,ID[p],1,-cost);
			return;
		}
		if(L<=mid)
			Update2(L,R,l,mid,lson[p],from,cost);
		if(R>mid)
			Update2(L,R,mid+1,r,rson[p],from,cost);
		return;
	}
	#undef mid
}

using namespace SegmentTree;

int main(void){
	n=read(),W=read();
	reg int s=n*2+1,t=s+1;
	id=s+1;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		V.push_back(a[i]);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=n;++i)
		a[i]=lower_bound(V.begin(),V.end(),a[i])-V.begin()+1;
	for(reg int i=1;i<=n;++i){
		Add_Tube(s,i+n,1,0);
		Add_Tube(i+n,t,1,W);
		Add_Tube(i,t,1,0);
	}
	for(reg int i=1;i<=n;++i){
		Build1(rt[i][0],a[i],1,V.size(),rt[i-1][0],i);
		Build2(rt[i][1],a[i],1,V.size(),rt[i-1][1],i);
	}
	for(reg int i=2;i<=n;++i){
		Update1(1,a[i],1,V.size(),rt[i-1][0],i+n,V[a[i]-1]);
		Update2(a[i]+1,V.size(),1,V.size(),rt[i-1][1],i+n,V[a[i]-1]);
	}
	Dinic(s,t);
	printf("%lld\n",MinCost);
	return 0;
}
