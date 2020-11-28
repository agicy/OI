#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define int ll
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXN=1e5+5;
const int MAXS=256;

int n,q;
int a[MAXN];
int cnt[MAXS];
int sum[MAXN][MAXS];

signed main(void){
	n=read(),q=read();
	for(reg int i=0;i<MAXS;++i)
		cnt[i]=cnt[i>>1]+(i&1);
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		for(reg int j=0;j<MAXS;++j)
			if((a[i]&j)==a[i])
				sum[i][j]=sum[i-1][j]+1;
			else
				sum[i][j]=sum[i-1][j];
	}
	while(q--){
		static int l,r,x;
		l=read(),r=read(),x=read();
		reg ll ans=0;
		for(reg int i=0;i<MAXS;++i)
			if((i&x)==i){
				reg ll val=sum[r][i]-sum[l-1][i];
				if((cnt[i^x])&1)
					ans-=1ll*val*(val-1)*(val-2)/6;
				else
					ans+=1ll*val*(val-1)*(val-2)/6;
			}
		printf("%lld\n",ans);
	}
	return 0;
}