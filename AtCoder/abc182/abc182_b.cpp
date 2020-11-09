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

const int MAXN=100+5;

int n;
int a[MAXN];

int main(void){
	n=read();
	int Max=0;
	for(reg int i=1;i<=n;++i){
		a[i]=read();
		Max=max(Max,a[i]);
	}
	int ans=0,gcd=0;
	for(reg int i=2;i<=Max;++i){
		reg int tot=0;
		for(reg int j=1;j<=n;++j)
			if(!(a[j]%i))
				++tot;
		if(tot>gcd)
			ans=i,gcd=tot;
	}
	printf("%d\n",ans);
	return 0;
}