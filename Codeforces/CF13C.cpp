#include<bits/stdc++.h>
using namespace std;
#define reg register
typedef long long ll;
#define getchar() (p1==p2&&(p2=(p1=buf)+fread(buf,1,100000,stdin),p1==p2)?EOF:*p1++)
static char buf[100000],*p1=buf,*p2=buf;
inline int read(void){
	reg bool f=false;
	reg char ch=getchar();
	reg int res=0;
	while(!isdigit(ch))f|=(ch=='-'),ch=getchar();
	while(isdigit(ch))res=10*res+(ch^'0'),ch=getchar();
	return f?-res:res;
}

priority_queue<int> Q;

int main(void){
	reg int n=read();
	reg ll ans=0;
	while(n--){
		int x=read();
		Q.push(x);
		if(Q.top()>x){
			ans+=Q.top()-x;
			Q.pop();
			Q.push(x);
		}
	}
	printf("%lld\n",ans);
	return 0;
}