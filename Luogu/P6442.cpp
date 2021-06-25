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

const int MAXN=1e6+5;
const int MAXM=20;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n,m;
int bas[MAXN];
int f[1<<MAXM];

int main(void){
	n=read(),m=read();
	bas[0]=1;
	for(reg int i=1;i<=n;++i){
		bas[i]=add(bas[i-1],bas[i-1]);
		reg int cnt=read();
		reg int S=0;
		while(cnt--)
			S|=(1<<(read()-1));
		S=(~S)&((1<<m)-1);
		++f[S];
	}
	for(reg int i=0;i<m;++i)
		for(reg int S=(1<<m)-1;S>=0;--S)
			if(!((S>>i)&1))
				f[S]=add(f[S],f[S|(1<<i)]);
	reg int ans=0;
	for(reg int S=0;S<(1<<m);++S)
		if(__builtin_popcount(S)&1)
			ans=sub(ans,sub(bas[f[S]],1));
		else
			ans=add(ans,sub(bas[f[S]],1));
	printf("%d\n",ans);
	return 0;
}