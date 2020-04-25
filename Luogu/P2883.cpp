#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=5000+5;
const int MAXM=50000+5;

struct Graph{
	int n;
	int cnt,head[MAXN],to[MAXM],Next[MAXM];
	int inDeg[MAXN];
	int f[MAXN];
	inline void Init(reg int size){
		n=size;
		cnt=0;
		memset(head,0,sizeof(head));
		return;
	}
	inline void Add_Edge(reg int u,reg int v){
		++inDeg[v];
		Next[++cnt]=head[u];
		to[cnt]=v;
		head[u]=cnt;
		return;
	}
	inline void Topo(void){
		reg int ID;
		queue<int> Q;
		for(reg int i=1;i<=n;++i)
			if(!inDeg[i])
				Q.push((int)i),f[i]=1;
		while(!Q.empty()){
			ID=Q.front();
			Q.pop();
			for(reg int i=head[ID];i;i=Next[i]){
				f[to[i]]+=f[ID];
				--inDeg[to[i]];
				if(!inDeg[to[i]])
					Q.push(to[i]);
			}
		}
		return;
	}
};

int n,m;
int u[MAXM],v[MAXM];
Graph G1,G2;

inline void Read(void);
inline void Work(void);

int main(void){
	Read();
	Work();
	return 0;
}

inline void Read(void){
	n=read(),m=read();
	G1.Init(n),G2.Init(n);
	for(reg int i=1;i<=m;++i){
		u[i]=read(),v[i]=read();
		G1.Add_Edge(u[i],v[i]);
		G2.Add_Edge(v[i],u[i]);
	}
	return;
}

inline void Work(void){
	int ans=0;
	G1.Topo(),G2.Topo();
	for(reg int i=1;i<=m;++i)
		ans=max(ans,G1.f[u[i]]*G2.f[v[i]]);
	printf("%d\n",ans);
	return;
}