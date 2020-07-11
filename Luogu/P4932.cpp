#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

int n,a,b,c,d;
int cnt[1<<16];
ll x0,x1;
ll ans[2];

int main(void){
	cnt[0]=0,cnt[1]=1;
	for(reg int i=2;i<(1<<16);++i)
		cnt[i]=cnt[i>>1]+(i&1);
	n=read(),a=read(),b=read(),c=read(),d=read(),x0=read();
	for(reg int i=1;i<=n;++i){
		x1=(a*x0%d*x0%d+b*x0%d+c)%d;
		reg int temp=cnt[x1>>16]+cnt[x1&((1<<16)-1)];
		++ans[temp&1];
		x0=x1;
	}
	printf("%lld\n",ans[0]*ans[1]);
	return 0;
}
