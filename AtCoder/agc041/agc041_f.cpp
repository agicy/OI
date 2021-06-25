#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=400+5;
const int MAXLOG2N=9+1;
const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
		assert(0<=x&&x<mod);
		return;
	}
	inline modInt operator+(const modInt& a)const{
		reg int sum=x+a.x;
		return sum>=mod?sum-mod:sum;
	}
	inline modInt operator-(const modInt& a)const{
		reg int sum=x-a.x;
		return sum<0?sum+mod:sum;
	}
	inline modInt operator-(void)const{
		return modInt(0)-*this;
	}
	inline modInt operator*(const modInt& a)const{
		return 1ll*x*a.x%mod;
	}
	inline void operator+=(const modInt& a){
		x+=a.x;
		if(x>=mod) x-=mod;
		return;
	}
	inline void operator-=(const modInt& a){
		x-=a.x;
		if(x<0) x+=mod;
		return;
	}
	inline void operator*=(const modInt& a){
		x=1ll*x*a.x%mod;
		return;
	}
};

inline modInt fpow(modInt x,reg int exp){
	modInt res=1;
	while(exp){
		if(exp&1)
			res*=x;
		x*=x,exp>>=1;
	}
	return res;
}

int n;
int h[MAXN];
modInt g[MAXN][MAXN][2];

inline void Init(reg int n){
	modInt bas=1;
	for(reg int i=0;i<=n;++i){
		g[i][0][0]=g[i][0][1]=1;
		for(reg int j=1;j<=n;++j){
			g[i][j][0]=g[i][j-1][0]*(bas-1);
			g[i][j][1]=g[i][j-1][1]*bas;
		}
		bas+=bas;
	}
	return;
}

vector<int> G[MAXN];
int siz[MAXN],len[MAXN];
modInt f[MAXN][MAXN][2];

inline void dfs(reg int u){
	if(!u)
		return;
	f[u][0][1]=1;
	for(int v:G[u]){
		dfs(v);
		static modInt tmp[MAXN][2];
		for(reg int i=0;i<=siz[u]+siz[v];++i)
			tmp[i][0].x=tmp[i][1].x=0;
		for(reg int i=0;i<=siz[u];++i)
			for(reg int j=0;j<=siz[v];++j){
				tmp[i+j][0]+=f[u][i][0]*f[v][j][0]+f[u][i][0]*f[v][j][1]+f[u][i][1]*f[v][j][0];
				tmp[i+j][1]+=f[u][i][1]*f[v][j][1];
			}
		for(reg int i=0;i<=siz[u]+siz[v];++i)
			f[u][i][0]=tmp[i][0],f[u][i][1]=tmp[i][1];
		siz[u]+=siz[v];
	}
	for(reg int i=0;i<=siz[u];++i){
		f[u][i][0]*=g[siz[u]-i][len[u]][0];
		f[u][i][1]*=g[siz[u]-i][len[u]][1];
	}
	return;
}

namespace ST{
	int lg[MAXN];
	int posMin[MAXLOG2N][MAXN];
	int *cmp;
	inline void Init(reg int n,reg int a[]){
		cmp=a;
		lg[0]=-1;
		for(reg int i=1;i<=n;++i){
			lg[i]=lg[i>>1]+1;
			posMin[0][i]=i;
		}
		for(reg int j=1;j<MAXLOG2N;++j)
			for(reg int i=1;i+(1<<j)-1<=n;++i){
				if(cmp[posMin[j-1][i]]<=cmp[posMin[j-1][i+(1<<(j-1))]])
					posMin[j][i]=posMin[j-1][i];
				else
					posMin[j][i]=posMin[j-1][i+(1<<(j-1))];
			}
		return;
	}
	inline int queryMinpos(reg int l,reg int r){
		reg int k=lg[r-l+1];
		if(cmp[posMin[k][l]]<=cmp[posMin[k][r-(1<<k)+1]])
			return posMin[k][l];
		else
			return posMin[k][r-(1<<k)+1];
	}
}

int tot;

inline int build(reg int l,reg int r,reg int las){
	reg int p=++tot;
	reg int Min=h[ST::queryMinpos(l,r)],ptr=l;
	len[p]=Min-las;
	while(ptr<=r){
		reg int nex=ST::queryMinpos(ptr,r);
		if(h[nex]!=Min)
			break;
		if(nex!=ptr)
			G[p].push_back(build(ptr,nex-1,Min));
		G[p].push_back(0);
		ptr=nex+1;
	}
	if(ptr<=r)
		G[p].push_back(build(ptr,r,Min));
	return p;
}

int main(void){
	n=read();
	Init(n);
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	ST::Init(n,h);
	siz[0]=1,f[0][1][1]=-modInt(1),f[0][0][1]=f[0][1][0]=modInt(1);
	reg int rt=build(1,n,0);
	dfs(rt);
	modInt ans=0;
	for(reg int i=0;i<=n;++i)
		ans+=f[rt][i][0]+f[rt][i][1];
	printf("%d\n",ans.x);
	return 0;
}