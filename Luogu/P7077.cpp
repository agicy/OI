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

const int MAXN=1e5+5;
const int MAXM=1e6+5;
const int mod=998244353;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

int n,m,Q;
int a[MAXN];
int t[MAXM],p[MAXM],v[MAXM];
vector<int> G[MAXM],invG[MAXM];
int cnt[MAXM],mul[MAXM];

inline void getMul(void){
	static int Q[MAXM],deg[MAXM];
	reg int head=0,tail=0;
	for(reg int i=0;i<=m;++i){
		deg[i]=G[i].size();
		if(!deg[i])
			Q[tail++]=i;
	}
	while(head<tail){
		reg int u=Q[head++];
		for(reg int i=0,siz=invG[u].size();i<siz;++i){
			reg int v=invG[u][i];
			mul[v]=1ll*mul[v]*mul[u]%mod;
			--deg[v];
			if(!deg[v])
				Q[tail++]=v;
		}
	}
	return;
}

inline void getCnt(void){
	static int Q[MAXM],deg[MAXM];
	reg int head=0,tail=0;
	for(reg int i=0;i<=m;++i){
		deg[i]=invG[i].size();
		if(!deg[i])
			Q[tail++]=i;
	}
	while(head<tail){
		reg int u=Q[head++];
		reg int pod=1;
		for(reg int i=G[u].size()-1;i>=0;--i){
			reg int v=G[u][i];
			cnt[v]=add(cnt[v],1ll*cnt[u]*pod%mod);
			pod=1ll*pod*mul[v]%mod;
			--deg[v];
			if(!deg[v])
				Q[tail++]=v;
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	m=read();
	for(int i=1;i<=m;++i){
		t[i]=read();
		switch(t[i]){
			case 1:{
				p[i]=read(),v[i]=read();
				mul[i]=1;
				break;
			}
			case 2:{
				mul[i]=read();
				break;
			}
			case 3:{
				mul[i]=1;
				reg int c=read();
				G[i].resize(c);
				for(reg int j=0;j<c;++j){
					static int g;
					g=read();
					G[i][j]=g;
					invG[g].push_back(i);
				}
				break;
			}
		}
	}
	Q=read();
	for(reg int i=1;i<=Q;++i){
		static int f;
		f=read();
		G[0].push_back(f);
		invG[f].push_back(0);
	}
	cnt[0]=mul[0]=1;
	getMul(),getCnt();
	for(reg int i=1;i<=n;++i)
		a[i]=1ll*a[i]*mul[0]%mod;
	for(reg int i=1;i<=m;++i)
		if(t[i]==1)
			a[p[i]]=add(a[p[i]],1ll*cnt[i]*v[i]%mod);
	for(reg int i=1;i<=n;++i)
		printf("%d%c",a[i],i==n?'\n':' ');
	return 0;
}