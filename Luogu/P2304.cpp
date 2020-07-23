#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
//#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=50000+5;

struct Node{
	int id,x,y,b1,b2;
	inline void Read(reg int i){
		id=i;
		x=read(),y=read();
		b1=y+x;
		b2=y-x;
		return;
	}
	inline bool operator<(const Node& a)const{
		return (y>a.y)||(y==a.y&&x<a.x);
	}
};

int n;
Node a[MAXN];
vector<int> Vx,Vy,Vb1,Vb2;

inline void GetVector(vector<int>& V){
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	return;
}

inline void GetVal(Node &a){
	a.x=lower_bound(Vx.begin(),Vx.end(),a.x)-Vx.begin()+1;
	a.y=lower_bound(Vy.begin(),Vy.end(),a.y)-Vy.begin()+1;
	a.b1=lower_bound(Vb1.begin(),Vb1.end(),a.b1)-Vb1.begin()+1;
	a.b2=lower_bound(Vb2.begin(),Vb2.end(),a.b2)-Vb2.begin()+1;
	return;
}

int T[MAXN],Tb1[MAXN],Tb2[MAXN];
int up[MAXN],lu[MAXN],ru[MAXN];
vector<int> F[MAXN];

inline void Init(void){
	GetVector(Vx),GetVector(Vy),GetVector(Vb1),GetVector(Vb2);
	for(reg int i=1;i<=n;++i)
		GetVal(a[i]);
	sort(a+1,a+n+1);
	for(reg int i=1;i<=n;++i){
		up[i]=T[a[i].x];
		lu[i]=Tb1[a[i].b1];
		ru[i]=Tb2[a[i].b2];
		T[a[i].x]=Tb1[a[i].b1]=Tb2[a[i].b2]=i;
	}
	for(reg int i=1;i<=n;++i)
		F[a[i].y].push_back(i);
	return;
}

inline void Insert(const Node& a){
	Vx.push_back(a.x);
	Vy.push_back(a.y);
	Vb1.push_back(a.b1);
	Vb2.push_back(a.b2);
	return;
}

inline void Read(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i].Read(i);
		Insert(a[i]);
	}
	a[++n].id=0;
	Insert(a[n]);
	return;
}

namespace Solve1{
	int f[MAXN],gup[MAXN],bup[MAXN];
	int bj[MAXN];
	int cnt,path[MAXN];
	int rnk[MAXN];
	inline void Print(reg int k){
		path[++cnt]=a[k].id;
		reg int next=bj[k];
		reg int size=F[a[k].y].size();
		if(a[next].x<a[k].x){
			for(reg int i=rnk[k]+1;i<size;++i){
				reg int u=F[a[k].y][i];
				path[++cnt]=a[u].id;
			}
			for(reg int i=rnk[k]-1;i>=rnk[next];--i){
				reg int u=F[a[k].y][i];
				path[++cnt]=a[u].id;
			}
		}
		if(a[next].x>a[k].x){
			for(reg int i=rnk[k]-1;i>=0;--i){
				reg int u=F[a[k].y][i];
				path[++cnt]=a[u].id;
			}
			for(reg int i=rnk[k]+1;i<=rnk[next];++i){
				reg int u=F[a[k].y][i];
				path[++cnt]=a[u].id;
			}
		}
		if(bup[next])
			Print(bup[next]);
		return;
	}
	inline void Solve(void){
		reg int Max,ptr;
		for(reg int i=Vy.size();i>=1;--i){
			reg int size=F[i].size();
			Max=ptr=0;
			for(reg int j=0;j<size;++j){
				reg int u=F[i][j];
				rnk[u]=j;
				if(up[u]&&f[up[u]]>gup[u]){
					gup[u]=f[up[u]];
					bup[u]=up[u];
				}
				if(lu[u]&&f[lu[u]]>gup[u]){
					gup[u]=f[lu[u]];
					bup[u]=lu[u];
				}
				if(ru[u]&&f[ru[u]]>gup[u]){
					gup[u]=f[ru[u]];
					bup[u]=ru[u];
				}
				f[u]=Max,bj[u]=ptr;
				if(size-j+gup[u]>Max)
					Max=size-j+gup[u],ptr=u;
			}
			Max=ptr=0;
			for(reg int j=size-1;j>=0;--j){
				reg int u=F[i][j];
				if(Max>f[u])
					f[u]=Max,bj[u]=ptr;
				if(gup[u]+1>f[u])
					f[u]=gup[u]+1,bj[u]=u;
				if(j+1+gup[u]>Max)
					Max=i+1+gup[u],ptr=u;
			}
		}
		printf("%d\n",f[n]-1);
		Print(n);
		for(reg int i=2;i<=cnt;++i)
			printf("%d%c",path[i],i==cnt?'\n':' ');
		return;
	}
}

namespace Solve2{
	int cnt=1,head[MAXV],to[MAXE],w[MAXE],Next[MAXE];
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
	int dep[MAXV];
	queue<int> Q;
	inline bool BFS(int s,reg int t){
		memset(dep,-1,sizeof(dep));
		while(!Q.empty())Q.pop();
		dep[s]=1,Q.push(s);
		while(!Q.empty()){
			reg int u=Q.front();
			Q.pop();
			for(reg int i=head[u];i;i=Next[i]){
				int v=to[i];
				if(dep[v]==-1&&w[i]>0){
					dep[v]=dep[u]+1;
					Q.push(v);
				}
			}
		}
		return dep[t]!=-1;
	}
	int cur[MAXV];
	inline int DFS(reg int u,reg int t,reg int lim){
		if(u==t)
			return lim;
		reg int flow=0;
		for(reg int &i=cur[u];i;i=Next[i]){
			reg int v=to[i];
			if(dep[v]==dep[u]+w[i]&&w[i]>0){
				reg int f=DFS(v,t,min(lim-flow,w[i]));
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
			res+=DFS(s,t);
		}
		return res;
	}
	inline void Calc(void){
		return;
	}
	inline void Build(void){
		return;
	}
	inline void Solve(void){
		Build();
		return;
	}
}

int main(void){
	Read();
	Init();
	Solve1::Solve();
	Solve2::Solve();
	return 0;
}
