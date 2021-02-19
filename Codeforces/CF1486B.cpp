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

const int MAXN=1e3+5;

int n;
int x[MAXN],y[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		for(reg int i=0;i<n;++i)
			x[i]=read(),y[i]=read();
		sort(x,x+n),sort(y,y+n);
		printf("%lld\n",1ll*(x[n>>1]-x[(n-1)>>1]+1)*(y[n>>1]-y[(n-1)>>1]+1));
	}
	return 0;
}