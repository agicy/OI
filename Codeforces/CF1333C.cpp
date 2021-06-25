#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch)) f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=100000+5;

int n;
map<ll,int> M;

int main(void){
	n=read();
	M[0]=1;
	int Max=0;
	ll sum=0;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		sum+=a;
		Max=max(Max,M[sum]);
		ans+=i-Max;
		M[sum]=i+1;
	}
	printf("%lld\n",ans);
	return 0;
}
