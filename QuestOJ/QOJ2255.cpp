#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
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

const int MAXN=2e5+5;

int n,k;
int a[MAXN],b[MAXN];
int r[MAXN];

inline bool check(reg ll a,reg ll b){
	return 1.0*a*b<=2.1e18;
}

inline ll solve(reg int lef){
	reg ll p=1,s=0,res=0;
	for(reg int i=lef;i<=n;++i)
		if(a[i]==1){
			reg int rig=r[i];
			reg int cnt=rig-i+1;
			if(p%k==0){
				reg ll tmp=p/k-s;
				if(1<=tmp&&tmp<=cnt)
					++res;
			}
			i=rig,s+=cnt;
		}
		else{
			if(!check(p,a[i]))
				break;
			p*=a[i],s+=a[i];
			if(p%k==0&&p/k==s)
				++res;
		}
	return res;
}

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=n;i>=1;--i)
		r[i]=a[i+1]==1?r[i+1]:i;
	reg ll ans=0;
	for(reg int i=1;i<=n;++i)
		ans+=solve(i);
	printf("%lld\n",ans);
	return 0;
}