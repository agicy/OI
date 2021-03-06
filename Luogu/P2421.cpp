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

inline int max(reg int a,reg int b){
	return a>b?a:b;
}

const int MAXN=15+5;

int n;
int s[MAXN],p[MAXN],l[MAXN];

inline int exgcd(reg int a,reg int b,reg int &x,reg int &y){
	if(!b){
		x=1,y=0;
		return a;
	}
	reg int d=exgcd(b,a%b,y,x);
	y-=a/b*x;
	return d;
}

inline bool check(reg int mod){
	for(reg int i=1;i<=n;++i)
		for(reg int j=i+1;j<=n;++j){
			reg int a=p[i]-p[j],b=mod,c=s[j]-s[i];
			int x,y;
			reg int d=exgcd(a,b,x,y);
			if(c%d)
				continue;
			a/=d,b/=d,c/=d;
			if(b<0)
				b=-b;
			x=(1ll*x*c%b+b)%b;
			if(x<=l[i]&&x<=l[j])
				return false;
		}
	return true;
}

int main(void){
	n=read();
	reg int Max=0;
	for(reg int i=1;i<=n;++i){
		s[i]=read(),p[i]=read(),l[i]=read();
		Max=max(Max,s[i]);
	}
	while(!check(Max))
		++Max;
	printf("%d\n",Max);
	return 0;
}