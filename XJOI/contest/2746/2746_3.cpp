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

const int MAXN=5e3+5;

int n,k;
int w[MAXN];
ll ans1,ans2;

int main(void){
	n=read();
	for(reg int i=1;i<=n;++i)
		w[i]=read();
	for(reg int i=1;i<n;++i)
		read(),read();
	k=read();
	for(reg int i=1;i<=k;++i){
		static int s,t;
		s=read(),t=read();
		ans1+=w[s],ans2+=w[t];
	}
	printf("%lld\n",max(ans1,ans2));
	return 0;
}