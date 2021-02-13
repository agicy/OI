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

inline void read(reg char *s){
	*s=getchar();
	while(!isdigit(*s))*s=getchar();
	while(isdigit(*s))*(++s)=getchar();
	*s='\0';
	return;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=20;
const int MAXM=1e5;
const int inf=0x3f3f3f3f;

namespace Poly{
	typedef vector<ll> poly;
	inline void FWT_xor(poly& a,reg int flag){
		reg int n=a.size();
		for(reg int i=1;i<n;i<<=1)
			for(reg int j=0;j<n;j+=(i<<1))
				for(reg int k=0;k<i;++k){
					reg ll x=a[j+k],y=a[i+j+k];
					a[j+k]=x+y,a[i+j+k]=x-y;
				}
		if(flag==-1)
			for(reg int i=0;i<n;++i)
				a[i]/=n;
		return;
	}
}

using namespace Poly;

int n,m;
int S[MAXM];
poly f,g;

int main(void){
	n=read(),m=read();
	for(reg int i=0;i<n;++i){
		static char str[MAXM+1];
		read(str);
		for(reg int j=0;j<m;++j)
			if(str[j]=='1')
				S[j]|=(1<<i);
	}
	f.resize(1<<n),g.resize(1<<n);
	for(reg int i=0;i<m;++i)
		++f[S[i]];
	for(reg int i=0;i<(1<<n);++i)
		g[i]=g[i>>1]+(i&1);
	for(reg int i=0;i<(1<<n);++i)
		g[i]=min(g[i],n-g[i]);
	FWT_xor(f,1),FWT_xor(g,1);
	for(reg int i=0;i<(1<<n);++i)
		f[i]*=g[i];
	FWT_xor(f,-1);
	reg int Min=inf;
	for(reg int i=0;i<(1<<n);++i)
		Min=min(Min,(int)f[i]);
	printf("%d\n",Min);
	return 0;
}