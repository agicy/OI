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

inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

const int MAXN=1e4+5;
const int MAXK=1e3+5;

int n,k;
ll p;

inline ll add(reg ll a,reg ll b){
	a+=b;
	return a>=p?a-p:a;
}

ll strling[MAXN][MAXK];

__int128 I=1;

int main(void){
	n=read(),k=read(),p=readll();
	strling[0][0]=1;
	for(reg int i=1;i<=n;++i)
		for(reg int j=1;j<=k;++j)
			strling[i][j]=add(strling[i-1][j-1],I*j*strling[i-1][j]%p);
	printf("%lld\n",strling[n][k]);
	return 0;
}