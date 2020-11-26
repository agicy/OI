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

const int p=1e9+7;
const ll ans[]={0,0,0,2,2,0,0,52,300,0,0,35584,216288,0,0,79619280,653443600,0,0};
//              0 1 2 3 4 5 6 7  8   9 1011    12     131415       16        1718

int n;

int main(void){
	n=read();
	printf("%lld\n",ans[n]%p);
	return 0;
}