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

const int MAXN=1e5+5;

int n;
int a[MAXN];
ll sum[MAXN];
int g[MAXN],pos[MAXN];
ll f[MAXN];

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		sum[i]=sum[i-1]+a[i];
	}
	for(reg int i=1;i<=n;++i){
		pos[i]=max(pos[i],pos[i-1]);
		g[i]=g[pos[i]]+1;
		f[i]=sum[i]-sum[pos[i]];
		reg int l=i+1,r=n+1,mid;
		while(l<r){
			mid=(l+r)>>1;
			if(sum[mid]>=sum[i]+f[i])
				r=mid;
			else
				l=mid+1;
		}
		pos[l]=max(pos[l],i);
	}
	printf("%d\n",n-g[n]);
	return 0;
}