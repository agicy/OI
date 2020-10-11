#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return res;
}

const int MAXN=100+5;
const int MAXM=100+5;
const int inf=0x3f3f3f3f;

int n,m;
int a[MAXN][MAXM];

inline void cMax(reg int &Max,reg int &pMax,reg int val){
	if(Max<val)
		pMax=Max,Max=val;
	else if(pMax<val)
		pMax=val;
	return;
}

int main(void){
	reg int t=read();
	while(t--){
		n=read(),m=read();
		for(reg int i=1;i<=n;++i)
			for(reg int j=1;j<=m;++j)
				a[i][j]=read();
		reg ll ans=0;
		for(reg int i=1;i<=(n+1)/2;++i)
			for(reg int j=1;j<=(m+1)/2;++j){
				reg int ip=n-i+1,jp=m-j+1;
				int Max=a[i][j],pMax=-inf;
				cMax(Max,pMax,a[i][jp]),cMax(Max,pMax,a[ip][j]),cMax(Max,pMax,a[ip][jp]);
				if(i==ip&&j==jp)
					continue;
				else if(i==ip)
					ans+=0ll+abs(a[i][j]-pMax)+abs(a[i][jp]-pMax);
				else if(j==jp)
					ans+=0ll+abs(a[i][j]-pMax)+abs(a[ip][j]-pMax);
				else
					ans+=0ll+abs(a[i][j]-pMax)+abs(a[i][jp]-pMax)+abs(a[ip][j]-pMax)+abs(a[ip][jp]-pMax);
			}
		printf("%lld\n",ans);
	}
	return 0;
}