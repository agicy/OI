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
int X[MAXN],Y[MAXN];

int main(void){
	reg int t=read();
	while(t--){
		n=read();
		reg int cntx=0,cnty=0;
		for(reg int i=1;i<=(n<<1);++i){
			static int x,y;
			x=read(),y=read();
			if(!x)
				Y[++cnty]=y;
			else
				X[++cntx]=x;
		}
		sort(X+1,X+cntx+1),sort(Y+1,Y+cnty+1);
		reg double ans=0;
		for(reg int i=1;i<=n;++i)
			ans+=sqrt(1.0*X[i]*X[i]+1.0*Y[i]*Y[i]);
		printf("%.15lf\n",ans);
	}
	return 0;
}