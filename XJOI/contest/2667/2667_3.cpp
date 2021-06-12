#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=128+5;

int n;
bool G[MAXN][MAXN];
unsigned int ans;

inline void dfs(vector<int> bas,vector<int> p,vector<int> n){
	if(ans>1000u)
		return;
	if(!p.size()){
		if(!n.size())
			++ans;
		return;
	}
	reg int pivot=p[0];
	for(reg int i=0,siz=p.size();i<siz;++i){
		int v=p[i];
		if(G[pivot][v])
			continue;
		vector<int> np,nn;
		for(reg int j=0;j<i;++j)
			if(G[pivot][p[j]]&&G[v][p[j]])
				np.push_back(p[j]);
		for(reg int j=i+1;j<siz;++j)
			if(G[v][p[j]])
				np.push_back(p[j]);
		for(int x:n)
			if(G[v][x])
				nn.push_back(x);
		vector<int> nbas=bas;
		nbas.push_back(v);
		dfs(nbas,np,nn);
		if(ans>1000u)
			return;
		n.push_back(v);
	}
	return;
}

int main(void){
	reg int t=read();
	while(t--){
		reg int n=read();
		for(reg int i=0;i<n;++i)
			for(reg int j=0;j<n;++j)
				G[i][j]=false;
		reg int m=read();
		for(reg int i=0;i<m;++i){
			static int x,y;
			x=read()-1,y=read()-1;
			G[x][y]=G[y][x]=true;
		}
		vector<int> U;
		U.resize(n);
		for(reg int i=0;i<n;++i)
			U[i]=i;
		ans=0;
		dfs(vector<int>{},U,vector<int>{});
		if(ans>1000u)
			puts("Too many maximal sets of friends.");
		else
			printf("%u\n",ans);
	}
	return 0;
}