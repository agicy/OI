#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
#define flush() (fwrite(wbuf,1,wp1,stdout),wp1=0)
#define putchar(c) (wp1==wp2&&(flush(),0),wbuf[wp1++]=c)
static char wbuf[1<<21];int wp1;const int wp2=1<<21;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline void writeln(reg int x){
	static char buf[32];
	reg int p=-1;
	if(x==0)
		putchar('0');
	else
		while(x)
			buf[++p]=(x%10)^'0',x/=10;
	while(~p)
		putchar(buf[p--]);
	putchar('\n');
	return;
}

const int MAXN=3e3+5;
const int p=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=p?a-p:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+p:a;
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

typedef vector<int> poly;

inline poly operator+(poly a,const poly& b){
	a.resize(max(a.size(),b.size()),0);
	for(reg int i=b.size()-1;i>=0;--i)
		a[i]=add(a[i],b[i]);
	return a;
}

inline poly operator-(poly a,const poly& b){
	for(reg int i=b.size()-1;i>=0;--i)
		a[i]=sub(a[i],b[i]);
	while(!a.back())
		a.pop_back();
	return a;
}

inline poly operator*(const poly& a,const poly& b){
	poly res;
	res.resize(a.size()+b.size()-1,0);
	for(reg int i=a.size()-1,j;i>=0;--i)
		for(j=b.size()-1;j>=0;--j)
			res[i+j]=add(res[i+j],1ll*a[i]*b[j]%p);
	return res;
}

inline poly operator/(poly a,const poly& b){
	poly res;
	res.resize(a.size()-b.size()+1,0);
	reg int inv=fpow(b.back(),p-2);
	for(reg int i=res.size()-1,j;i>=0;--i){
		res[i]=1ll*inv*a[i+b.size()-1]%p;
		for(j=b.size()-1;j>=0;--j)
			a[i+j]=sub(a[i+j],1ll*res[i]*b[j]%p);
	}
	return res;
}

int n;
int w[MAXN];
int cnt,head[MAXN],to[MAXN<<1],Next[MAXN<<1];

inline void Add_Edge(reg int u,reg int v){
	Next[++cnt]=head[u];
	to[cnt]=v;
	head[u]=cnt;
	return;
}

poly f[MAXN];
poly mul[MAXN],sum[MAXN];

inline void dfs1(reg int u,reg int father){
	mul[u].resize(2,0);
	mul[u][1]=w[u];
	for(reg int i=head[u],v;i;i=Next[i]){
		v=to[i];
		if(v!=father){
			dfs1(v,u);
			mul[u]=mul[u]*f[v],sum[u]=sum[u]+f[v];
		}
	}
	f[u]=mul[u]+sum[u],f[u][0]=1;
	return;
}

int ans[MAXN][MAXN];

inline void dfs2(reg int u,reg int father){
	mul[u]=mul[u]*f[father],sum[u]=sum[u]+f[father];
	f[u]=mul[u]+sum[u],f[u][0]=1;
	for(reg int i=f[u].size()-1;i;--i){
		ans[u][i]=f[u][i];
		ans[u][0]=add(ans[u][0],ans[u][i]);
	}
	for(reg int i=head[u],v;i;i=Next[i]){
		v=to[i];
		if(v!=father){
			f[u]=(mul[u]/f[v])+(sum[u]-f[v]),f[u][0]=1;
			dfs2(v,u);
		}
	}
	return;
}

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1,u,v;i<n;++i){
		u=read(),v=read();
		Add_Edge(u,v),Add_Edge(v,u);
	}
	f[0].resize(1),f[0][0]=1;
	dfs1(1,0),dfs2(1,0);
	reg int q=read(),u,x;
	while(q--){
		u=read(),x=read();
		writeln(ans[u][x]);
	}
	flush();
	return 0;
}