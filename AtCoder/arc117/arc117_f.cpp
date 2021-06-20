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

inline ll max(reg ll a,reg ll b){
	return a>b?a:b;
}

const int MAXN=1.5e5;

int n;
int a[MAXN<<1];
ll dis[MAXN<<1];

inline void calc(reg ll S){
	for(reg int i=1;i<n;++i)
		dis[i]=max(dis[i-1],dis[i+n-1]+a[i+n]-S),dis[i+n]=max(dis[i+n-1],dis[i-1]+a[i]);
	return;
}

inline bool check(reg ll S){
	for(reg int i=0;i<n;++i)
		if(a[i]+a[i+n]>S)
			return false;
	dis[n]=a[0];
	calc(S);
	reg ll las=dis[n-1];
	dis[n]=max(dis[n],dis[n-1]);
	if(dis[n]+a[n]-S>0)
		return false;
	calc(S);
	if(las!=dis[n-1])
		return false;
	return dis[2*n-1]<=S;
}

int main(void){
	n=read();
	for(reg int i=0;i<(n<<1);++i)
		a[i]=read();
	reg ll l=0,r=1.5e14,mid;
	while(l<r){
		mid=(l+r)>>1;
		if(check(mid))
			r=mid;
		else
			l=mid+1;
	}
	printf("%lld\n",l);
	return 0;
}