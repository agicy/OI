#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
typedef unsigned long long ull;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return res;
}

inline ull readull(void){
	reg char ch=getchar();
	reg ull res=0;
	while(!isdigit(ch))ch=getchar();
	while(isdigit(ch))res=10ull*res+(ch^'0'),ch=getchar();
	return res;
}

int n,m,c,k;
bool vis[64],tag[64];

int main(void){
	n=read(),m=read(),c=read(),k=read();
	for(reg int i=1;i<=n;++i){
		reg ull a=readull();
		for(reg int j=0;j<k;++j)
			vis[j]|=(a>>j)&1;
	}
	for(reg int i=1;i<=m;++i){
		static int p,q;
		p=read(),q=read();
		if(!vis[p])
			tag[p]=true;
	}
	reg int cnt=0;
	for(reg int i=0;i<k;++i)
		if(tag[i])
			++cnt;
	if(k-cnt==64)
		if(n)
			printf("%llu\n",ull(-n));
		else
			puts("18446744073709551616");
	else
		printf("%llu\n",(1ull<<(k-cnt))-n);
	return 0;
}