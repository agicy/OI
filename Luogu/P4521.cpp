#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define MOD 1000000007
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=1000000+5;
const int MAXM=1000000+5;

int n,m,K;
ll line[MAXN],column[MAXM];

inline ll GetVal(reg ll i,reg ll j){
	return ((i-1)*m%MOD+j)%MOD;
}

int main(void){
	n=read(),m=read(),K=read();
	for(reg int i=1;i<=n;++i)
		line[i]=1;
	for(reg int i=1;i<=m;++i)
		column[i]=1;
	while(K--){
		static char ch;
		static int x,y;
		do
			ch=getchar();
		while(ch<'A'||'Z'<ch);
		x=read(),y=read();
		if(ch=='R')
			line[x]=(line[x]*y)%MOD;
		if(ch=='S')
			column[x]=(column[x]*y)%MOD;
	}
	reg ll sum=0,d=0,ans=0;
	for(reg int i=1;i<=n;++i){
		sum=(sum+(GetVal(i,1)*line[i]%MOD))%MOD;
		d=(d+line[i])%MOD;
	}
	for(reg int i=1;i<=m;++i){
		ans=(ans+sum*column[i])%MOD;
		sum=(sum+d)%MOD;
	}
	printf("%lld\n",ans);
	return 0;
}
