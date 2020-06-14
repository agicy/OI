#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool fa=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)fa|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return fa?-res:res;
}

const int MAXN=100000+5;
const int MAXM=50000+5;

int n,m;
int inDeg[MAXN];
vector<int> V[MAXM],G[MAXN];
priority_queue<int,vector<int>,greater<int>/**/> Q;

inline void ReBuild(reg int mid){
	memset(inDeg,0,sizeof(inDeg));
	for(reg int i=1;i<=n;++i)
		G[i].clear();
	while(!Q.empty())Q.pop();
	int u,v;
	for(reg int i=1;i<=mid;++i)
		for(reg int j=0,size=V[i].size();j<size-1;++j){
			u=V[i][j],v=V[i][j+1];
			G[u].push_back(v);
			++inDeg[v];
		}
	return;
}

inline bool Topo(reg int mid){
	ReBuild(mid);
	for(int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i);
	reg int cnt=0,ID;
	int to;
	while(!Q.empty()){
		ID=Q.top();
		Q.pop();
		++cnt;
		for(reg int i=0,size=G[ID].size();i<size;++i){
			to=G[ID][i];
			--inDeg[to];
			if(!inDeg[to])
				Q.push(to);
		}
	}
	return cnt==n;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=m;++i){
		static int mi;
		mi=read();
		for(reg int j=1;j<=mi;++j){
			static int s;
			s=read();
			V[i].push_back(s);
		}
	}
	reg int l=0,r=m,mid,ans=0;
	while(l<=r){
		mid=(l+r)>>1;
		if(Topo(mid)){
			l=mid+1;
			ans=mid;
		}
		else
			r=mid-1;
	}
	ReBuild(ans);
	for(int i=1;i<=n;++i)
		if(!inDeg[i])
			Q.push(i);
	reg int ID;
	int to;
	while(!Q.empty()){
		ID=Q.top();
		Q.pop();
		printf("%d ",ID);
		for(reg int i=0,size=G[ID].size();i<size;++i){
			to=G[ID][i];
			--inDeg[to];
			if(!inDeg[to])
				Q.push(to);
		}
	}
	return 0;
}