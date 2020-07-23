#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=1000+5;
const int MAXM=3000+5;
const int MAXP=10+1;

int n,m,p;
int cnt,head[MAXN],to[MAXM<<1],w[MAXM<<1],Next[MAXM<<1];
int f[MAXN][1<<MAXP],g[1<<MAXP];

inline void Add_Edge(reg int u,reg int v,reg int len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

bool inque[MAXN];
queue<int> Q;

inline void SPFA(reg int S){
	while(!Q.empty()){
		reg int id=Q.front();
		Q.pop();
		inque[id]=false;
		for(reg int i=head[id];i;i=Next[i]){
			int v=to[i];
			if(f[v][S]>f[id][S]+w[i]){
				f[v][S]=f[id][S]+w[i];
				if(!inque[v]){
					inque[v]=true;
					Q.push(v);
				}
			}
		}
	}
	return;
}

struct City{
	int c,d;
	inline void Read(void){
		c=read(),d=read();
		return;
	}
	inline bool operator<(const City& a)const{
		return c<a.c;
	}
};

vector<int> V;
City C[MAXP];

inline int Solve(reg int cnt){
	reg int U=(1<<cnt)-1;
	for(reg int S=1;S<=U;++S){
		for(int i=1;i<=n;++i){
			for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
				f[i][S]=min(f[i][S],f[i][sub]+f[i][S^sub]);
			if(f[i][S]!=INF){
				inque[i]=true;
				Q.push(i);
			}
		}
		SPFA(S);
	}
	int res=INF;
	for(reg int i=1;i<=n;++i)
		res=min(res,f[i][U]);
	return res;
}

int main(void){
	n=read(),m=read(),p=read();
	for(reg int i=1;i<=m;++i){
		static int u,v,w;
		u=read(),v=read(),w=read();
		Add_Edge(u,v,w);
		Add_Edge(v,u,w);
	}
	for(reg int i=1;i<=p;++i){
		C[i].Read();
		V.push_back(C[i].c);
	}
	sort(V.begin(),V.end());
	V.erase(unique(V.begin(),V.end()),V.end());
	for(reg int i=1;i<=p;++i)
		C[i].c=lower_bound(V.begin(),V.end(),C[i].c)-V.begin()+1;
	reg int U=(1<<V.size())-1;
	for(reg int S=1;S<=U;++S){
		memset(f,0X3F,sizeof(f));
		reg int cnt=0;
		for(reg int i=1;i<=p;++i)
			if((S>>(C[i].c-1))&1)
				f[C[i].d][1<<(cnt++)]=0;
		g[S]=Solve(cnt);
	}
	for(reg int S=1;S<=U;++S)
		for(reg int sub=S&(S-1);sub;sub=S&(sub-1))
			g[S]=min(g[S],g[S^sub]+g[sub]);
	printf("%d\n",g[U]);
	return 0;
}
