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

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=500+5;
const int MAXH=1e6+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int fpow(reg int x,reg int exp){
	reg int res=1;
	while(exp){
		if(exp&1)
			res=1ll*res*x%p;
		x=1ll*x*x%p;
		exp>>=1;
	}
	return res;
}

struct Node{
	int ch[2],siz;
	#define ch(x) unit[(x)].ch
	#define siz(x) unit[(x)].siz
};
#define lson(x) ch(x)[0]
#define rson(x) ch(x)[1]

int n,k;
int h[MAXN];
int fac[MAXH],invfac[MAXH];
Node unit[MAXN];
int f[MAXN][MAXN];

inline int binom(reg int n,reg int m){
	if(n<0||m>n)
		return 0;
	else
		return 1ll*fac[n]*invfac[m]%p*invfac[n-m]%p;
}

inline int getCnt(reg int n,reg int m,reg int k){
	return 1ll*binom(n,k)*binom(m,k)%p*fac[k]%p;
}

inline void dfs(reg int u,reg int H){
	f[u][0]=1;
	siz(u)=1;
	if(lson(u)){
		reg int v=lson(u);
		dfs(v,h[u]);
		siz(u)+=siz(v);
		for(reg int i=min(siz(u),k);i>=0;--i)
			for(reg int j=1;j<=min(siz(v),i);++j)
				f[u][i]=add(f[u][i],1ll*f[u][i-j]*f[v][j]%p)%p;
	}
	if(rson(u)){
		reg int v=rson(u);
		dfs(v,h[u]);
		siz(u)+=siz(v);
		for(reg int i=min(siz(u),k);i>=0;--i)
			for(reg int j=1;j<=min(siz(v),i);++j)
				f[u][i]=add(f[u][i],1ll*f[u][i-j]*f[v][j]%p)%p;
	}
	for(reg int i=min(siz(u),k);i>=0;--i)
		for(reg int j=1;j<=min(h[u]-H,i);++j)
			f[u][i]=add(f[u][i],1ll*f[u][i-j]*getCnt(h[u]-H,siz(u)-(i-j),j)%p);
	return;
}

int main(void){
	fac[0]=1;
	for(reg int i=1;i<MAXH;++i)
		fac[i]=1ll*fac[i-1]*i%p;
	invfac[MAXH-1]=fpow(fac[MAXH-1],p-2);
	for(reg int i=MAXH-2;i>=0;--i)
		invfac[i]=1ll*invfac[i+1]*(i+1)%p;
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		h[i]=read();
	reg int top=0;
	static int S[MAXN];
	for(reg int i=1;i<=n;++i){
		reg int tmp=top;
		while(tmp&&h[S[tmp]]>h[i])
			--tmp;
		if(tmp)
			rson(S[tmp])=i;
		if(tmp<top)
			lson(i)=S[tmp+1];
		S[++tmp]=i;
		top=tmp;
	}
	dfs(S[1],0);
	printf("%d\n",f[S[1]][k]);
	return 0;
}