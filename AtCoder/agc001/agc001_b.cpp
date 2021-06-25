#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar()(p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[1<<21],*p1=buf,*p2=buf;
inline ll readll(void){
	reg char ch=getchar();
	reg ll res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ll dfs(reg ll l,reg ll s){
	if(l%s)
		return (((l/s)*s)<<1)+dfs(s,l%s);
	else
		return (l<<1)-s;
}

int main(void){
	reg ll n=readll(),x=readll();
	printf("%lld\n",n+(x>=n-x?dfs(x,n-x):dfs(n-x,x)));
	return 0;
}