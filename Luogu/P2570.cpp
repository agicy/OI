#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=30+5;
const int MAXM=30+5;
const double eps=1e-6;
const double inf=1e9;
const int MAXV=2*MAXN*MAXM+MAXN;
const int MAXE=2*(MAXN+2*MAXN*MAXN*MAXM+2*MAXN*MAXM);

int n,m;
int sum;
int p[MAXN],r[MAXN],d[MAXN];
int s[MAXM];
int S,T;

int cnt,head[MAXV],to[MAXE],Next[MAXE];
double w[MAXE];

inline void Add_Edge(reg int u,reg int v,reg double len){
	Next[++cnt]=head[u];
	to[cnt]=v;
	w[cnt]=len;
	head[u]=cnt;
	return;
}

inline void Add_Tube(reg int u,reg int v,reg double len){
	Add_Edge(u,v,len);
	Add_Edge(v,u,0.0);
	return;
}

int dep[MAXV];
queue<int> Q;

inline bool bfs(int s,reg int t){
	memset(dep,-1,sizeof(dep));
	dep[s]=1,Q.push(s);
	while(!Q.empty()){
		reg int u=Q.front();
		Q.pop();
		for(reg int i=head[u];i;i=Next[i]){
			int v=to[i];
			if(dep[v]==-1&&w[i]>eps){
				dep[v]=dep[u]+1;
				Q.push(v);
			}
		}
	}
	return dep[t]!=-1;
}

int cur[MAXV];

inline double dfs(reg int u,reg int t,reg double lim){
	if(u==t)
		return lim;
	reg double flow=0;
	for(reg int &i=cur[u];i;i=Next[i]){
		reg int v=to[i];
		if(dep[v]==dep[u]+1&&w[i]>eps){
			reg double f=dfs(v,t,min(lim-flow,w[i]));
			if(f>eps){
				flow+=f;
				w[i]-=f,w[i^1]+=f;
				if(fabs(flow-lim)<eps)
					break;
			}
		}
	}
	return flow;
}

inline double dinic(reg int s,reg int t){
	reg double res=0;
	while(bfs(s,t)){
		memcpy(cur,head,sizeof(head));
		res+=dfs(s,t,inf);
	}
	return res;
}

vector<double> V;

inline bool check(reg double t){
	cnt=1,memset(head,0,sizeof(head));
	V.clear();
	for(reg int i=1;i<=n;++i){
		Add_Tube(S,i,p[i]);
		V.push_back(r[i]),V.push_back(t+d[i]);
	}
	sort(V.begin(),V.end());
	reg int id=n;
	for(reg int i=1;i<=m;++i)
		for(reg int j=1,siz=V.size();j<siz;++j){
			if(V[j]-V[j-1]<eps)
				continue;
			++id;
			Add_Tube(id,T,(V[j]-V[j-1])*s[i]*i);
			for(reg int k=1;k<=n;++k)
				if((r[k]-V[j-1])<eps&&t+d[k]-V[j]>-eps)
					Add_Tube(k,id,s[i]*(V[j]-V[j-1]));
		}
	return fabs(sum-dinic(S,T))<eps;
}

inline double Solve(void){
	reg double l=0,r=sum,mid;
	while(r-l>eps){
		mid=0.5*(l+r);
		if(check(mid))
			r=mid;
		else
			l=mid;
	}
	return l;
}

int main(void){
	reg int k=read();
	while(k--){
		n=read(),m=read();
		sum=0,S=0,T=2*n*m+n+1;
		for(reg int i=1;i<=n;++i){
			p[i]=read(),r[i]=read(),d[i]=read();
			sum+=p[i];
		}
		for(reg int i=1;i<=m;++i)
			s[i]=read();
		sort(s+1,s+m+1);
		for(reg int i=m;i>=1;--i)
			s[i]-=s[i-1];
		reverse(s+1,s+m+1);
		printf("%.5lf\n",Solve());
	}
	return 0;
}