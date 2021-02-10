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

const int MAXS=1e5+5;

ll f[MAXS];

int main(void){
	static int c[4];
	for(reg int i=0;i<4;++i)
		c[i]=read();
	f[0]=1;
	for(reg int j=0;j<4;++j)
		for(reg int i=1;i<=1e5;++i)
			if(i>=c[j])
				f[i]+=f[i-c[j]];
	reg int n=read();
	while(n--){
		static int d[4],s;
		for(reg int i=0;i<4;++i)
			d[i]=read();
		s=read();
		reg ll ans=f[s];
		for(reg int S=1;S<(1<<4);++S){
			reg int cnt=0;
			reg ll sum=0;
			for(reg int i=0;i<4;++i)
				if((S>>i)&1){
					cnt^=1;
					sum+=1ll*c[i]*(d[i]+1);
				}
			if(sum<=s){
				if(cnt)
					ans-=f[s-sum];
				else
					ans+=f[s-sum];
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}