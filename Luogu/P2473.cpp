#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch)) res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

const int MAXK=100+5;
const int MAXN=15;

inline double max(reg double a,reg double b){
	return a>b?a:b;
}

int k,n;
int p[MAXN],S[MAXN];
double f[MAXK][1<<MAXN];

int main(void){
	k=read(),n=read();
	for(reg int i=0,x;i<n;++i){
		p[i]=read();
		do{
			x=read();
			if(x)
				S[i]|=(1<<(x-1));
		}while(x);
	}
	for(reg int i=k;i>=1;--i)
		for(reg int T=0;T<(1<<n);++T){
			for(reg int k=0;k<n;++k)
				if((S[k]&T)==S[k])
					f[i][T]+=max(f[i+1][T],f[i+1][T|(1<<k)]+p[k]);
				else
					f[i][T]+=f[i+1][T];
			f[i][T]/=n;
		}
	printf("%lf\n",f[1][0]);
	return 0;
}