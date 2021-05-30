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

const int mod=998244353;

struct modInt{
	int x;
	inline modInt(reg int x=0):x(x){
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
		x*=x;
		exp>>=1;
	}
	return res;
}

const int MAXN=1e5+5;

int n;
vector<int> G[MAXN];
modInt f[MAXN][2];

inline void dfs(reg int u,reg int father){
	f[u][0]=f[u][1]=1;
	for(int v:G[u])
		if(v!=father){
			dfs(v,u);
			modInt tmp[2]={f[u][0],f[u][1]};
			f[u][0]=tmp[0]*f[v][0]*2+tmp[0]*f[v][1]+tmp[1]*f[v][0];
			f[u][1]=tmp[1]*f[v][0]+tmp[1]*f[v][1];
		}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<n;++i){
		static int a,b;
		a=read(),b=read();
		G[a].push_back(b),G[b].push_back(a);
	}
	dfs(1,0);
	printf("%d\n",(fpow(2,2*n-1)-f[1][0]).x);
	return 0;
}