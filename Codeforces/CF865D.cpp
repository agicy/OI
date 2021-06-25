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

int n;
priority_queue<int,vector<int>,greater<int>/**/> Q;

int main(void){
	n=read();
	reg ll ans=0;
	for(reg int i=1;i<=n;++i){
		int p=read();
		if(!Q.empty()&&Q.top()<p)
			ans+=p-Q.top(),Q.pop(),Q.push(p);
		Q.push(p);
	}
	printf("%lld\n",ans);
	return 0;
}