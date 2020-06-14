#include<bits/stdc++.h>
using namespace std;
#define reg register
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(ch<'0'||'9'<ch)f|=(ch=='-'),ch=getchar();
	while('0'<=ch&&ch<='9')res=10*res+ch-'0',ch=getchar();
	return f?-res:res;
}

const int MAXN=20+5;
const int MAXM=6+5;

int n,m;
int a[MAXN];
double ave=0;
double ans=1e20;
int x[MAXM];

inline void Calc(void){
	for(reg int i=1;i<=m;++i)
		x[i]=0;
	for(reg int i=1;i<=n;++i){
		reg int ptr=1;
		for(reg int j=1;j<=m;++j)
			if(x[j]<x[ptr])
				ptr=j;
		x[ptr]+=a[i];
	}
	reg double S2=0;
	for(reg int i=1;i<=m;++i)
		S2+=(ave-x[i])*(ave-x[i]);
	ans=min(ans,sqrt(S2/m));
	return;
}

int main(void){
	n=read(),m=read();
	for(reg int i=1;i<=n;++i)
		a[i]=read(),ave+=a[i];
	ave=ave/(double)m;
	for(reg int i=1;i<=500000;++i){
		random_shuffle(a+1,a+n+1);
		Calc();
	}
	printf("%.2lf\n",ans);
	return 0;
}