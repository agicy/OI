#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=2.5e5+5;
const int MAXM=2.5e5+5;

int A,B,n,m;
int a[MAXN],b[MAXM];
int x[MAXN],y[MAXN];

int main(void){
	A=read(),B=read(),n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read();
	for(reg int i=1;i<=m;++i)
		b[i]=read();
	a[++n]=A,b[++m]=B;
	sort(a+1,a+n+1),sort(b+1,b+m+1);
	for(reg int i=1;i<=n;++i)
		x[i]=a[i]-a[i-1];
	for(reg int i=1;i<=m;++i)
		y[i]=b[i]-b[i-1];
	sort(x+1,x+n+1),sort(y+1,y+m+1);
	reg int ptr1=2,ptr2=2;
	reg ll ans=1ll*x[1]*(m-1)+1ll*y[1]*(n-1);
	while(ptr1<=n&&ptr2<=m)
		if(x[ptr1]<y[ptr2])
			ans+=1ll*x[ptr1++]*(m-ptr2+1);
		else
			ans+=1ll*y[ptr2++]*(n-ptr1+1);
	printf("%lld\n",ans);
	return 0;
}