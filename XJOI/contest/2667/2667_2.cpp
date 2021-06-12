#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;

bool st;

#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline int lowbit(reg int x){
	return x&(-x);
}

inline int lg(reg int x){
	switch(x){
		case 1<<0:return 0;
		case 1<<1:return 1;
		case 1<<2:return 2;
		case 1<<3:return 3;
		case 1<<4:return 4;
		case 1<<5:return 5;
		case 1<<6:return 6;
		case 1<<7:return 7;
		case 1<<8:return 8;
		case 1<<9:return 9;
		case 1<<10:return 10;
		case 1<<11:return 11;
		case 1<<12:return 12;
		case 1<<13:return 13;
	}
	assert(false);
	return -1;
}

const int MAXN=13;
const double eps=1e-8;

inline void Gauss(reg int n,reg double G[MAXN][MAXN+1]){
	for(reg int i=n-1;i>=1;--i){
		reg double d=G[i-1][i]/G[i][i];
		G[i-1][0]-=d*G[i][0],G[i-1][i]-=d*G[i][i],G[i-1][n]-=d*G[i][n];
	}
	G[0][n]/=G[0][0],G[0][0]=1;
	for(reg int i=1;i<n;++i){
		G[i][n]-=G[i][0]*G[0][n];
		G[i][0]=0;
	}
	return;
}

int n;
double p[MAXN];
int nex[1<<MAXN][MAXN];
double f[1<<MAXN][MAXN][MAXN];
double G[MAXN][MAXN+1];
double ans[MAXN];

inline double getVal(reg int S,reg int i,reg int del){
	return f[S^(1<<del)][nex[S^(1<<del)][i]][i];
}

bool ed;

int main(void){
	for(reg int S=0;S<(1<<MAXN);++S){
		reg int tot=0;
		static int V[MAXN+1];
		for(reg int T=S;T;T^=lowbit(T))
			V[tot++]=lg(lowbit(T));
		V[tot]=V[0];
		for(reg int i=0;i<tot;++i)
			nex[S][V[i]]=V[i+1];
	}
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=0;i<n;++i)
			p[i]=read()/100.0;
		for(reg int i=0;i<n;++i)
			f[1<<i][i][i]=1;
		for(reg int S=0;S<(1<<n);++S){
			reg int siz=__builtin_popcount(S);
			if(siz<=1)
				continue;
			vector<int> V;
			V.reserve(siz);
			for(reg int Ts=S;Ts;Ts^=lowbit(Ts))
				V.push_back(lg(lowbit(Ts)));
			vector<int> ptr[siz];
			for(reg int i=0;i<siz;++i)
				for(int j=0;j<siz;++j)
					if(i!=j){
						if(ptr[i].empty()||getVal(S,V[i],V[j])-getVal(S,V[i],V[ptr[i].front()])>eps)
							ptr[i]={j};
						else if(fabs(getVal(S,V[i],V[j])-getVal(S,V[i],V[ptr[i].front()]))<eps)
							ptr[i].push_back(j);
					}
			for(int u:V){
				for(reg int i=0;i<siz;++i){
					reg int v=V[i];
					G[i][i]=1,G[i][(i+1)%siz]=-(1-p[v]);
					for(int del:ptr[i]){
						reg int nS=S^(1<<V[del]),nxt=nex[nS][v];
						G[i][siz]+=f[nS][nxt][u];
					}
					G[i][siz]=G[i][siz]*p[v]/ptr[i].size();
				}
				Gauss(siz,G);
				for(reg int i=0;i<siz;++i)
					f[S][V[i]][u]=G[i][siz],G[i][siz]=0;
			}
		}
		for(reg int i=0;i<n;++i)
			ans[i]=fabs(100.0*f[(1<<n)-1][0][i]);
		for(reg int i=0;i<n;++i)
			printf("%.2lf%c",ans[i],i==n-1?'\n':' ');
	}
	fprintf(stderr,"%.3lf s\n",1.0*clock()/CLOCKS_PER_SEC);
	fprintf(stderr,"%.3lf MiB\n",(&ed-&st)/1048576.0);
	return 0;
}