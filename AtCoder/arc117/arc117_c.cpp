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

inline void read(reg char *s){
	*s=getchar();
	while(!isalpha(*s)) *s=getchar();
	while(isalpha(*s)) *(++s)=getchar();
	*s='\0';
	return;
}

const int mod=3;

inline int add(reg int a,reg int b){
	a+=b;
	return a>=mod?a-mod:a;
}

const int fac[mod]={1,1,2};
const int invfac[mod]={1,1,2};

inline int binom(reg int n,reg int m){
	if(m<0||n<m)
		return 0;
	else
		return fac[n]*invfac[m]*invfac[n-m]%mod;
}

inline int lucas(reg int n,reg int m){
	if(!m)
		return 1;
	else
		return lucas(n/mod,m/mod)*binom(n%mod,m%mod)%mod;
}

const int MAXN=4e5+5;

int n;
char s[MAXN];

int main(void){
	n=read(),read(s+1);
	reg int ans=0;
	for(reg int i=1;i<=n;++i){
		switch(s[i]){
			case 'W':{
				break;
			}
			case 'R':{
				ans=add(ans,lucas(n-1,i-1));
				break;
			}
			case 'B':{
				ans=add(ans,lucas(n-1,i-1)*2%mod);
				break;
			}
		}
	}
	if(!(n&1))
		ans=add(0,mod-ans);
	switch(ans){
		case 0:{
			puts("W");
			break;
		}
		case 1:{
			puts("R");
			break;
		}
		case 2:{
			puts("B");
			break;
		}
	}
	return 0;
}