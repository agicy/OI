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

const int MAXN=1e5+5;

int n,m;
bool dis[MAXN];

int main(void){
	n=read(),m=read();
	while(m--){
		static int a,b;
		a=read(),b=read();
		dis[a]=!dis[a],dis[b]=!dis[b];
	}
	for(reg int i=1;i<n;++i)
		if(dis[i]){
			puts("NO");
			return 0;
		}
	puts("YES");
	return 0;
}