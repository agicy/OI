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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

inline int min(reg int a,reg int b){
	return a<b?a:b;
}

const int MAXN=1e6+5;
const int MAXLOG2A=20;
const int mod=1e9+7;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

inline int sub(reg int a,reg int b){
	a-=b;
	return a<0?a+mod:a;
}

int n;
int bas[MAXN];
int f[1<<MAXLOG2A];

int main(void){
	n=read();
	bas[0]=1;
	for(reg int i=1;i<=n;++i)
		bas[i]=add(bas[i-1],bas[i-1]);
	reg int Maxb=1,Max=0;
	for(reg int i=1;i<=n;++i){
		reg int a=read();
		if(a)
			Maxb=max(Maxb,ceil(log2(a))+(__builtin_popcount(a)==1));
		++f[a];
		Max=max(Max,a);
	}
	for(reg int i=0;i<Maxb;++i)
		for(reg int S=Max;S>=0;--S)
			if(!((S>>i)&1))
				f[S]=add(f[S],f[S|(1<<i)]);
	reg int ans=0;
	for(reg int S=0;S<=Max;++S)
		if(__builtin_popcount(S)&1)
			ans=sub(ans,sub(bas[f[S]],1));
		else
			ans=add(ans,sub(bas[f[S]],1));
	printf("%d\n",ans);
	return 0;
}