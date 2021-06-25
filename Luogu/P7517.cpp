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

const int MAXN=2e5+5;
const int MAXA=5e5+5;

int n;
int a[MAXN];
int cnt[MAXA],T[MAXA];

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		++cnt[a[i]],Max=max(Max,a[i]);
	}
	for(reg int i=1;i<=Max;++i)
		for(reg int j=i;j<=Max;j+=i)
			T[i]+=cnt[j];
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=T[a[i]]-1;
	printf("%lld\n",ans);
	return 0;
}