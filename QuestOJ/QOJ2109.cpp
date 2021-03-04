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

int n,m;
int w[MAXN];
ll sum;

int main(void){
	n=read(),m=read(),read();
	for(reg int i=1;i<=n;++i){
		w[i]=read();
		sum+=w[i];
	}
	for(reg int i=1;i<=n;++i)
		printf("%.4lf%c",(1.0/sum*m+1.0)*w[i],i==n?'\n':' ');
	return 0;
}