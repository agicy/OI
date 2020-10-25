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
	while(isdigit(ch))res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=2e5+5;
const int MAXK=300+5;
const int p=998244353;
const int inv2=499122177;

inline int add(reg int a,reg int b){
	reg int sum=a+b;
	return sum>=p?sum-p:sum;
}

inline int mul(reg int a,reg int b){
	return 1ll*a*b%p;
}

int n,k;
int h[MAXK],C[MAXK][MAXK];

int main(void){
	n=read(),k=read();
	for(reg int i=1;i<=n;++i){
		static int a;
		a=read();
		for(reg int j=0,x=1;j<=k;++j,x=mul(x,a))
			h[j]=add(h[j],x);
	}
	C[0][0]=1;
	for(reg int i=1;i<=k;++i){
		C[i][0]=1;
		for(reg int j=1;j<=i;++j)
			C[i][j]=add(C[i-1][j-1],C[i-1][j]);
	}
	for(reg int i=1;i<=k;++i){
		reg int ans=0;
		for(reg int j=0;j<=i;++j)
			ans=add(ans,1ll*C[i][j]*inv2%p*add(p-h[i],mul(h[j],h[i-j]))%p);
		printf("%d\n",ans);
	}
	return 0;
}
